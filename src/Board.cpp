#include "../include/Board.h"
#include "SFML/Graphics/VertexArray.hpp"

Board::Board() : width_(10), height_(20), colorBackground_(Color::Black)
{
    // Игровая сетка
    VertexArray grid(PrimitiveType::Lines, (GameConfig::BOARD_WIDTH + GameConfig::BOARD_HEIGHT + 2) * 2);
    for (int x = 0; x < GameConfig::BOARD_WIDTH + 1; ++x)
    {
        grid.append(Vertex(Vector2f(x * GameConfig::CELL_SIZE, 0), Color::White));
        grid.append(Vertex(Vector2f(x * GameConfig::CELL_SIZE, GameConfig::WINDOW_HEIGHT), Color::White));
    }
    for (int y = 0; y < GameConfig::BOARD_HEIGHT + 1; ++y)
    {
        grid.append(Vertex(Vector2f(0, y * GameConfig::CELL_SIZE), Color::White));
        grid.append(Vertex(Vector2f(GameConfig::WINDOW_WIDTH, y * GameConfig::CELL_SIZE), Color::White));
    }
    grid_ = grid;
}

unsigned short Board::getWidth() const
{
    return width_;
}

unsigned short Board::getHeight() const
{
    return height_;
}

Color Board::getColorBackground() const
{
    return colorBackground_;
}

void Board::addTetromino(const Tetromino& tetromino)
{
    tetrominos_.push_back(tetromino);
}

VertexArray Board::getGrid() const
{
    return grid_;
}

void Board::draw(RenderWindow& window) const
{
    // Рисуем тетромино
    for (Tetromino tetromino : tetrominos_)
        tetromino.draw(window);

    // Рисуем сетку
    window.draw(grid_);
}
