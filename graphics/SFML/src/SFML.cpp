#include "DisplayVariable.hpp"
#include "IDisplay.hpp"
#include "SFML.hpp"
#include "gfx.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <ostream>
#include <variant>

extern "C" IDisplay *create()
{
    return new SFML();
}

sf::Color SFML::convert_rgba(int hex_color)
{
    sf::Color color;

    color.r = ((hex_color >> 24) & 0xFF) ;
    color.g = ((hex_color >> 16) & 0xFF);
    color.b = ((hex_color >> 8) & 0xFF);
    color.a = 255 - ((hex_color) & 0xFF);
    return color;
}

SFML::SFML() : _window(sf::VideoMode(SCREEN_W, SCREEN_H), 
        "SFML",
        sf::Style::Default)
{
}

void SFML::init()
{
    _window.setFramerateLimit(FRAMELIMITS);
    _window.clear(sf::Color::Blue);
}

void SFML::close()
{
    _window.close();
}

void SFML::clear()
{
}

void SFML::display_instruction(rectInstr &rectangle)
{
    sf::RectangleShape rect(sf::Vector2f(rectangle.w * screenSize.ratio, rectangle.h * screenSize.ratio));
    rect.setPosition(sf::Vector2f(rectangle.x * screenSize.ratio, rectangle.y * screenSize.ratio));

    if (!rectangle.asset_location->empty()) {
        if (!_textures.contains(rectangle.asset_location.value())) {
            _textures.emplace();
            _textures[rectangle.asset_location.value()].loadFromFile(rectangle.asset_location->c_str());
        }
        rect.setTexture(&_textures[rectangle.asset_location.value()]);
        rect.setTextureRect(sf::IntRect(0, 0,
            _textures[rectangle.asset_location.value()].getSize().x,
            _textures[rectangle.asset_location.value()].getSize().y));
    }
    else
        rect.setFillColor(convert_rgba(rectangle.color_hex));
    _window.draw(rect);
}

void SFML::display_instruction(circleInstr &circle)
{
    sf::CircleShape circ(circle.radius);
    circ.setFillColor(convert_rgba(circle.color_hex));
    circ.setPosition(sf::Vector2f(circle.x, circle.y));

    if (!circle.asset_location->empty()) {
        if (_textures.contains(circle.asset_location.value())) {
            _textures.emplace();
            _textures[circle.asset_location.value()].loadFromFile(circle.asset_location->c_str());
        }
        circ.setTexture(&_textures[circle.asset_location.value()]);
        circ.setTextureRect(sf::IntRect(0, 0,
            _textures[circle.asset_location.value()].getSize().x,
            _textures[circle.asset_location.value()].getSize().y));
    }
    _window.draw(circ);
}

void SFML::display_instruction(textInstr &text)
{
    sf::Font font;

    font.loadFromFile(text.asset_location->c_str());
    sf::Text Text(text.text, font, text.fontSize);
    Text.setFillColor(convert_rgba(text.color_hex));
    Text.setPosition(sf::Vector2f(text.x, text.y));
    _window.draw(Text);
}

void SFML::display_instruction(dimensionInstr &dimension)
{
    screenSize.w = dimension.w;
    screenSize.h = dimension.h;
    screenSize.ratio = (800 / dimension.h);
}

void SFML::render(std::queue<AnyInstruction> instructions)
{
    _window.clear(sf::Color::Transparent);
    while (!instructions.empty()) {
        std::visit(
            [this](auto &arg) { display_instruction(arg); },
        instructions.front());
        instructions.pop();
    }
    _window.display();
    _textures.clear();
}

CommonKey SFML::sfmlToCommonKey(sf::Keyboard::Key key)
{
    for (const auto& [commonKey, trio] : KEY_MAP) {
        if (std::get<1>(trio) == key)
            return commonKey;
    }
    return CommonKey::UNKNOWN;
}

void SFML::addEvents(sf::Keyboard::Key touch)
{
    Event event = sfmlToCommonKey(touch);

    _events.push(event);
}

void SFML::addEvents(sf::Event::MouseButtonEvent click)
{
    point_t point = {click.x, click.y};
    Event event = point;

    printf("X: %d Y: %d\n", point.x, point.y);
    _events.push(event);
}

std::queue<Event> SFML::pollEvents()
{
    sf::Event event;

    _events = {};
    if  (_window.pollEvent(event)) {
        if ((event.type == sf::Event::KeyPressed))
            addEvents(sf::Keyboard::localize(event.key.scancode));
        sf::Mouse::getPosition();
        if ((event.type == sf::Event::MouseButtonPressed))
            addEvents(event.mouseButton);
        if (event.type == sf::Event::Closed)
            this->close();
    }
    return _events;
}

extern "C" LIB_TYPE getLibType()
{
    return DISPLAY;
}

SFML::~SFML()
{
}
