#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <cstddef>
#include <cstdio>
#include "Keys.hpp"
#include "Snake.hpp"
#include "gfx.hpp"

Test(GameSnake, shark_fish_collision)
{
    Snake::GameSnake snake;
    snake.init();
    snake.setShark();
    snake.setFish();

    auto shark = snake.getShark();
    auto fish = snake.getFish();
    auto shark_size = shark.size();

    fish.x = shark.front().x;
    fish.y = shark.front().y;
    (void)fish;
    cr_assert_eq(5, (shark_size + 1));
}

Test(GameSnake, shark_wall_collision)
{
    Snake::GameSnake snake;
    snake.setShark();
    snake.init();

    auto shark = snake.getShark();
    auto fish = snake.getFish();
    auto wall = snake.getGames();

    fish.x = shark.front().x;
    fish.y = shark.front().y;
    (void)fish;
    shark.front().x = wall[Snake::WALL].front().x;
    shark.front().y = wall[Snake::WALL].front().y;
    cr_assert_eq(4, shark.size());
}

Test(GameSnake, move_shark_up)
{
    Event event = CommonKey::UP;
    std::queue<Event> events = {};
    Snake::GameSnake snake;
    snake.init();
    snake.setShark();
    events.push(event);
    auto shark = snake.getShark();
    size_t y = shark.front().y;
    snake.update(events);
    shark = snake.getShark();
    cr_assert_eq((y), shark.front().y);
}

Test(GameSnake, move_shark_down)
{
    Event event = CommonKey::DOWN;
    std::queue<Event> events = {};
    Snake::GameSnake snake;
    snake.init();
    snake.setShark();
    events.push(event);
    auto shark = snake.getShark();
    size_t y = shark.front().y;
    snake.update(events);
    shark = snake.getShark();
    cr_assert_eq((y), shark.front().y);
}

