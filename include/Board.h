#pragma once
#include "Tetromino.h"
#include "ConfigurationConstants.h"
#include "SFML/Graphics/VertexArray.hpp"

class Board
{
private:
    struct Block
    {
        bool exist_;
        sf::Color color_;
    };

    Tetromino currentTetromino_;
    sf::VertexArray grid_;
    std::array<std::array<Block, GameConfig::BOARD_WIDTH>, GameConfig::BOARD_HEIGHT> matrixBlocks_ = {};
    Tetromino getCurrentTetromino() const;
    bool isCollide(const Tetromino& tetromino);
    void fillBoardMatrixTetrominos();
    void blocksInLine();
    bool tryWallKick(Tetromino& tetromino);
    void createCurrentTetromino();

public:
    Board();
    bool fallCurrentTetromino();
    void action(const sf::Event& event);
    void draw(sf::RenderWindow& window) const;
};
