/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Arcade
*/

#include "Arcade.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include "IGame.hpp"
#include "gfx.hpp"
#include <chrono>
#include <queue>
#include <string>
#include <thread>
#include <variant>

Core::Core(const std::string &display_lib, const std::string &game_lib) : _game(game_lib), _display(display_lib)
{
    _displayList = getDisplayList();
    _gamesList = getGamesList();

    _currentDisplay = _findIndex(_displayList, display_lib);
    _currentGame = _findIndex(_gamesList, game_lib);
}

void Core::run()
{
    bool running = true;
    const auto interval = std::chrono::microseconds(SECOND / IPS);

    while (running) {
        auto start = std::chrono::steady_clock::now();

        if (doIteration() < 0)
            return;

        auto elapsed = std::chrono::steady_clock::now() - start;
        if (elapsed < interval) {
            std::this_thread::sleep_for(interval - elapsed);
            continue;
        }
        std::this_thread::sleep_for(interval);
    }
}

int Core::doIteration()
{
    auto events = _display.pollEvents();
    auto gameEvents = _game.getEvent();

    int cmd = _handle_command(events);
    if (cmd < 0)
        return -1;

    _handle_gameEvent(gameEvents);

    if (cmd == 0)
        _game.update(events);
    _display.render(_game.getGfxInstructions());
    return 0;
}

int Core::_handle_command(std::queue<Event> events)
{
    Event curr;
    bool switched = false;

    while (!events.empty()) {
        curr = events.front();
        if (std::holds_alternative<CommonKey>(curr)) {
            int res = _apply_command(std::get<CommonKey>(curr), switched);
            if (res < 0)
                return -1;
        }
        events.pop();
    }
    return switched ? 1 : 0;
}

int Core::_apply_command(CommonKey cmd, bool &switched)
{
    switch (cmd) {
        case CommonKey::P:
            _display.reset();
            _currentDisplay = (_currentDisplay + 1) % _displayList.size();
            _display = Display(_displayList[_currentDisplay]);
            _display.init();
            switched = true;
            break;
        case CommonKey::M:
            _currentGame = (_currentGame + 1) % _gamesList.size();
            _game = Game(_gamesList[_currentGame]);
            switched = true;
            break;
        case CommonKey::O:
            _game = Game(_gamesList[_currentGame]);
            switched = true;
            break;
        case CommonKey::L:
            _game = Game(MENU_GAME);
            switched = true;
            break;
        case CommonKey::I:
            return -1;
        default:
            break;
    }
    return 0;
}

size_t Core::_findIndex(const std::vector<std::string> &list, const std::string &value)
{
    for (size_t i = 0; i < list.size(); ++i) {
        if (list[i] == value)
            return i;
    }
    return 0;
}

std::vector<std::string> Core::getGamesList()
{
    return {std::string(LIB_PATH) + "arcade_snake.so", std::string(LIB_PATH) + "arcade_minesweeper.so"};
}

std::vector<std::string> Core::getDisplayList()
{
    return {std::string(LIB_PATH) + "arcade_sfml.so", std::string(LIB_PATH) + "arcade_sdl2.so", std::string(LIB_PATH) + "arcade_ncurses.so"};
}

void Core::_handle_gameEvent(std::queue<GameEvent> events)
{
    GameEvent curr;

    while (!events.empty()) {
        curr = events.front();
        if (std::holds_alternative<switchGamevent>(curr))
            _game = Game(std::get<switchGamevent>(curr).lib_location);
        events.pop();
    }
}
