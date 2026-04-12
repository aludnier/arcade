/*
** EPITECH PROJECT, 2026
** GFX
** File description:
** GFX header
*/

#pragma once

#include <cstddef>
#include "Keys.hpp"
#include "shape.hpp"
#include <optional>
#include <variant>

typedef struct gfx_s gfx_instr_t;
typedef struct point_s {
    int x;
    int y;
} point_t;

typedef struct area_s {
    point_t a;
    point_t b;
    bool operator<(const struct area_s &o) const {
        if (a.x != o.a.x) return a.x < o.a.x;
        if (a.y != o.a.y) return a.y < o.a.y;
        if (b.x != o.b.x) return b.x < o.b.x;
        return b.y < o.b.y;
    }
} area_t;

struct GfxInstruction {
    size_t x;
    size_t y;
    char txt;
    std::optional<std::string> asset_location;
    size_t color_hex;
};

struct rectInstr : public GfxInstruction {
    size_t h;
    size_t w;
};

struct circleInstr : public GfxInstruction {
    size_t radius;
};

struct  textInstr : public rectInstr {
    std::string text;
    size_t fontSize;
};

struct dimensionInstr {
    size_t h;
    size_t w;
};

using Event = std::variant<CommonKey, point_t>;

using AnyInstruction = std::variant<rectInstr, circleInstr, textInstr, dimensionInstr>;
