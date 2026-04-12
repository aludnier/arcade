cmake_minimum_required(VERSION 3.13)
project(arcade)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ..)
set(LIBRARY_OUTPUT_PATH ../lib)

set(SFML_INCLUDE /opt/sfml2/include)

option(DEBUG "Compile with -g3" OFF)

include_directories(${PROJECT_SOURCE_DIR}/shared/include)
include_directories(${SFML_INCLUDE})

# ===== CORE / SHARED =====

set(SHARED
    shared/src/DlLoader.cpp
    shared/src/Utils.cpp
)

set(CORE
    ${SHARED}
    core/src/Display.cpp
    core/src/Game.cpp
    core/src/Arcade.cpp
)

add_executable(arcade ${CORE} core/src/main.cpp)
target_include_directories(arcade PRIVATE
    ${PROJECT_SOURCE_DIR}/core/include
)

target_compile_options(arcade PRIVATE
    -Wall
    -Wextra
)

target_compile_definitions(arcade PRIVATE
    LIB_PATH="${CMAKE_SOURCE_DIR}/libs/"
)

if(DEBUG)
    target_compile_options(arcade PRIVATE -g3)
endif()

# ===== Libraries =====
# === SDL2 ===
set(SDL2
    ${SHARED}
    graphics/SDL2/src/SDL2.cpp
)

add_library(arcade_sdl2 SHARED ${SDL2})

target_include_directories(arcade_sdl2 PRIVATE
    ${PROJECT_SOURCE_DIR}/graphics/SDL2/include
)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

target_link_libraries(arcade_sdl2 PRIVATE
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
    SDL2_image::SDL2_image
)

set_target_properties(arcade_sdl2 PROPERTIES PREFIX "")


# === SFML ===
set(SFML
    ${SHARED}
    graphics/SFML/src/SFML.cpp
)

add_library(arcade_sfml SHARED ${SFML})

target_include_directories(arcade_sfml PRIVATE
    ${PROJECT_SOURCE_DIR}/graphics/SFML/include
)

find_package(SFML COMPONENTS graphics audio REQUIRED)

target_link_libraries(arcade_sfml sfml-graphics sfml-audio)

set_target_properties(arcade_sfml PROPERTIES PREFIX "")


# === Ncurses ===
set(NCURSES_SRC
    ${SHARED}
    graphics/Ncurses/src/Ncurses.cpp;
)

add_library(arcade_ncurses SHARED ${NCURSES_SRC})

target_include_directories(arcade_ncurses PRIVATE
    ${PROJECT_SOURCE_DIR}/graphics/Ncurses/include
)

find_package(Curses REQUIRED)

target_link_libraries(arcade_ncurses PRIVATE ncurses)

set_target_properties(arcade_ncurses PROPERTIES PREFIX "")


# ===== Games =====
# === Snake ===
set(SNAKE
    ${SHARED}
    games/Snake/src/Snake.cpp
)

add_library(arcade_snake SHARED ${SNAKE})

target_include_directories(arcade_snake PRIVATE
    ${PROJECT_SOURCE_DIR}/games/Snake/include
)

set_target_properties(arcade_snake PROPERTIES PREFIX "")

# ===== MineSweeper =====
SET(MINESWEEPER
    ${SHARED}
    games/MineSweeper/src/MineSweeper.cpp
)

add_library(arcade_minesweeper SHARED
    ${MINESWEEPER}
    games/MineSweeper/src/symEntry.cpp
)

target_include_directories(arcade_minesweeper PRIVATE
    ${PROJECT_SOURCE_DIR}/games/MineSweeper/include
)

set_target_properties(arcade_minesweeper PROPERTIES PREFIX "")

# === Menu ===
set(MENU
    ${SHARED}
    games/Menu/src/Menu.cpp
)

add_library(arcade_menu SHARED ${MENU})

target_include_directories(arcade_menu PRIVATE
    ${PROJECT_SOURCE_DIR}/games/Menu/include
)

target_compile_definitions(arcade_menu PRIVATE
    LIB_PATH="${CMAKE_SOURCE_DIR}/libs/"
)

set_target_properties(arcade_menu PROPERTIES PREFIX "")



# ======

if(DEBUG)
    target_compile_options(arcade PRIVATE -g3)
endif()

# ===== Tests =====

enable_testing()

add_executable(test_binary
    ${CORE}
    ${SNAKE}
    ${MINESWEEPER}
    tests/test_void.cpp
    tests/test_shared.cpp
    tests/test_core.cpp
    tests/test_gameMatrix.cpp
    tests/test_snake.cpp
    tests/test_minesweeper.cpp
)

target_include_directories(test_binary
    PRIVATE
        ${PROJECT_SOURCE_DIR}/core/include
        ${PROJECT_SOURCE_DIR}/games/Snake/include
        ${PROJECT_SOURCE_DIR}/games/MineSweeper/include
)

add_library(test_lib SHARED tests/libtest/lib_test.cpp)
target_include_directories(test_lib
    PRIVATE
        ${PROJECT_SOURCE_DIR}/libtest/
)

add_library(game_mock SHARED tests/libgame_mock/lib_game_mock.cpp)
target_include_directories(game_mock PRIVATE
    ${PROJECT_SOURCE_DIR}/tests/libgame_mock
)

add_library(display_mock SHARED tests/libdisplay_mock/lib_display_mock.cpp)
target_include_directories(display_mock PRIVATE
    ${PROJECT_SOURCE_DIR}/tests/libdisplay_mock
)

add_dependencies(test_binary game_mock display_mock)

target_compile_options(test_binary PRIVATE
    -Wall
    -Wextra
    -g3
)

target_compile_definitions(test_binary PRIVATE
    LIB_PATH="${CMAKE_SOURCE_DIR}/libs/"
)

target_link_libraries(test_binary PRIVATE criterion)
