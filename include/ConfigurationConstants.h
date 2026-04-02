#pragma once

namespace GameConfig
{
    constexpr unsigned short BOARD_BLOCK_WIDTH = 10; // Ширина игрового поля в клетках
    constexpr unsigned short BOARD_BLOCK_HEIGHT = 20; // Высота игрового поля в клетках

    constexpr unsigned short CELL_SIZE = 50; // Размер клетки в пикселях
    constexpr unsigned short SIDE_PANEL_WIDTH = CELL_SIZE * 6; // Ширина боковой панели

    constexpr unsigned short SPEED_FREE_FALL = 500; // Скорость падения тетрамино в миллисекундах
    constexpr unsigned short PANEL_X = (BOARD_BLOCK_WIDTH + 1) * CELL_SIZE - CELL_SIZE / 2;

    constexpr unsigned short SIZE_SHAPE = 4; // Размер блока в котором находится тетромино

    constexpr int START_X = BOARD_BLOCK_WIDTH / 2 - SIZE_SHAPE / 2; // Стартовая позиция тетромино на доске по X
    constexpr int START_Y = -1; // Стартовая позиция тетромино на доске по Y

    constexpr unsigned short WINDOW_HEIGHT = BOARD_BLOCK_HEIGHT * CELL_SIZE + 1; // Высота окна в пикселях
    constexpr unsigned short WINDOW_WIDTH = BOARD_BLOCK_WIDTH * CELL_SIZE + SIDE_PANEL_WIDTH; // Общая ширина окна
}