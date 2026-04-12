/*
** EPITECH PROJECT, 2026
** tests
** File description:
** tests for Core
*/

#include <criterion/criterion.h>
#include <exception>
#include "Arcade.hpp"
#include "DlLoader.hpp"
#include "Keys.hpp"

#define GAME_MOCK_LIB LIB_PATH "libgame_mock.so"
#define DISPLAY_MOCK_LIB LIB_PATH "libdisplay_mock.so"
#define INVALID_LIB "./nonexistent_lib.so"

// static

Test(Core, getGamesList_not_empty)
{
    auto list = Core::getGamesList();
    cr_assert(!list.empty());
}

Test(Core, getDisplayList_not_empty)
{
    auto list = Core::getDisplayList();
    cr_assert(!list.empty());
}

// constructor

Test(Core, constructor_throws_on_invalid_display)
{
    cr_assert_throw(Core(INVALID_LIB, GAME_MOCK_LIB), std::runtime_error);
}

Test(Core, constructor_throws_on_invalid_game)
{
    cr_assert_throw(Core(DISPLAY_MOCK_LIB, INVALID_LIB), std::runtime_error);
}

Test(Core, constructor_throws_when_game_lib_used_as_display)
{
    cr_assert_throw(Core(GAME_MOCK_LIB, GAME_MOCK_LIB), std::runtime_error);
}

Test(Core, constructor_throws_when_display_lib_used_as_game)
{
    cr_assert_throw(Core(DISPLAY_MOCK_LIB, DISPLAY_MOCK_LIB), std::runtime_error);
}

Test(Core, constructor_valid_does_not_throw)
{
    bool threw = false;
    try {
        Core core(DISPLAY_MOCK_LIB, GAME_MOCK_LIB);
    } catch (const std::exception &) {
        threw = true;
    }
    cr_assert(!threw);
}

// iteration

Test(Core, doIteration_calls_update_and_render)
{
    DlLoader game_loader(GAME_MOCK_LIB);
    game_loader.load();
    DlLoader display_loader(DISPLAY_MOCK_LIB);
    display_loader.load();

    auto g_reset = reinterpret_cast<void(*)()>(game_loader.sym("reset_counts"));
    auto d_reset = reinterpret_cast<void(*)()>(display_loader.sym("reset_counts"));
    auto d_clear = reinterpret_cast<void(*)()>(display_loader.sym("clear_events"));
    g_reset();
    d_reset();
    d_clear();

    Core core(DISPLAY_MOCK_LIB, GAME_MOCK_LIB);
    g_reset();
    d_reset();

    core.doIteration();

    auto get_update = reinterpret_cast<int(*)()>(game_loader.sym("get_update_count"));
    auto get_render = reinterpret_cast<int(*)()>(display_loader.sym("get_render_count"));
    cr_assert_eq(get_update(), 1);
    cr_assert_eq(get_render(), 1);
}

Test(Core, doIteration_exit_command_skips_update_and_render)
{
    DlLoader game_loader(GAME_MOCK_LIB);
    game_loader.load();
    DlLoader display_loader(DISPLAY_MOCK_LIB);
    display_loader.load();

    auto g_reset = reinterpret_cast<void(*)()>(game_loader.sym("reset_counts"));
    auto d_reset = reinterpret_cast<void(*)()>(display_loader.sym("reset_counts"));
    auto d_clear = reinterpret_cast<void(*)()>(display_loader.sym("clear_events"));
    auto push_event = reinterpret_cast<void(*)(CommonKey)>(display_loader.sym("push_event_key"));
    g_reset();
    d_reset();
    d_clear();

    Core core(DISPLAY_MOCK_LIB, GAME_MOCK_LIB);
    g_reset();
    d_reset();

    push_event(CommonKey::I);
    core.doIteration();

    auto get_update = reinterpret_cast<int(*)()>(game_loader.sym("get_update_count"));
    auto get_render = reinterpret_cast<int(*)()>(display_loader.sym("get_render_count"));
    cr_assert_eq(get_update(), 0);
    cr_assert_eq(get_render(), 0);
}
