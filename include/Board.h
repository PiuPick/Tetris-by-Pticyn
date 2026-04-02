#pragma once
#include "Tetromino.h"
#include "Heap.h"
#include "SFML/Graphics/VertexArray.hpp"

class Board
{
private:
    struct InputCommand
    {
        bool moveLeft = false;
        bool moveRight = false;
        bool rotate = false;
        bool softDrop = false;
        bool hardDrop = false;
    };

    Tetromino tetromino_;
    Heap heap_;

    bool isFix_;
    InputCommand command_;
    sf::VertexArray grid_;

    void fall();
    bool isCollide(const Tetromino& tetromino) const;
    bool tryWallKick(Tetromino& tetromino) const;
    void createGrid();

public:
    Board();

    unsigned getClearedLines() const;
    bool isOverFlow() const;
    bool isFix() const;
    void setTetromino(const Tetromino& tetromino);

    void action();

    void requestMoveLeft();
    void requestMoveRight();
    void requestRotate();
    void requestSoftDrop();
    void requestHardDrop();

    const sf::VertexArray& getGrid() const;
    const Tetromino& getTetromino() const;
    const Heap& getHeap() const;
};
