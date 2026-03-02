#include "../include/Heap.h"

#include "SFML/Graphics/RectangleShape.hpp"
using namespace GameConfig;

void Heap::clearFullLines()
{
    clearedLines_ = 0;

    for (int y = BOARD_BLOCK_HEIGHT - 1; y >= 0; --y)
    {
        bool lineFull = true;

        for (int x = 0; x < BOARD_BLOCK_WIDTH; ++x)
            if (!heapBlocks_[y][x].exist_)
            {
                lineFull = false;
                break;
            }

        if (lineFull)
        {
            ++clearedLines_;

            for (int i = 0; i < BOARD_BLOCK_WIDTH; ++i)
                heapBlocks_[y][i].exist_ = false;

            for (int row = y; row > 0; --row)
                for (int i = 0; i < BOARD_BLOCK_WIDTH; ++i)
                    heapBlocks_[row][i] = heapBlocks_[row - 1][i];
            y++;
        }
    }
}

bool Heap::isOverFlow() const
{
    if (heapBlocks_[0][START_X].exist_)
        return true;
    return false;
}

bool Heap::isBlockExist(const int x, const int y) const
{
    return heapBlocks_[y][x].exist_;
}

unsigned Heap::getClearedLines() const
{
    return clearedLines_;
}

void Heap::addTetromino(const Tetromino& tetromino)
{
    const auto shape = tetromino.getShape();
    for (int y = 0; y < SIZE_SHAPE; ++y)
        for (int x = 0; x < SIZE_SHAPE; ++x)
            if (shape[y][x])
            {
                const int yFull = tetromino.getY() + y;
                const int xFull = tetromino.getX() + x;

                if (yFull >= 0 && yFull < BOARD_BLOCK_HEIGHT &&
                    xFull >= 0 && xFull < BOARD_BLOCK_WIDTH)
                {
                    heapBlocks_[yFull][xFull].exist_ = true;
                    heapBlocks_[yFull][xFull].color_ = tetromino.getColor();
                }
            }

    clearFullLines();
}

void Heap::draw(sf::RenderWindow& window) const
{
    for (int y = 0; y < BOARD_BLOCK_HEIGHT; ++y)
        for (int x = 0; x < BOARD_BLOCK_WIDTH; ++x)
            if (heapBlocks_[y][x].exist_)
            {
                sf::RectangleShape block(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                block.setFillColor(heapBlocks_[y][x].color_);
                block.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                window.draw(block);
            }
}
