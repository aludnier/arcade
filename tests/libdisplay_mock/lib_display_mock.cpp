/*
** EPITECH PROJECT, 2026
** tests
** File description:
** mock display library for unit tests
*/

#include "lib_display_mock.hpp"
#include "Keys.hpp"
#include <queue>

static int init_count = 0;
static int close_count = 0;
static int render_count = 0;
static int poll_count = 0;
static std::queue<Event> events;

void MockDisplay::init() { init_count++; }
void MockDisplay::close() { close_count++; }
void MockDisplay::clear() {}
void MockDisplay::render(std::queue<AnyInstruction>) { render_count++; }

std::queue<Event> MockDisplay::pollEvents()
{
    poll_count++;
    std::queue<Event> copy = events;
    while (!events.empty())
        events.pop();
    return copy;
}

LIB_TYPE getLibType() { return LIB_TYPE::DISPLAY; }
IDisplay *create() { return new MockDisplay(); }
int get_init_count() { return init_count; }
int get_close_count() { return close_count; }
int get_render_count() { return render_count; }
int get_poll_count() { return poll_count; }
void push_event_key(CommonKey event) { events.push(Event(event)); }
void clear_events()
{
    while (!events.empty())
        events.pop();
}
void reset_counts()
{
    init_count = 0;
    close_count = 0;
    render_count = 0;
    poll_count = 0;
}
