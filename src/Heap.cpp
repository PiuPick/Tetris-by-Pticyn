#include "../include/Heap.h"

using namespace GameConfig;
using namespace std;
using namespace sf;

void Heap::clearFullLines()
{
    clearedLines_ = 0;

    for (int y = BOARD_BLOCK_HEIGHT - 1; y >= 0; --y)
    {
        bool lineFull = true;

        for (int x = 0; x < BOARD_BLOCK_WIDTH; ++x)
        {
            if (!heapBlocks_[y][x].exist_)
            {
                lineFull = false;
                break;
            }
        }

        if (lineFull)
        {
            for (int row = y; row > 0; --row)
                heapBlocks_[row] = heapBlocks_[row - 1];

            for (auto& block : heapBlocks_[0])
            {
                block.exist_ = false;
                block.color_ = Color{};
            }

            ++clearedLines_;
            ++y;
        }
    }
}

bool Heap::isOverFlow() const
{
    if (heapBlocks_[0][BOARD_BLOCK_WIDTH / 2].exist_)
        return true;
    return false;
}

bool Heap::isBlockExist(const int x, const int y) const
{
    if (x < 0 || x >= BOARD_BLOCK_WIDTH ||
        y < 0 || y >= BOARD_BLOCK_HEIGHT)
        return false;

    return heapBlocks_[y][x].exist_;
}

unsigned Heap::getClearedLines() const
{
    return clearedLines_;
}

sf::Color Heap::getColorAt(const int x, const int y) const
{
    return heapBlocks_[y][x].color_;
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