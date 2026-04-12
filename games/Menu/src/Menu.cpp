/*
** EPITECH PROJECT, 2026
** Menu
** File description:
** Menu
*/

#include "Menu.hpp"
#include "IGame.hpp"
#include "gfx.hpp"
#include "DisplayVariable.hpp"
#include "Utils.hpp"

#include <queue>
#include <string>

#define MENU_SCREEN_H SCREEN_H / 3
#define MENU_SCREEN_W SCREEN_W / 4

extern "C" LIB_TYPE getLibType()
{
    return LIB_TYPE::GAME;
}

extern "C" IGame *create()
{
    return new MenuGame();
}

void MenuGame::init()
{
}

void MenuGame::close()
{
}

std::queue<GameEvent> MenuGame::getEvent()
{
    std::queue<GameEvent> events;
    std::swap(events, _events);
    return events;
}

std::queue<AnyInstruction> MenuGame::createButton(size_t x, size_t y, std::string background_location, std::function<void()> callback)
{
    std::queue<AnyInstruction> q;
    size_t w = 400;
    size_t h = 250;
    rectInstr rect = {{x, y, '/', background_location, 23718336}, h, w};
    textInstr text = {{{x + (w / 5), y + (h / 4), 0, "games/Menu/assets/Minecraft.ttf", 0x000000FF}, h, w}, "Play", 100};

    area_t area = {{(int)x, (int)y}, {(int)(x + w), (int)(y + h)}};
    if (_interactiveAreas.find(area) == _interactiveAreas.end())
        _interactiveAreas[area] = callback;

    q.push(rect);
    q.push(text);
    return q;
}

void MenuGame::_handle_click(point_t click)
{
    for (auto &[area, callback] : _interactiveAreas) {
        if (click.x >= area.a.x && click.x <= area.b.x &&
            click.y >= area.a.y && click.y <= area.b.y)
            callback();
    }
}

void MenuGame::update(std::queue<Event> events)
{
    while (!events.empty()) {
        point_t *click = std::get_if<point_t>(&events.front());
        if (click)
            _handle_click(*click);
        events.pop();
    }
}

std::queue<AnyInstruction> MenuGame::getGfxInstructions()
{
    std::queue<AnyInstruction> instructions;
    std::queue<AnyInstruction> button = createButton(MENU_SCREEN_W, MENU_SCREEN_H, "games/Menu/assets/button.jpg",
        [this](){_events.push(switchGamevent{std::string(LIB_PATH) + "arcade_snake.so"});});
    rectInstr background = {{0, 0, ' ', "games/Menu/assets/background.jpg"}, SCREEN_H, SCREEN_W};

    instructions.push((dimensionInstr){SCREEN_H, SCREEN_W});
    instructions.push(background);
    instructions = Utils::mergeQueues(instructions, button);

    return instructions;
}
