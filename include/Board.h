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
    std::array<std::array<Block, GameConfig::BOARD_BLOCK_WIDTH>, GameConfig::BOARD_BLOCK_HEIGHT> matrixBlocks_ = {};
    bool isCollide(const Tetromino& tetromino);
    void fillBoardMatrixTetrominos();
    bool tryWallKick(Tetromino& tetromino);

public:
    Board();
    bool fallCurrentTetromino();
    void action(const sf::Event& event);
    void draw(sf::RenderWindow& window) const;
    bool isGameOver() const;
    int clearFullLines();
    void createCurrentTetromino();
    void setCurrentTetromino(const Tetromino& tetromino);
    const Tetromino& getCurrentTetromino() const;
};
