#pragma once
#include <array>

#include "ConfigurationConstants.h"
#include "DrawableEntity.h"
#include "Tetromino.h"
#include "SFML/Graphics/Color.hpp"

class Heap : public DrawableEntity
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

    void draw(sf::RenderWindow& window) const override;
};
