/*
** EPITECH PROJECT, 2026
** IGame
** File description:
** header
*/

#pragma once

#include "IGame.hpp"
#include "Keys.hpp"
#include "gfx.hpp"
#include <cstddef>
#include <deque>
#include <functional>
#include <ncurses.h>
#include <queue>
#include <string>
#include <deque>
#include <map>
#include <vector>
#include "GameMatrix.hpp"

#define TILESIZE 40
#define COLUMNS 20
#define LINES 20
#define BASIC_SPEED 500


namespace Snake {

enum GAME {
    EMPTY,
    WALL,
    SCORE,
    FISH,
    HEAD,
    BODY,
    TAIL,
};

enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct snake_t {
    size_t x;
    size_t y;
    GAME part;
    DIRECTION direction;
};

struct cell {
    std::string assets;
    char txt;
    size_t color;
};

using MoveFunc = std::function<void(void)>;
using setDirectionFunc = std::function<DIRECTION(CommonKey)>;

class GameSnake : public IGame {
public:
    GameSnake();
    void init() override;
    void close() override;
    void update(std::queue<Event>) override;
    DIRECTION getDirection(CommonKey &key);
    void setShark();
    void setFish();
    GameMatrix<GAME> getMatrix() const { return _matrix; };
    std::deque<snake_t> &getShark() { return _snake; };
    point_t &getFish() { return _fish; };
    std::map<GAME, std::vector<point_t>> &getGames() { return _games; };
    std::queue<AnyInstruction> getGfxInstructions() override;
    std::queue<GameEvent> getEvent() override;
    ~GameSnake();
private:
    void _moveUp();
    void _moveDown();
    void _moveLeft();
    void _moveRight();
    void _moveSnake();
    void _updateMatrix();
    void _setBackground();
    void _handleCollision();
    std::queue<AnyInstruction> _convertMatrixToGfx();

    static cell createCell(std::string assetLocation, char txt, size_t color)
    { cell newCell {assetLocation, txt, color}; return newCell; }

    std::map<GAME, cell> _assets {
            {EMPTY, createCell("games/Snake/assets/empty.png", ' ', 0)},
            {SCORE, createCell("games/Snake/assets/wild-jungle-font/WildJungleRegular-vnop9.ttf", '\0', 16777215)},
            {WALL, createCell("games/Snake/assets/wall.png", '#', 32768)},
            {FISH, createCell("games/Snake/assets/fish.png", '@', 16711680)},
            {HEAD, createCell("games/Snake/assets/pixelhead.png", '>', 255)},
            {TAIL, createCell("games/Snake/assets/pixeltail.png", '<', 7845374)},
            {BODY, createCell("games/Snake/assets/pixelbody.png", '=', 3247335)}
    };

    std::map<DIRECTION, MoveFunc> _directions {
        {UP, [this]() -> void { _moveUp();}},
        {DOWN, [this]() -> void { _moveDown(); }},
        {LEFT, [this]() -> void { _moveLeft(); }},
        {RIGHT, [this]() -> void { _moveRight(); }}
    };

    std::map<DIRECTION, DIRECTION> _opposites {
        {UP, DOWN},
        {DOWN, UP},
        {LEFT, RIGHT},
        {RIGHT, LEFT}
    };

    std::map<CommonKey, DIRECTION> _keys {
        {CommonKey::UP, UP},
        {CommonKey::DOWN, DOWN},
        {CommonKey::LEFT, LEFT},
        {CommonKey::RIGHT, RIGHT}
    };

    GameMatrix<GAME> _matrix;
    std::deque<snake_t> _snake;
    std::map<GAME, std::vector<point_t>> _games;
    point_t _fish;
    int _speed;
    size_t _score;
    std::queue<GameEvent> _events;
};
}
