#pragma once
#include <vector>
#include "Tetromino.h"
#include "ConfigurationConstants.h"
#include "SFML/Graphics/VertexArray.hpp"
using namespace sf;
using namespace std;
using namespace GameConfig;

class Board
{
private:
    unsigned short width_;
    unsigned short height_;
    vector<Tetromino> tetrominos_;
    VertexArray grid_;
    Tetromino currentTetromino_;
    array<array<bool, BOARD_WIDTH>, WINDOW_HEIGHT> boardMatrixTetrominos_ = {};
    void fillBoardMatrixTetrominos();
    bool isCollide(Tetromino tetromino);

public:
    Board();
    void draw(RenderWindow& window) const;
    Tetromino getCurrentTetromino() const;
    bool fallCurrentTetromino();
    void action(const Event& event);
};
