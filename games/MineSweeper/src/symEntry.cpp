/*
** EPITECH PROJECT, 2026
** entry point minesweeper
** File description:
** 
*/

#include "MineSweeper.hpp"

extern "C" IGame *create()
{
    return new MineSweeper::Game();
}

extern "C" LIB_TYPE getLibType()
{
    return LIB_TYPE::GAME;
}
