#include "SDL2.hpp"
#include "DisplayVariable.hpp"
#include "IDisplay.hpp"
#include "gfx.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <cstddef>
#include <cstdio>
#include <memory>
#include <numbers>
#include <ostream>
#include <stdexcept>
#include <variant>
#include <iostream>
#include <Keys.hpp>

extern "C" IDisplay *create()
{
    return new SDL2();
}

SDL2::SDL2() :
    _window(std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(
        SDL_CreateWindow("SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_W,
        SCREEN_H,
        SDL_WINDOW_RESIZABLE), SDL_DestroyWindow)),
        _renderer(
            std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>
            (SDL_CreateRenderer(
        _window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer)),
        _textures({}), _surfaces({})
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw std::runtime_error(SDL_GetError());
    if (TTF_Init() != 0)
        throw std::runtime_error(SDL_GetError());
    _events = {};
}

void SDL2::init()
{
}

void SDL2::close()
{
    for (auto &elem : _textures)
        SDL_DestroyTexture(elem.second);
        SDL_Quit();
}

void SDL2::clear()
{
    SDL_RenderClear(_renderer.get());
}

SDL_Color SDL2::convert_rgba(int hex_color)
{
    SDL_Color color;

    color.r = ((hex_color >> 24) & 0xFF) ;
    color.g = ((hex_color >> 16) & 0xFF);
    color.b = ((hex_color >> 8) & 0xFF);
    color.a = ((hex_color) & 0xFF);
    return color;
}

void SDL2::createTextureFromSurface(SDL_Surface &surface, std::string &assets, int x, int y, int w, int h)
{
    if (!_textures.contains(assets)) {
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(_renderer.get(), &surface);
        if (!textTexture) {
            std::cout << "TEXTURE FAIL" << std::endl;
            throw std::runtime_error(SDL_GetError());
        }
        _textures[assets] = std::move(textTexture);
    }
    SDL_Rect textRect = {x, y, w * screenSize.ratio, h * screenSize.ratio};
    SDL_RenderCopy(_renderer.get(), _textures[assets], NULL, &textRect);
}

void SDL2::display_instruction(rectInstr &rectangle)
{
    SDL_Color color = convert_rgba(rectangle.color_hex);
    SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_Rect rect = {(int)rectangle.x, 
        (int)rectangle.y, (int)rectangle.w, (int)rectangle.h};
    SDL_RenderFillRect(_renderer.get(), &rect);
    if (!rectangle.asset_location->empty()) {
        if (!_surfaces.contains(rectangle.asset_location.value())) {
            _surfaces[rectangle.asset_location.value()] =
                *IMG_Load(rectangle.asset_location.value().c_str());   
        }
        createTextureFromSurface(
        _surfaces[rectangle.asset_location.value()],
        rectangle.asset_location.value(),
        rect.x , rect.y, rect.w, rect.h);
    }
}

void SDL2::DrawCircle(int x, int y, float radius)
{
    double pi = std::numbers::pi;
    int precision = 100;
    double step = pi / (double)(precision - 1);

    for (int i = 0; i < precision; i++) {
        float x1 = cos(-i * step) * radius + x;
        float y1 = sin(-i * step) * radius + y;
        float x2 = cos(i * step) * radius + x;
        float y2 = sin(i * step) * radius + y;
        SDL_RenderDrawLine(_renderer.get(), x1, y1, x2, y2);
    }
}

void SDL2::display_instruction(circleInstr &circle)
{
    SDL_Color color = convert_rgba(circle.color_hex);

    SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, color.a);
    DrawCircle(
        circle.x, 
        circle.y, 
        circle.radius * screenSize.ratio);
}

void SDL2::display_instruction(textInstr &text)
{
    SDL_Color color = convert_rgba(text.color_hex);

    if (!text.asset_location->empty()) {
        TTF_Font *font = TTF_OpenFont(text.asset_location->c_str(), text.fontSize);
        if (!font) {
            throw std::runtime_error(SDL_GetError());
        }
        if (!_surfaces.contains(text.asset_location.value().c_str())) {
            _surfaces[text.asset_location.value() + text.text] =
                *TTF_RenderText_Blended(font, text.text.c_str(), color);
        }
        std::string asset = text.asset_location.value() + text.text;
        createTextureFromSurface(
            _surfaces[text.asset_location.value() + text.text],
            asset,
            text.x * screenSize.ratio,
            text.y * screenSize.ratio,
            text.w * screenSize.ratio,
            text.h * screenSize.ratio);
        TTF_CloseFont(font);
    }
}

void SDL2::display_instruction(dimensionInstr &dimension)
{
    screenSize.h = dimension.h;
    screenSize.w = dimension.w;
    screenSize.ratio = (SCREEN_H / dimension.h);
}

void SDL2::render(std::queue<AnyInstruction> instructions)
{
    SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(_renderer.get());

    while (!instructions.empty()) {
        std::visit([this](auto &arg){ display_instruction(arg); },
        instructions.front());
        instructions.pop();
    }
    SDL_RenderPresent(_renderer.get());
}


CommonKey SDL2::sdlToCommonKey(SDL_Keycode sdlKey)
    {
        for (const auto& [commonKey, trio] : KEY_MAP) {
            if (std::get<0>(trio) == sdlKey)
                return commonKey;
        }
        return CommonKey::UNKNOWN;
}


void SDL2::addEvents(SDL_KeyboardEvent &touch)
{
    int key = touch.keysym.sym;
    Event event = sdlToCommonKey(key);

    _events.push(event);
}

void SDL2::addEvents(SDL_MouseButtonEvent &click)
{
    if (click.button) {
        point_t point = {click.x, click.y};
        Event event = point;
        printf("X: %d Y: %d\n", point.x, point.y);
        _events.push(event);
    }
}

std::queue<Event> SDL2::pollEvents()
{
    SDL_Event sdl_event = {0};

    _events = {};
    while (SDL_PollEvent(&sdl_event)) {
        if (sdl_event.type == SDL_KEYDOWN)
            addEvents(sdl_event.key);
        if (sdl_event.type == SDL_MOUSEBUTTONDOWN)
            addEvents(sdl_event.button);
        if (sdl_event.type == SDL_QUIT) {
            this->close();
        }
    }
    return _events;
}

extern "C" LIB_TYPE getLibType()
{
    return DISPLAY;
}

SDL2::~SDL2()
{
    SDL_Quit();
}
