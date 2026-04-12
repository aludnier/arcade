/*
** EPITECH PROJECT, 2026
** Utils
** File description:
** Utils for menu game
*/

#include "MenuUtils.hpp"
#include "Utils.hpp"
#include "gfx.hpp"
#include <cstddef>
#include <functional>
#include <queue>

std::queue<AnyInstruction> MenuUtils::createButton(size_t x, size_t y, std::string background_location, std::function<void()> callback)
{
    std::queue<AnyInstruction> q;
    size_t w = 400;
    size_t h = 250;
    rectInstr rect = {{x, y, '/', background_location, 23718336}, h, w};
    textInstr text = {{{x + (w / 5), y + (h / 4), 0, "games/Menu/assets/Minecraft.ttf", 0x000000FF}, h / 2, w / 2}, "Play", 100};

    q.push(rect);
    q.push(text);
    return q;
}
