/*
** EPITECH PROJECT, 2026
** Display
** File description:
** Display header
*/

#pragma once

#include "IDisplay.hpp"
#include "gfx.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_test_font.h>
#include <DisplayVariable.hpp>
#include <cstdio>
#include <map>
#include <memory>


class SDL2 : public IDisplay {
public:
    SDL2();
    void init() override;
    void close() override;
    void clear() override;
    void render(std::queue<AnyInstruction>) override;
    std::queue<Event> pollEvents() override;
    ~SDL2();

private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _renderer;
    std::map<std::string, SDL_Surface> _surfaces;
    std::map<std::string, SDL_Texture*> _textures;
    std::queue<Event> _events;
    screen screenSize;
    void addEvents(SDL_KeyboardEvent &);
    void addEvents(SDL_MouseButtonEvent &);
    void DrawCircle(int x, int y, float radius);
    SDL_Color convert_rgba(int hexValue);
    void createTextureFromSurface(SDL_Surface &surface, std::string &assets,
        int x, int y, int w, int h);
    CommonKey sdlToCommonKey(SDL_Keycode sdlKey);
    void display_instruction(rectInstr &);
    void display_instruction(circleInstr &);
    void display_instruction(textInstr &);
    void display_instruction(dimensionInstr &);
};
