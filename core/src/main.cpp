/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "Arcade.hpp"
#include <exception>
#include <iostream>

int main(int ac, char **av)
{
    if (ac < 2)
        return EXIT_FAIL;
    try {
        Core arcade(av[1], MENU_GAME);
        arcade.run();
    } catch (const std::exception &e) {
        std::cerr << e.what();
        return EXIT_FAIL;
    }
    return EXIT_SUCCESS;
}
