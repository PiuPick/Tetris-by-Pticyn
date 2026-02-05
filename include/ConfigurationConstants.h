#pragma once

namespace GameConfig
{
    constexpr unsigned short BOARD_WIDTH = 10; // Ширина игрового поля в клетках
    constexpr unsigned short BOARD_HEIGHT = 20; // Высота игрового поля в клетках
    constexpr unsigned short CELL_SIZE = 50; // Размер клетки в пикселях
    constexpr unsigned short WINDOW_WIDTH = BOARD_WIDTH * CELL_SIZE + 1; // Ширина окна в пикселях
    constexpr unsigned short WINDOW_HEIGHT = BOARD_HEIGHT * CELL_SIZE + 1; // Высота окна в пикселях
    constexpr float SPEED_FREE_FALL = 0.5; // Скорость свободного падения (в секундах)
    constexpr int SIZE_SHAPE = 4; // Размер блока в котором находится тетромино
    constexpr int START_X = BOARD_WIDTH / 2 - SIZE_SHAPE / 2; // Стартовая точка тетромино на доске по x
    constexpr int START_Y = -1; // Стартовая точка тетромино на доске по y
}
