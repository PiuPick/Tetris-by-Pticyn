#include "../include/Board.h"
#include "SFML/Graphics/RectangleShape.hpp"
using namespace sf;
using namespace std;
using namespace GameConfig;

Board::Board()
{
    tetromino_ = Tetromino();
    tetromino_.setPosition(START_X, START_Y);

    createGrid();
}

void Board::draw(RenderWindow& window) const
{
    tetromino_.draw(window);
    heap_.draw(window);
    window.draw(grid_);
}

const Tetromino& Board::getTetromino() const
{
    return tetromino_;
}

unsigned Board::getClearedLines() const
{
    return heap_.getClearedLines();
}

bool Board::isOverFlowHeap() const
{
    return heap_.isOverFlow();
}

bool Board::fallTetromino()
{
    Tetromino testTetromino = getTetromino();
    testTetromino.moveDown();

    if (isCollide(testTetromino))
    {
        heap_.addTetromino(tetromino_);
        return false;
    }

    tetromino_.moveDown();
    return true;
}

void Board::action(const Event& event)
{
    if (event.is<Event::KeyPressed>())
    {
        Tetromino testTetromino = getTetromino();

        if (Keyboard::isKeyPressed(Keyboard::Key::Left))
        {
            testTetromino.moveLeft();
            if (!isCollide(testTetromino))
                tetromino_.moveLeft();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Right))
        {
            testTetromino.moveRight();
            if (!isCollide(testTetromino))
                tetromino_.moveRight();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Down)) fallTetromino();
        else if (Keyboard::isKeyPressed(Keyboard::Key::Space)) while (fallTetromino()) {}
        else if (Keyboard::isKeyPressed(Keyboard::Key::Up))
        {
            testTetromino.rotate();
            tetromino_ = tryWallKick(testTetromino);
        }
    }
}

Tetromino& Board::tryWallKick(Tetromino& tetromino) const
{
    const int x = tetromino.getX();
    const int y = tetromino.getY();

    static int kicks[] = {0, -1, 1, -2, 2};

    for (const int dx : kicks)
    {
        tetromino.setPosition(x + dx, y);
        if (!isCollide(tetromino))
            return tetromino;
    }

    tetromino.setPosition(x, y);
    return tetromino;
}

void Board::setTetromino(const Tetromino& tetromino)
{
    tetromino_ = tetromino;
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

bool Board::isCollide(const Tetromino& tetromino) const
{
    const array<array<bool, SIZE_SHAPE>, SIZE_SHAPE> shape = tetromino.getShape();
    for (int y = 0; y < SIZE_SHAPE; ++y)
        for (int x = 0; x < SIZE_SHAPE; ++x)
            if (shape[y][x])
            {
                const int yFull = y + tetromino.getY();
                const int xFull = x + tetromino.getX();

                if (yFull == BOARD_BLOCK_HEIGHT ||
                    xFull < 0 || xFull >= BOARD_BLOCK_WIDTH ||
                    (yFull >= 0 && heap_.isBlockExist(xFull, yFull)))
                    return true;
            }
    return false;
}
