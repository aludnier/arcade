/*
** EPITECH PROJECT, 2026
** Ncurses
** File description:
** Ncurses
*/

#include <ncurses.h>
#define NCURSES_H 40
#define NCURSES_W 40

#include "DisplayVariable.hpp"
#include "IDisplay.hpp"
#include "gfx.hpp"
#include <queue>

class Ncurses : public IDisplay {
    public:
        Ncurses();
        ~Ncurses() override;

        void init() override;
        void close() override;
        void clear() override;
        void render(std::queue<AnyInstruction>) override;
        std::queue<Event> pollEvents() override;

        void render_instruction(rectInstr &);
        void render_instruction(circleInstr &);
        void render_instruction(textInstr &);
        void render_instruction(dimensionInstr &);

    private:
        screen _screenSize;
        size_t _cell_w = 1;
        size_t _cell_h = 1;

        void _format_instructions(std::queue<AnyInstruction>&);
        void _handle_click(int x, int y, std::queue<Event> &events);
};
