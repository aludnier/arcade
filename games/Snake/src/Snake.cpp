#include "Snake.hpp"
#include "GameMatrix.hpp"
#include "IGame.hpp"
#include "Keys.hpp"
#include "gfx.hpp"
#include <cstddef>
#include <cstdio>
#include <ncurses.h>
#include <queue>
#include <chrono>
#include <stack>
#include <variant>

extern "C" IGame *create()
{
    return new Snake::GameSnake();
}

Snake::GameSnake::GameSnake() :
    _matrix(COLUMNS, LINES, Snake::EMPTY, TILESIZE), _speed(1)
{
};

void Snake::GameSnake::_setBackground()
{
    for (size_t x = 0; x < COLUMNS; x++)
            _matrix(x, 0) = WALL;
    for (size_t x = 0; x < COLUMNS; x++)
        _matrix(x, LINES - 1) = WALL;
    for (size_t y = 0; y < LINES; y++)
            _matrix(0, y) = WALL;
    for (size_t y = 0; y < LINES; y++)
            _matrix(COLUMNS - 1, y) = WALL;
    for (int i = 0; i < COLUMNS; i++) {
        for (int j = 0; j < LINES; j++)
            _games[_matrix(i, j)].push_back({i, j});
    }
}

void Snake::GameSnake::setShark()
{
    _snake.clear();
    _snake.push_front({11, 10, HEAD, UP});
    _snake.push_back({10, 10, BODY, RIGHT});
    _snake.push_back({9, 10, BODY, RIGHT});
    _snake.push_back({8, 10, TAIL, RIGHT});
}

void Snake::GameSnake::setFish()
{
    int index = rand() % (_games[EMPTY].size());

    _fish.x = _games[EMPTY][index].x;
    _fish.y = _games[EMPTY][index].y;
}

void Snake::GameSnake::init()
{
    _score = 0;
    _setBackground();
    setShark();
    setFish();
};

void Snake::GameSnake::close()
{

};

Snake::DIRECTION Snake::GameSnake::getDirection(CommonKey &key)
{
    DIRECTION direction = _keys[key];

    if (direction == _opposites[_snake.front().direction])
        return _snake.front().direction;
    return direction;
};

void Snake::GameSnake::_moveUp()
{
    _snake.front().y = (_snake.front().y - _speed + LINES) % LINES;
}

void Snake::GameSnake::_moveDown()
{
    _snake.front().y = (_snake.front().y + _speed) % LINES;
}
void Snake::GameSnake::_moveLeft()
{
    _snake.front().x = (_snake.front().x - _speed + COLUMNS) % COLUMNS;
}

void Snake::GameSnake::_moveRight()
{
    _snake.front().x = (_snake.front().x + _speed) % COLUMNS;
}

void Snake::GameSnake::_updateMatrix()
{
    _matrix = GameMatrix<GAME>(COLUMNS, LINES, EMPTY, TILESIZE);
    _setBackground();

    for (const auto &elem : _snake) {
        _matrix(elem.x, elem.y) = elem.part;
    }
    _matrix(_fish.x, _fish.y) = FISH;
}

void Snake::GameSnake::_handleCollision()
{
    if (_matrix(_snake.front().x, _snake.front().y) == WALL) {
        printf("WALL\n");
        this->init();
    }
    if (_matrix(_snake.front().x, _snake.front().y) == FISH) {
        printf("FISH\n");
        _score += 1;
        snake_t newPart = {
            _snake.back().x, _snake.back().y, TAIL, _snake.front().direction};
        _snake.back().part = BODY;
        _snake.push_back(newPart);
        setFish();
        printf("SPEED: %ld\n", (BASIC_SPEED - (_score * 10)));
    }
    if ((_matrix(_snake.front().x, _snake.front().y) == BODY) || 
        _matrix(_snake.front().x, _snake.front().y) == TAIL) {
        this->init();
    }
}

void Snake::GameSnake::_moveSnake()
{
    for (size_t i = (_snake.size() - 1); i > 0; i--) {
        _snake[i].x = _snake[i - 1].x;
        _snake[i].y = _snake[i - 1].y;
    }
    _directions[_snake.front().direction]();

}

void Snake::GameSnake::update(std::queue<Event> events)
{
    static auto start = std::chrono::steady_clock::now();
    const auto interval = std::chrono::milliseconds((BASIC_SPEED - (_score * 10)));
    CommonKey *key = 0;

    _setBackground();
    while (!events.empty()) {
        key = std::get_if<CommonKey>(&events.front());
        if (key)
            _snake.front().direction = this->getDirection(*key);
        events.pop();
    }
    auto now = std::chrono::steady_clock::now();
    if (now - start >= interval) {
        _moveSnake();
        _handleCollision();
        _updateMatrix();
        start = now;
    }
}

std::queue<AnyInstruction> Snake::GameSnake::_convertMatrixToGfx()
{
    std::queue<AnyInstruction> instructions = {};
    std::stack<rectInstr> matrixInstruction =_matrix.matrixToGFX("", 5);
    point_t coordonates = {0, 0};
    GAME type = EMPTY;

    while (!matrixInstruction.empty()) {
        rectInstr tile = matrixInstruction.top();
        coordonates.x = tile.x / TILESIZE;
        coordonates.y = tile.y / TILESIZE;
        type = _matrix(coordonates.x, coordonates.y);
        tile.asset_location = _assets[type].assets;
        tile.txt = _assets[type].txt;
        tile.color_hex = _assets[type].color;
        instructions.push(tile);
        matrixInstruction.pop();
    }
    return instructions;
}

std::queue<AnyInstruction> Snake::GameSnake::getGfxInstructions()
{
    std::queue<AnyInstruction> instructions = _convertMatrixToGfx();
    //dimensionInstr dim = {LINES * TILESIZE, COLUMNS * TILESIZE};

    //instructions.push(dim);
    return instructions;
}

std::queue<GameEvent> Snake::GameSnake::getEvent()
{
    return _events;
}

Snake::GameSnake::~GameSnake() {};

extern "C" LIB_TYPE getLibType()
{
    return GAME;
}
