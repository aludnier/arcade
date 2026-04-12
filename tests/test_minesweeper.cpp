/*
** EPITECH PROJECT, 2026
** minesweeper
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <queue>
#include "MineSweeper.hpp"


static std::optional<std::string> get_tile_asset(MineSweeper::Game &game, int x, int y)
{
    auto gfx = game.getGfxInstructions();
    point_t coordinate;

    while (!gfx.empty()) {
        AnyInstruction inst = gfx.front();
        gfx.pop();
        rectInstr *rect = std::get_if<rectInstr>(&inst);
        if (!rect)
            continue;
        coordinate.x = rect->x / TILESIZE;
        coordinate.y = rect->y / TILESIZE;
        if (coordinate.x == x && coordinate.y == y){
            return rect->asset_location.value();
        }
    }
    return std::nullopt;
}

Test(GameMineSweeper, clicking_tile_reveals_it)
{
    MineSweeper::Game game;
    std::queue<Event> event;

    game.init();
    auto tile = get_tile_asset(game, 5, 5);
    cr_assert(tile.has_value());
    cr_assert_eq(tile, TILEASSET);

    event.push(point_t{5 * TILESIZE, 5 * TILESIZE});
    game.update(event);
    auto tile2 = get_tile_asset(game, 5, 5);
    cr_assert(tile2.has_value());
    cr_assert_neq(tile2, TILEASSET);
}

Test(GameMineSweeper, flag_sets_flag_asset)
{
    MineSweeper::Game game;
    std::queue<Event> events;

    game.init();
    events.push(CommonKey::F);
    game.update(events);
    events.pop();
    events.push(point_t{2 * TILESIZE, 2 * TILESIZE});
    game.update(events);
    auto asset = get_tile_asset(game, 2, 2);
    cr_assert(asset.has_value());
    cr_assert_eq(asset, FLAGASSET);
}

Test(GameMineSweeper, restart_resets_board)
{
    std::queue<Event> events;
    MineSweeper::Game game;

    game.init();
    events.push(point_t{0, 0});
    game.update(events);
    auto tile = get_tile_asset(game, 0, 0);
    cr_assert(tile.has_value());
    cr_assert_neq(tile, TILEASSET);
    events.push(CommonKey::R);
    game.update(events);
    tile = get_tile_asset(game, 0, 0);
    cr_assert(tile.has_value());
    cr_assert_eq(tile, TILEASSET);
}

Test(GameMineSweeper, flag_tile_do_not_reveals)
{
    MineSweeper::Game game;
    std::queue<Event> events;

    game.init();
    events.push(CommonKey::F);
    events.push(point_t{4 * TILESIZE, 4 * TILESIZE});
    events.push(CommonKey::F);
    events.push(point_t{4 * TILESIZE, 4 * TILESIZE});
    game.update(events);
    auto asset = get_tile_asset(game, 4, 4);
    cr_assert(asset.has_value());
    cr_assert_eq(asset.value(), FLAGASSET);
}
