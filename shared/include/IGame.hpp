/*
** EPITECH PROJECT, 2026
** IGame
** File description:
** header
*/

#pragma once

#include "gfx.hpp"
#include <queue>

enum LIB_TYPE {
    GAME,
    DISPLAY
};

struct switchGamevent {
    std::string lib_location;
};

using GameEvent = std::variant<switchGamevent>;

class IGame {
    public:
        virtual ~IGame() = default;
        virtual void init() = 0;
        virtual void close() = 0;
        virtual void update(std::queue<Event>) = 0;
        virtual std::queue<AnyInstruction> getGfxInstructions() = 0;
        virtual std::queue<GameEvent> getEvent() = 0;
};
