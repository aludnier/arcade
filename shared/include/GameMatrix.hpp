/*
** EPITECH PROJECT, 2026
** GameMatrix
** File description:
** 
*/

#pragma once

#include "IGame.hpp"
#include <cstdio>
#include <vector>
#include <exception>
#include <sstream>
#include <iostream>
#include "gfx.hpp"
#include <stack>

template <typename T>
class GameMatrix {
    public:
        GameMatrix(std::size_t columns, std::size_t lines, T defaultValue, std::size_t tileSize):
        _lines(lines),
        _columns(columns),
        _tileSize(tileSize),
        _defaultValue(defaultValue)
        {
            _matrix.resize(_lines, std::vector<T>(_columns));
            for (std::vector<T> &elem : _matrix) {
                elem.resize(_columns, _defaultValue);
            }
        };

        rectInstr createTileGFX(char txt)
        {
            rectInstr tileGFX = {{0, 0, ' ', std::nullopt ,0x0}, 0,0};

            tileGFX.h = _tileSize;
            tileGFX.w = _tileSize;
            tileGFX.txt = txt;
            return tileGFX;
        };


        void clearInstruct() 
        {
            while (!instruct.empty()) {
                instruct.pop();
            }
        }

        std::stack<rectInstr> &matrixToGFX(std::size_t color, char txt = ' ')
        {
            rectInstr tileGFX;
            clearInstruct();

            for (std::size_t y = 0; y < _matrix.size(); y++){
                for (std::size_t x = 0; x < _matrix[y].size(); x++){
                    tileGFX = createTileGFX(txt);
                    tileGFX.color_hex = color;
                    tileGFX.x = x * _tileSize;
                    tileGFX.y = y * _tileSize;
                    instruct.push(tileGFX);
                }
            }
            return instruct;
        };

        std::stack<rectInstr> &matrixToGFX(std::string asset, char txt = ' ')
        {
            rectInstr tileGFX;
            clearInstruct();

            for (std::size_t y = 0; y < _matrix.size(); y++){
                for (std::size_t x = 0; x < _matrix[y].size(); x++){
                    tileGFX = createTileGFX(txt);
                    tileGFX.asset_location = asset;
                    tileGFX.x = x * _tileSize;
                    tileGFX.y = y * _tileSize;
                    instruct.push(tileGFX);
                }
            }
            return instruct;
        };

        void resize(std::size_t newColumns, std::size_t newLines)
        {
            _lines = newLines;
            _columns = newColumns;
            _matrix.resize(_lines, std::vector<T>(_columns));
            for (std::vector<T> &elem : _matrix) {
                elem.resize(_columns, _defaultValue);
            }
        };

        T& operator()(std::size_t x, std::size_t y) 
        {
            if (x >= _columns || y >= _lines){
                throw SizeError(x, y);
            }
            return _matrix[y][x];
        };

        void printMatrix()
        {
            for (std::vector<T> line : _matrix){
                for (T &elem : line){
                    std::cout << elem;
                }
                std::cout << std::endl;
            }
        };

        class SizeError : public std::exception
        {
            private:
                std::string msg;
            public:
                SizeError(std::size_t x, std::size_t y)
                {
                    std::stringstream tmp;

                    tmp << "the coordinate (" << x << "," << y << ") doesnt fit the matrix";
                    msg = tmp.str();
                };
                const char* what() const noexcept override{
                    return msg.c_str();
                }
        };

        void onTileClick(point_t EventPoint, const std::function<void(T &cell)> &func)
        {
            std::size_t cellX = EventPoint.x / _tileSize;
            std::size_t cellY = EventPoint.y / _tileSize;

            if (cellX >= _columns || cellY >= _lines)
                return;
            func(_matrix[cellY][cellX]);
        }
    private:
        std::stack<rectInstr> instruct;
        std::vector<std::vector<T>> _matrix;
        std::size_t _lines;
        std::size_t _columns;
        std::size_t _tileSize;
        T _defaultValue;
};
