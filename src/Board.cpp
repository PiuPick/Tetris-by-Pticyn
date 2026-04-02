#include "../include/Board.h"

using namespace GameConfig;
using namespace std;
using namespace sf;

Board::Board() : isFix_(false)
{
    tetromino_ = Tetromino();
    tetromino_.setPosition(START_X, START_Y);
    createGrid();
}

bool Board::isCollide(const Tetromino& tetromino) const
{
    const array<array<bool, SIZE_SHAPE>, SIZE_SHAPE> shape = tetromino.getShape();
    for (int y = 0; y < SIZE_SHAPE; ++y)
        for (int x = 0; x < SIZE_SHAPE; ++x)
            if (shape[y][x])
            {
                const int yFull = y + tetromino.getY();
                const int xFull = x + tetromino.getX();

                if (yFull >= BOARD_BLOCK_HEIGHT ||
                    xFull < 0 || xFull >= BOARD_BLOCK_WIDTH ||
                    heap_.isBlockExist(xFull, yFull))
                    return true;
            }
    return false;
}

bool Board::tryWallKick(Tetromino& tetromino) const
{
    const int x = tetromino.getX();
    const int y = tetromino.getY();

    static int kicks[] = {0, -1, 1, -2, 2};

    for (const int dx : kicks)
    {
        tetromino.setPosition(x + dx, y);
        if (!isCollide(tetromino))
            return true;
    }

    tetromino.setPosition(x, y);
    return false;
}

unsigned Board::getClearedLines() const { return heap_.getClearedLines(); }
bool Board::isOverFlow() const { return heap_.isOverFlow(); }
bool Board::isFix() const { return isFix_; }

void Board::setTetromino(const Tetromino& tetromino)
{
    isFix_ = false;
    tetromino_ = tetromino;
    tetromino_.setPosition(START_X, START_Y);
}

void Board::action()
{
    Tetromino test = tetromino_;

    if (command_.softDrop)
        fall();
    else if (command_.moveRight)
    {
        test.moveRight();
        if (!isCollide(test))
            tetromino_.moveRight();
    }
    else if (command_.rotate)
    {
        test.rotate();
        if (tryWallKick(test))
            tetromino_ = test;
    }
    else if (command_.moveLeft)
    {
        test.moveLeft();
        if (!isCollide(test))
            tetromino_.moveLeft();
    }
    else if (command_.hardDrop)
        while (!isFix_)
            fall();

    command_ = {};
}

void Board::fall()
{
    Tetromino test = tetromino_;

    test.moveDown();
    if (isCollide(test))
    {
        heap_.addTetromino(tetromino_);
        isFix_ = true;
    }
    else tetromino_.moveDown();
}

void Board::requestMoveLeft() { command_.moveLeft = true; }
void Board::requestMoveRight() { command_.moveRight = true; }
void Board::requestRotate() { command_.rotate = true; }
void Board::requestSoftDrop() { command_.softDrop = true; }
void Board::requestHardDrop() { command_.hardDrop = true; }

const VertexArray& Board::getGrid() const
{
    return grid_;
}

const Tetromino& Board::getTetromino() const
{
    return tetromino_;
}

const Heap& Board::getHeap() const
{
    return heap_;
}

void Board::createGrid()
{
    VertexArray grid(PrimitiveType::Lines, (BOARD_BLOCK_WIDTH + BOARD_BLOCK_HEIGHT + 2) * 2);
    for (int x = 0; x < BOARD_BLOCK_WIDTH + 1; ++x)
    {
        grid.append(Vertex(Vector2f(x * CELL_SIZE, 0), Color::White));
        grid.append(Vertex(Vector2f(x * CELL_SIZE, WINDOW_HEIGHT), Color::White));
    }
    for (int y = 0; y < BOARD_BLOCK_HEIGHT + 1; ++y)
    {
        grid.append(Vertex(Vector2f(0, y * CELL_SIZE), Color::White));
        grid.append(Vertex(Vector2f(BOARD_BLOCK_WIDTH * CELL_SIZE, y * CELL_SIZE), Color::White));
    }
    grid_ = grid;
}