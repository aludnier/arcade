/*
** EPITECH PROJECT, 2026
** Display
** File description:
** Display header
*/

#pragma once

#include "IDisplay.hpp"
#include <SFML/Window/Mouse.hpp>
#include <cstdio>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "DisplayVariable.hpp"

class SFML : public IDisplay {
public:
    SFML();
    void init() override;
    void close() override;
    void clear() override;
    void render(std::queue<AnyInstruction>) override;
    std::queue<Event> pollEvents() override;
    ~SFML();

private:
    screen screenSize;
    sf::RenderWindow _window;
    std::queue<Event> _events;
    std::map<std::string, sf::Texture> _textures;
    sf::Color convert_rgba(int hex_color);
    void addEvents(sf::Keyboard::Key touch);
    void addEvents(sf::Event::MouseButtonEvent click);
    CommonKey sfmlToCommonKey(sf::Keyboard::Key);
    void create_texture(const int width, const int height);
    void display_instruction(rectInstr &rectangle);
    void display_instruction(circleInstr &circle);
    void display_instruction(textInstr &text);
    void display_instruction(dimensionInstr &text);
};
