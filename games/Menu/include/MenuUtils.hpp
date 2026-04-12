/*
** EPITECH PROJECT, 2026
** Utils
** File description:
** Utils for Menu game only
*/

#include "gfx.hpp"
#include <functional>
#include <queue>

class MenuUtils {
    public:
        static std::queue<AnyInstruction> createButton(size_t x, size_t y, std::string, std::function<void()>);
};
