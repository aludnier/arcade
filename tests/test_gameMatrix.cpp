/*
** EPITECH PROJECT, 2026
** tests
** File description:
** tests for GameMatrix
*/

#include <criterion/criterion.h>
#include <exception>
#include "GameMatrix.hpp"
#include "gfx.hpp"

Test(GameMatrix, constructor_initializes_matrix)
{
    GameMatrix<int> matrix(5, 4, 0, 32);

    for (std::size_t y = 0; y < 4; ++y) {
        for (std::size_t x = 0; x < 5; ++x) {
            cr_assert_eq(matrix(x, y), 0);
        }
    }
}

Test(GameMatrix, operator_sets_and_gets_value)
{
    GameMatrix<int> matrix(5, 4, 0, 32);
    matrix(2, 1) = 42;
    cr_assert_eq(matrix(2, 1), 42);
}

Test(GameMatrix, operator_throws_on_invalid_index)
{
    GameMatrix<int> matrix(5, 4, 0, 32);
    cr_assert_throw(matrix(10, 0), GameMatrix<int>::SizeError);
    cr_assert_throw(matrix(0, 10), GameMatrix<int>::SizeError);
}

Test(GameMatrix, onScreenPoint_modifies_correct_cell)
{
    GameMatrix<int> matrix(5, 4, 0, 32);
    point_t click{50, 70};
    matrix.onTileClick(click, [](int &cell){ cell = 99; });

    std::size_t expectedX = click.x / 32;
    std::size_t expectedY = click.y / 32;
    cr_assert_eq(matrix(expectedX, expectedY), 99);
}

Test(GameMatrix, matrixToGFX_creates_correct_number_of_tiles_color)
{
    GameMatrix<int> matrix(5, 4, 0, 32);
    auto &stack = matrix.matrixToGFX(0xFF, 'A');
    cr_assert_eq(stack.size(), 20);
    
    rectInstr top = stack.top();
    cr_assert_eq(top.txt, 'A');
    cr_assert_eq(top.color_hex, 0xFF);
    cr_assert_eq(top.w, 32);
    cr_assert_eq(top.h, 32);
}

Test(GameMatrix, matrixToGFX_creates_correct_number_of_tiles_asset)
{
    GameMatrix<int> matrix(5, 4, 0, 32);
    auto &stack = matrix.matrixToGFX("asset.png", 'B');
    cr_assert_eq(stack.size(), 20);

    rectInstr top = stack.top();
    cr_assert(top.asset_location.has_value());
    cr_assert_str_eq(top.asset_location.value().c_str(), "asset.png");
    cr_assert_eq(top.txt, 'B');
}

Test(GameMatrix, resize_changes_matrix_size)
{
    GameMatrix<int> matrix(5, 4, 0, 32);
    matrix.resize(6, 5);

    cr_assert_eq(matrix(5, 4), 0);
    cr_assert_throw(matrix(6, 4), GameMatrix<int>::SizeError);
    cr_assert_throw(matrix(5, 5), GameMatrix<int>::SizeError);
}