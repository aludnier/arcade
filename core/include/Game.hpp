/*
** EPITECH PROJECT, 2026
** Game
** File description:
** Game header
*/

#pragma once

#include "IGame.hpp"
#include "DlLoader.hpp"
#include <memory>

class Game : public IGame {
    public:
        Game(const std::string &lib_location);
        Game &operator=(Game &&other) noexcept;
        ~Game();

        void init() override;
        void close() override;
        void update(std::queue<Event>) override;
        std::queue<AnyInstruction> getGfxInstructions() override;
        std::queue<GameEvent> getEvent() override;

    private:
        DlLoader _lib;
        std::unique_ptr<IGame> _self;
};
