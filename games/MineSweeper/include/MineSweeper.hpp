/*
** EPITECH PROJECT, 2026
** Minesweeper
** File description:
** 
*/

#pragma once

#include "IGame.hpp"
#include "Keys.hpp"
#include "gfx.hpp"
#include "GameMatrix.hpp"
#include <chrono>

namespace MineSweeper
{
    enum VISIBILITY {
        HIDE,
        VISIBLE,
        FLAG,
    };

    struct cell {
        bool isMine;
        VISIBILITY visiblility;
        int neighboringBombs;
    };

    #define TILESIZE 50
    #define MATRIXLEN 13
    #define MATRIXSIZE MATRIXLEN * MATRIXLEN
    #define MINBOMB 15
    #define MAXBOMB 25
    #define TILEASSET "games/MineSweeper/asset/tileMineSweeper.jpg"
    #define FLAGASSET "games/MineSweeper/asset/TileFlag.png"
    #define FONT "games/MineSweeper/asset/Minesweeper.ttf"
    #define SMILEY "games/MineSweeper/asset/Smiley.png"
    #define SMILEYDEAD "games/MineSweeper/asset/SmileyDead.png"
    #define SMILEYWIN "games/MineSweeper/asset/SmileyWin.png"

    class Game : public IGame 
    {
    public:
        Game();
        ~Game();

        void init() override;
        void close() override;
        void update(std::queue<Event>) override;
        std::queue<AnyInstruction> getGfxInstructions() override;
        std::queue<GameEvent> getEvent() {return {};} ;
        void discoverTile(cell &tile);
        void setNeighbour(std::size_t x, std::size_t y);
        void findNextNeighbour(std::size_t x, std::size_t y);
        point_t findCoords(cell &target);
        std::size_t discoverAdjacent(point_t pos);

    private:
        GameMatrix<cell> _bombs;

        rectInstr _smileyRect = {{MATRIXLEN * TILESIZE, 0, 0, "", 0}, 100, 100};
        textInstr _endGameScreen = {{{0, 700, 0, FONT, 0x0000FF00}, 100, 800}, "GAME OVER", 100};
        textInstr _timer = {{{MATRIXLEN * TILESIZE, 100, 0, FONT, 0xFFFFFF00}, 100, 150}, "", 50};
        std::unordered_map<int, std::string> _tileAsset {
            {-1, "games/MineSweeper/asset/bomb.jpg"},
            {0, "games/MineSweeper/asset/TileEmpty.png"},
            {1, "games/MineSweeper/asset/Tile1.png"},
            {2, "games/MineSweeper/asset/Tile2.png"},
            {3, "games/MineSweeper/asset/Tile3.png"},
            {4, "games/MineSweeper/asset/Tile4.png"},
            {5, "games/MineSweeper/asset/Tile5.png"},
            {6, "games/MineSweeper/asset/Tile6.png"},
            {7, "games/MineSweeper/asset/Tile7.png"},
            {8, "games/MineSweeper/asset/Tile8.png"},
        };
        bool _win = false;
        bool _isAlive = true;
        bool _flagActive = false;
        std::chrono::_V2::steady_clock::time_point _timerStart;
        std::size_t _discover = 0;
        std::size_t _nbBombs;
    };
}
