/*
** EPITECH PROJECT, 2026
** Snake
** File description:
** Snake
*/

#pragma once

#include "IGame.hpp"
#include "gfx.hpp"
#include <functional>
#include <map>
#include <queue>

class MenuGame : public IGame {
    public:
        void init() override;
        void close() override;
        void update(std::queue<Event>) override;
        std::queue<AnyInstruction> getGfxInstructions() override;
        std::queue<GameEvent> getEvent() override;

    private:
        std::queue<AnyInstruction> createButton(size_t x, size_t y, std::string background_location, std::function<void()> callback);
        void _handle_click(point_t click);

        std::map<area_t, std::function<void()>> _interactiveAreas;
        std::queue<GameEvent> _events;
};
