/*
** EPITECH PROJECT, 2026
** Display
** File description:
** Display header
*/

#pragma once

#include "IDisplay.hpp"
#include "DlLoader.hpp"
#include <memory>
#include <queue>

class Display : public IDisplay {
    public:
        Display(const std::string &lib_location);
        Display &operator=(Display &&other) noexcept;
        ~Display();

        void init() override;
        void close() override;
        void clear() override;
        void reset();
        void render(std::queue<AnyInstruction>) override;
        std::queue<Event> pollEvents() override;

    private:
        DlLoader _lib;
        std::unique_ptr<IDisplay> _self;
};
