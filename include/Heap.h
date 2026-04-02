#pragma once
#include "Tetromino.h"
#include "ConfigurationConstants.h"
#include <array>
#include "SFML/Graphics/Color.hpp"

class Heap
{
private:
    struct Block
    {
        bool exist_;
        sf::Color color_;
    };

    unsigned clearedLines_ = 0;
    std::array<std::array<Block, GameConfig::BOARD_BLOCK_WIDTH>, GameConfig::BOARD_BLOCK_HEIGHT> heapBlocks_ = {};

    void clearFullLines();

public:
    void addTetromino(const Tetromino& tetromino);

    bool isOverFlow() const;
    bool isBlockExist(int x, int y) const;

    unsigned getClearedLines() const;
    sf::Color getColorAt(int x, int y) const;
};