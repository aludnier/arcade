/*
** EPITECH PROJECT, 2026
** tests
** File description:
** mock game library header
*/

#pragma once

#include "IGame.hpp"

#define EXPORT extern "C"

class MockGame : public IGame {
public:
    void init() override;
    void close() override;
    void update(std::queue<Event>) override;
    std::queue<AnyInstruction> getGfxInstructions() override;
    std::queue<GameEvent> getEvent() override;
};

EXPORT {
    LIB_TYPE getLibType();
    IGame *create();
    int get_init_count();
    int get_close_count();
    int get_update_count();
    int get_gfx_count();
    void reset_counts();
}
