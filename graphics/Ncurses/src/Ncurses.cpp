/*
** EPITECH PROJECT, 2026
** Ncurses
** File description:
** Ncurses
*/

#include <ncurses.h>
#include "Ncurses.hpp"
#include "DisplayVariable.hpp"
#include "Keys.hpp"
#include "gfx.hpp"
#include <cmath>
#include <variant>

extern "C" IDisplay *create()
{
    return new Ncurses();
}

extern "C" LIB_TYPE getLibType()
{
    return DISPLAY;
}

Ncurses::~Ncurses()
{
}

Ncurses::Ncurses() : _screenSize()
{
    _screenSize.h = NCURSES_H;
    _screenSize.w = NCURSES_W;
    _screenSize.ratio = 1;
}

void Ncurses::init()
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS, nullptr);
}

void Ncurses::close()
{
    endwin();
}

void Ncurses::clear()
{
    ::clear();
}

void Ncurses::render(std::queue<AnyInstruction> instructions)
{
    ::clear();
    _format_instructions(instructions);

    while (!instructions.empty()) {
        std::visit([this](auto &arg) {
            render_instruction(arg); 
        }, instructions.front());
        instructions.pop();
    }
    refresh();
}

std::queue<Event> Ncurses::pollEvents()
{
    std::queue<Event> events;
    int ch;

    while ((ch = getch()) != ERR) {
        if (ch == KEY_MOUSE) {
            MEVENT mouse_event;
            if (getmouse(&mouse_event) == OK && mouse_event.bstate & BUTTON1_CLICKED)
                _handle_click(mouse_event.x, mouse_event.y, events);
            continue;
        }
        for (const auto &[commonKey, tuple] : KEY_MAP) {
            if (std::get<2>(tuple) == ch) {
                events.push(commonKey);
                break;
            }
        }
    }
    return events;
}

void Ncurses::_format_instructions(std::queue<AnyInstruction> &instructions)
{
    std::queue<AnyInstruction> tmp;

    while (!instructions.empty()) {
        AnyInstruction instr = instructions.front();
        instructions.pop();

        std::visit([this](auto &arg) {
            if constexpr (requires { arg.w; })
                arg.w /= 2;
            if constexpr (requires { arg.w; arg.x; })
                if (arg.w > 0 && arg.h > 0) {
                    _cell_w = arg.w;
                    _cell_h = arg.h;
                }
        }, instr);

        tmp.push(instr);
    }
    instructions = std::move(tmp);
}

// ===== render =====

void Ncurses::render_instruction(rectInstr &gfx)
{
    if (gfx.w == 0 || gfx.h == 0)
        return;
    mvaddch(gfx.y / gfx.h, gfx.x / gfx.w, gfx.txt);
}

void Ncurses::render_instruction(circleInstr &gfx)
{
    int cx = static_cast<int>(gfx.x / _screenSize.ratio);
    int cy = static_cast<int>(gfx.y / _screenSize.ratio);
    int r  = static_cast<int>(gfx.radius / _screenSize.ratio);

    for (double angle = 0; angle < 2 * M_PI; angle += 0.1) {
        mvaddch(cy + (int)std::round(std::sin(angle) * r),
                cx + (int)std::round(std::cos(angle) * r),
                gfx.txt);
    }
}

void Ncurses::render_instruction(textInstr &gfx)
{
    if (gfx.w == 0 || gfx.h == 0)
        return;
    mvprintw(gfx.y / gfx.h, gfx.x / gfx.w, "%s", gfx.text.c_str());
}

void Ncurses::render_instruction(dimensionInstr &gfx)
{
    _screenSize.h = gfx.h;
    _screenSize.w = gfx.w;
    _screenSize.ratio = (gfx.h > 0) ? gfx.h : 1;
}

void Ncurses::_handle_click(int x, int y, std::queue<Event> &events)
{
    point_t click = {
        x * (int)_cell_w + (int)(_cell_w / 2),
        y * (int)_cell_h + (int)(_cell_h / 2)
    };
    events.push(click);
}
