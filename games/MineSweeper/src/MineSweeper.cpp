/*
** EPITECH PROJECT, 2026
** MineSweeper
** File description:
** 
*/

#include "MineSweeper.hpp"
#include <ctime>


MineSweeper::Game::Game():
    _bombs(GameMatrix<cell>(0,0, {false, HIDE, 0}, TILESIZE))
{
}

MineSweeper::Game::~Game()
{
}

void MineSweeper::Game::setNeighbour(std::size_t x, std::size_t y)
{
    _bombs(x, y).isMine = true;
    _bombs(x, y).neighboringBombs = -1;
    for (int i = -1; i <= 1; i++) {
        for (int  j = -1; j <= 1; j++) {
            try {
                _bombs(x + i, y + j).neighboringBombs += 
                    (_bombs(x + i, y + j).isMine) ? 0 : 1;
            } catch (std::exception &e){
            }
        }
    }
    
}

void MineSweeper::Game::findNextNeighbour(std::size_t x, std::size_t y)
{
    std::size_t newX;
    std::size_t newY;
    for (size_t i = 0; i < MATRIXSIZE; i++) {
        newX = (x + ((i / 10) % MATRIXLEN)) % MATRIXLEN;
        newY = (y + (i % MATRIXLEN)) % MATRIXLEN;
        if (_bombs(newX, newY).isMine == false) {
            setNeighbour(newX, newY);
            return;
        }
    }
}

void MineSweeper::Game::init()
{
    std::size_t x = 0;
    std::size_t y = 0;

    _isAlive = true;
    _win = false;
    _discover = 0;
    _timerStart = std::chrono::steady_clock::now();
    std::srand(std::time({}));
    _nbBombs = std::rand() % (MAXBOMB - MINBOMB) + MINBOMB;
    _bombs.resize(0,0);
    _bombs.resize(MATRIXLEN, MATRIXLEN);

    for (std::size_t i = 0; i < _nbBombs; i++) {
        x = std::rand() % MATRIXLEN;
        y = std::rand() % MATRIXLEN;
        if (_bombs(x,y).isMine){
            findNextNeighbour(x, y);
            continue;
        }
        setNeighbour(x, y);
    }
    std::cout << "nb bomb = " << _nbBombs << std::endl;
}


point_t MineSweeper::Game::findCoords(cell &target)
{
    for (int x = 0; x < MATRIXLEN; x++) {
        for (int y = 0; y < MATRIXLEN; y++) {
            if (&_bombs(x, y) == &target)
                return {x, y};
        }
    }
    throw std::runtime_error("Cell not found in matrix");
}

std::size_t MineSweeper::Game::discoverAdjacent(point_t pos)
{
    if (_bombs(pos.x, pos.y).visiblility == VISIBILITY::VISIBLE ||
        _bombs(pos.x, pos.y).neighboringBombs == -1)
        return 0;

    _bombs(pos.x, pos.y).visiblility = VISIBILITY::VISIBLE;
    if (_bombs(pos.x, pos.y).neighboringBombs > 0){
        return 1;
    }
    std::size_t discover = 1;
    for (int i = -1; i <= 1; i++) {
        for (int  j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;
            try {
                point_t next = {pos.x + i, pos.y + j};
                discover += discoverAdjacent(next);
            } catch (std::exception &e){
            }
        }
    }
    return discover;
}

void MineSweeper::Game::discoverTile(cell &tile)
{
    if (tile.visiblility == VISIBLE)
        return;
    if (_flagActive){
        tile.visiblility = (tile.visiblility == FLAG) ? HIDE : FLAG;
    } else {
        if (tile.visiblility == VISIBILITY::FLAG)
            return;
        if (tile.isMine) {
            tile.visiblility = VISIBLE;
            _isAlive = false;
            return;
        }
        if (tile.neighboringBombs == 0) {
            try {
                _discover += discoverAdjacent(findCoords(tile));
            } catch (std::exception &e) {}
        } else {
            _discover += 1;
        }
        tile.visiblility = VISIBLE;
    }
    std::cout << "discover tiles : " << _discover << std::endl;
    if (_discover == MATRIXSIZE - _nbBombs){
        _win = true;
    }
}

void MineSweeper::Game::update(std::queue<Event> events)
{
    point_t *click;
    CommonKey *key;

    while (!events.empty()) {
        click = std::get_if<point_t>(&events.front());
        if (click && _isAlive && !_win){
            std::cout << "get Click" << std::endl;
            _bombs.onTileClick(*click,
                [this](MineSweeper::cell &tile) {discoverTile(tile);});
        }
        key = std::get_if<CommonKey>(&events.front());
        if (key && *key == CommonKey::F){
            _flagActive = !_flagActive;
            std::cout << "flag active : "<< _flagActive << std::endl;
        }
        if (key && *key == CommonKey::R){
            init();
            break;
        }
        events.pop();
    }
    if (_isAlive && !_win &&
        std::chrono::steady_clock::now() - _timerStart > std::chrono::minutes(5)){
        _isAlive = false;
    }
}

void MineSweeper::Game::close()
{
}

std::queue<AnyInstruction> MineSweeper::Game::getGfxInstructions()
{
    std::queue<AnyInstruction> instructions;
    std::stack<rectInstr> matrixInstruction = _bombs.matrixToGFX(TILEASSET, '#');
    point_t coordinates = {0, 0};

    while (!matrixInstruction.empty()) {
        rectInstr tile = matrixInstruction.top();
        coordinates.x = tile.x / TILESIZE;
        coordinates.y = tile.y / TILESIZE;
        if (_bombs(coordinates.x,coordinates.y).visiblility == VISIBILITY::VISIBLE){
            tile.asset_location = 
                _tileAsset[_bombs(coordinates.x,coordinates.y).neighboringBombs];
        } else if (_bombs(coordinates.x, coordinates.y).visiblility == VISIBILITY::FLAG) {
            tile.asset_location = FLAGASSET;
        }
        instructions.push(tile);
        matrixInstruction.pop();
    }
    if (!_isAlive || _win){
        instructions.push(_endGameScreen);
    } else {
        auto time = std::chrono::minutes(5) - (std::chrono::steady_clock::now() - _timerStart);
        auto sec = std::chrono::duration_cast<std::chrono::seconds>(time);
        _timer.text = std::to_string(sec.count());
    }
    _smileyRect.asset_location = (!_isAlive) ? SMILEYDEAD : (_win)? SMILEYWIN : SMILEY;
    instructions.push(_timer);
    instructions.push(_smileyRect);
    return instructions;
}
