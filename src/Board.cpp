#include "../include/Board.h"
#include "SFML/Graphics/VertexArray.hpp"
using namespace GameConfig;

Board::Board() : width_(BOARD_WIDTH), height_(BOARD_HEIGHT)
{
    currentTetromino_ = Tetromino();
    currentTetromino_.setPosition(0, -2);

    VertexArray grid(PrimitiveType::Lines, (width_ + height_ + 2) * 2);
    for (int x = 0; x < width_ + 1; ++x)
    {
        grid.append(Vertex(Vector2f(x * CELL_SIZE, 0), Color::White));
        grid.append(Vertex(Vector2f(x * CELL_SIZE, WINDOW_HEIGHT), Color::White));
    }
    for (int y = 0; y < height_ + 1; ++y)
    {
        grid.append(Vertex(Vector2f(0, y * CELL_SIZE), Color::White));
        grid.append(Vertex(Vector2f(WINDOW_WIDTH, y * CELL_SIZE), Color::White));
    }
    grid_ = grid;
}

void Board::draw(RenderWindow& window) const
{
    currentTetromino_.draw(window);

    for (Tetromino tetromino : tetrominos_)
        tetromino.draw(window);

    window.draw(grid_);
}

Tetromino Board::getCurrentTetromino() const
{
    return currentTetromino_;
}

bool Board::fallCurrentTetromino()
{
    Tetromino testTetromino = getCurrentTetromino();
    testTetromino.setPosition(currentTetromino_.getX(), currentTetromino_.getY() + 1);

    if (isCollide(testTetromino))
    {
        tetrominos_.push_back(currentTetromino_);
        fillBoardMatrixTetrominos();

        for (bool block : boardMatrixTetrominos_[0])
            if (block)
                return false;

        currentTetromino_ = Tetromino();
        currentTetromino_.setPosition(0, -2);
        return false;
    }
    else
        currentTetromino_.setPosition(currentTetromino_.getX(), currentTetromino_.getY() + 1);

    return true;
}

void Board::action(const Event& event)
{
    if (event.is<Event::KeyPressed>())
    {
        Tetromino testTetromino = getCurrentTetromino();
        int x = currentTetromino_.getX();
        int y = currentTetromino_.getY();

        if (Keyboard::isKeyPressed(Keyboard::Key::Left))
        {
            testTetromino.setPosition(x - 1, y);
            if (!isCollide(testTetromino))
                currentTetromino_.setPosition(x - 1, y);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Right))
        {
            testTetromino.setPosition(x + 1, y);
            if (!isCollide(testTetromino))
                currentTetromino_.setPosition(x + 1, y);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::Down)) fallCurrentTetromino();
        else if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) while (fallCurrentTetromino());
        else if (Keyboard::isKeyPressed(Keyboard::Key::Up))
        {
            testTetromino.rotate();
            if (!isCollide(testTetromino)) currentTetromino_.rotate();
        }
    }
}

void Board::fillBoardMatrixTetrominos()
{
    for (Tetromino tetromino : tetrominos_)
    {
        array<array<bool, 4>, 4> shape = tetromino.getShape();
        for (int y = 0; y < 4; ++y)
            for (int x = 0; x < 4; ++x)
                if (shape[y][x])
                    boardMatrixTetrominos_[tetromino.getY() + y][tetromino.getX() + x] = true;
    }
}

bool Board::isCollide(Tetromino tetromino)
{
    array<array<bool, 4>, 4> shape = tetromino.getShape();
    for (int y = 0; y < 4; ++y)
        for (int x = 0; x < 4; ++x)
            if (shape[y][x])
            {
                int yFull = y + tetromino.getY();
                int xFull = x + tetromino.getX();

                if (boardMatrixTetrominos_[yFull][xFull] ||
                    yFull == BOARD_HEIGHT ||
                    xFull < 0 || xFull >= BOARD_WIDTH)
                    return true;
            }

    return false;
}
