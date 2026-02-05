#pragma once
#include "Tetromino.h"
#include "ConfigurationConstants.h"
#include "SFML/Graphics/VertexArray.hpp"
using namespace sf;
using namespace std;
using namespace GameConfig;

class Board
{
private:
    struct Block
    {
        bool exist_;
        Color color_;
    };

    Tetromino currentTetromino_;
    VertexArray grid_;
    array<array<Block, BOARD_WIDTH>, BOARD_HEIGHT> matrixBlocks_ = {};
    Tetromino getCurrentTetromino() const;
    bool isCollide(Tetromino& tetromino);
    void fillBoardMatrixTetrominos();
    void blocksInLine();
    bool tryWallKick(Tetromino& tetromino);
    void createCurrentTetromino();

public:
    Board();
    bool fallCurrentTetromino();
    void action(const Event& event);
    void draw(RenderWindow& window) const;
};
