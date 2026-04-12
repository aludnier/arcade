/*
** EPITECH PROJECT, 2026
** tests
** File description:
** mock display library header
*/

#pragma once

#include "IDisplay.hpp"
#include "Keys.hpp"

#define EXPORT extern "C"

class MockDisplay : public IDisplay {
public:
    void init() override;
    void close() override;
    void clear() override;
    void render(std::queue<AnyInstruction>) override;
    std::queue<Event> pollEvents() override;
};

EXPORT {
    LIB_TYPE getLibType();
    IDisplay *create();
    int get_init_count();
    int get_close_count();
    int get_render_count();
    int get_poll_count();
    void push_event_key(CommonKey event);
    void clear_events();
    void reset_counts();
}
