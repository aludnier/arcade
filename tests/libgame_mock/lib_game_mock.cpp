/*
** EPITECH PROJECT, 2026
** tests
** File description:
** mock game library for unit tests
*/

#include "lib_game_mock.hpp"
#include <queue>

static int g_init_count = 0;
static int g_close_count = 0;
static int g_update_count = 0;
static int g_gfx_count = 0;
static int g_event_count = 0;

void MockGame::init() { g_init_count++; }
void MockGame::close() { g_close_count++; }
void MockGame::update(std::queue<Event>) { g_update_count++; }

std::queue<GameEvent> MockGame::getEvent()
{
    g_event_count++;
    return {};
}

std::queue<AnyInstruction> MockGame::getGfxInstructions()
{
    g_gfx_count++;
    return {};
}

LIB_TYPE getLibType() { return LIB_TYPE::GAME; }
IGame *create() { return new MockGame(); }
int get_init_count() { return g_init_count; }
int get_close_count() { return g_close_count; }
int get_update_count() { return g_update_count; }
int get_gfx_count() { return g_gfx_count; }
void reset_counts()
{
    g_init_count = 0;
    g_close_count = 0;
    g_update_count = 0;
    g_gfx_count = 0;
}
