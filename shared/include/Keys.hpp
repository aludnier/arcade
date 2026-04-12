/*
** EPITECH PROJECT, 2026
** keys
** File description:
** keys
*/

#include <unordered_map>
#include <tuple>
#include <SDL2/SDL_keycode.h>
#include <SFML/Window/Keyboard.hpp>
#include <ncurses.h>

#pragma once

enum class CommonKey : int {
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
    NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9,
    TAB, BACKSPACE, ESCAPE, ENTER,
    UP, DOWN, LEFT, RIGHT,
    UNKNOWN
};

using KeyTrio = std::tuple<SDL_Keycode, sf::Keyboard::Key, int>;
static const std::unordered_map<CommonKey, KeyTrio> KEY_MAP = {
    {CommonKey::A,  {SDLK_a, sf::Keyboard::A, 'a'}},
    {CommonKey::B,  {SDLK_b, sf::Keyboard::B, 'b'}},
    {CommonKey::C,  {SDLK_c, sf::Keyboard::C, 'c'}},
    {CommonKey::D,  {SDLK_d, sf::Keyboard::D, 'd'}},
    {CommonKey::E,  {SDLK_e, sf::Keyboard::E, 'e'}},
    {CommonKey::F,  {SDLK_f, sf::Keyboard::F, 'f'}},
    {CommonKey::G,  {SDLK_g, sf::Keyboard::G, 'g'}},
    {CommonKey::H,  {SDLK_h, sf::Keyboard::H, 'h'}},
    {CommonKey::I,  {SDLK_i, sf::Keyboard::I, 'i'}},
    {CommonKey::J,  {SDLK_j, sf::Keyboard::J, 'j'}},
    {CommonKey::K,  {SDLK_k, sf::Keyboard::K, 'k'}},
    {CommonKey::L,  {SDLK_l, sf::Keyboard::L, 'l'}},
    {CommonKey::M,  {SDLK_m, sf::Keyboard::M, 'm'}},
    {CommonKey::N,  {SDLK_n, sf::Keyboard::N, 'n'}},
    {CommonKey::O,  {SDLK_o, sf::Keyboard::O, 'o'}},
    {CommonKey::P,  {SDLK_p, sf::Keyboard::P, 'p'}},
    {CommonKey::Q,  {SDLK_q, sf::Keyboard::Q, 'q'}},
    {CommonKey::R,  {SDLK_r, sf::Keyboard::R, 'r'}},
    {CommonKey::S,  {SDLK_s, sf::Keyboard::S, 's'}},
    {CommonKey::T,  {SDLK_t, sf::Keyboard::T, 't'}},
    {CommonKey::U,  {SDLK_u, sf::Keyboard::U, 'u'}},
    {CommonKey::V,  {SDLK_v, sf::Keyboard::V, 'v'}},
    {CommonKey::W,  {SDLK_w, sf::Keyboard::W, 'w'}},
    {CommonKey::X,  {SDLK_x, sf::Keyboard::X, 'x'}},
    {CommonKey::Y,  {SDLK_y, sf::Keyboard::Y, 'y'}},
    {CommonKey::Z,  {SDLK_z, sf::Keyboard::Z, 'z'}},
    {CommonKey::NUM0, {SDLK_0, sf::Keyboard::Num0, '0'}},
    {CommonKey::NUM1, {SDLK_1, sf::Keyboard::Num1, '1'}},
    {CommonKey::NUM2, {SDLK_2, sf::Keyboard::Num2, '2'}},
    {CommonKey::NUM3, {SDLK_3, sf::Keyboard::Num3, '3'}},
    {CommonKey::NUM4, {SDLK_4, sf::Keyboard::Num4, '4'}},
    {CommonKey::NUM5, {SDLK_5, sf::Keyboard::Num5, '5'}},
    {CommonKey::NUM6, {SDLK_6, sf::Keyboard::Num6, '6'}},
    {CommonKey::NUM7, {SDLK_7, sf::Keyboard::Num7, '7'}},
    {CommonKey::NUM8, {SDLK_8, sf::Keyboard::Num8, '8'}},
    {CommonKey::NUM9, {SDLK_9, sf::Keyboard::Num9, '9'}},
    {CommonKey::NUMPAD0, {SDLK_KP_0, sf::Keyboard::Numpad0, '0'}},
    {CommonKey::NUMPAD1, {SDLK_KP_1, sf::Keyboard::Numpad1, '1'}},
    {CommonKey::NUMPAD2, {SDLK_KP_2, sf::Keyboard::Numpad2, '2'}},
    {CommonKey::NUMPAD3, {SDLK_KP_3, sf::Keyboard::Numpad3, '3'}},
    {CommonKey::NUMPAD4, {SDLK_KP_4, sf::Keyboard::Numpad4, '4'}},
    {CommonKey::NUMPAD5, {SDLK_KP_5, sf::Keyboard::Numpad5, '5'}},
    {CommonKey::NUMPAD6, {SDLK_KP_6, sf::Keyboard::Numpad6, '6'}},
    {CommonKey::NUMPAD7, {SDLK_KP_7, sf::Keyboard::Numpad7, '7'}},
    {CommonKey::NUMPAD8, {SDLK_KP_8, sf::Keyboard::Numpad8, '8'}},
    {CommonKey::NUMPAD9, {SDLK_KP_9, sf::Keyboard::Numpad9, '9'}},
    {CommonKey::TAB, {SDLK_TAB, sf::Keyboard::Tab, 9}},
    {CommonKey::BACKSPACE, {SDLK_BACKSPACE, sf::Keyboard::Backspace, KEY_BACKSPACE}},
    {CommonKey::ESCAPE, {SDLK_ESCAPE, sf::Keyboard::Escape, 27}},
    {CommonKey::ENTER, {SDLK_RETURN, sf::Keyboard::Return, 10}},
    {CommonKey::UP, {SDLK_UP, sf::Keyboard::Up, KEY_UP}},
    {CommonKey::DOWN, {SDLK_DOWN, sf::Keyboard::Down, KEY_DOWN}},
    {CommonKey::LEFT, {SDLK_LEFT, sf::Keyboard::Left, KEY_LEFT}},
    {CommonKey::RIGHT, {SDLK_RIGHT, sf::Keyboard::Right, KEY_RIGHT}},
    {CommonKey::UNKNOWN, {SDLK_UNKNOWN, sf::Keyboard::Unknown, ERR}}
};
