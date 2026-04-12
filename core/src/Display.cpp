/*
** EPITECH PROJECT, 2026
** Display
** File description:
** Display declaration
*/

#include "Display.hpp"
#include "IDisplay.hpp"
#include "IGame.hpp"
#include <functional>
#include <memory>
#include <ostream>
#include <iostream>
#include <stdexcept>

Display::Display(const std::string &_lib_location) : _lib(_lib_location)
{
    _lib.load();

    std::function<LIB_TYPE()> getLibType = reinterpret_cast<LIB_TYPE(*)()>(_lib.sym("getLibType"));
    std::function<IDisplay*()> create = reinterpret_cast<IDisplay*(*)()>(_lib.sym("create"));

    if (getLibType() != LIB_TYPE::DISPLAY)
        throw std::runtime_error("Error: " + _lib_location + " not a graphical library\n");

    _self = std::unique_ptr<IDisplay>(create());
    _self->init();
}

Display &Display::operator=(Display &&other) noexcept
{
    if (this != &other) {
        _self.reset();
        _lib = std::move(other._lib);
        _self = std::move(other._self);
    }
    return *this;
}

Display::~Display()
{
    if (_lib.is_loaded())
        close();
}

void Display::init()
{
    _self->init();
}

void Display::close()
{
    if (_self) {
        _self->close();
        _self.reset();
    }
}

void Display::clear()
{
    _self->clear();
}

void Display::render(std::queue<AnyInstruction> instructions)
{
    _self->render(instructions);
}

void Display::reset()
{
    _self.reset();
}

std::queue<Event> Display::pollEvents()
{
    return _self->pollEvents();
}
