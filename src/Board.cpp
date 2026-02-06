#include "../include/Board.h"
#include "SFML/Graphics/RectangleShape.hpp"
using namespace sf;
using namespace std;
using namespace GameConfig;

Board::Board()
{
    createCurrentTetromino();

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

void Board::draw(RenderWindow& window) const
{
    currentTetromino_.draw(window);

    for (int y = BOARD_BLOCK_HEIGHT - 1; y >= 0; --y)
        for (int x = BOARD_BLOCK_WIDTH - 1; x >= 0; --x)
            if (matrixBlocks_[y][x].exist_)
            {
                RectangleShape block(Vector2f(CELL_SIZE, CELL_SIZE));
                block.setFillColor(matrixBlocks_[y][x].color_);
                block.setPosition(Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                window.draw(block);
            }

    window.draw(grid_);
}

bool Board::isGameOver() const
{
    for (const Block& block : matrixBlocks_[0])
        if (block.exist_)
            return true;
    return false;
}

const Tetromino& Board::getCurrentTetromino() const
{
    return currentTetromino_;
}

bool Board::fallCurrentTetromino()
{
    Tetromino testTetromino = getCurrentTetromino();
    testTetromino.setPosition(testTetromino.getX(), testTetromino.getY() + 1);

    if (isCollide(testTetromino))
    {
        fillBoardMatrixTetrominos();
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
        int x = testTetromino.getX();
        int y = testTetromino.getY();

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
        else if (Keyboard::isKeyPressed(Keyboard::Key::Space)) while (fallCurrentTetromino());
        else if (Keyboard::isKeyPressed(Keyboard::Key::Up))
        {
            testTetromino.rotate();
            if (!isCollide(testTetromino))
                currentTetromino_ = testTetromino;
            else if (tryWallKick(testTetromino))
                currentTetromino_ = testTetromino;
        }
    }
}

int Board::clearFullLines()
{
    int cleared = 0;

    for (int y = BOARD_BLOCK_HEIGHT - 1; y >= 0; --y)
    {
        bool lineFull = true;

        for (int x = 0; x < BOARD_BLOCK_WIDTH; ++x)
            if (!matrixBlocks_[y][x].exist_)
            {
                lineFull = false;
                break;
            }

        if (lineFull)
        {
            ++cleared;

            for (int i = 0; i < BOARD_BLOCK_WIDTH; ++i)
                matrixBlocks_[y][i].exist_ = false;

            for (int row = y; row > 0; --row)
                for (int i = 0; i < BOARD_BLOCK_WIDTH; ++i)
                    matrixBlocks_[row][i] = matrixBlocks_[row - 1][i];
            y++;
        }
    }

    return cleared;
}

void Board::fillBoardMatrixTetrominos()
{
    auto shape = currentTetromino_.getShape();
    for (int y = 0; y < SIZE_SHAPE; ++y)
        for (int x = 0; x < SIZE_SHAPE; ++x)
            if (shape[y][x])
            {
                int boardY = currentTetromino_.getY() + y;
                int boardX = currentTetromino_.getX() + x;

                if (boardY >= 0 && boardY < BOARD_BLOCK_HEIGHT &&
                    boardX >= 0 && boardX < BOARD_BLOCK_WIDTH)
                {
                    matrixBlocks_[boardY][boardX].exist_ = true;
                    matrixBlocks_[boardY][boardX].color_ = currentTetromino_.getColor();
                }
            }
}

bool Board::tryWallKick(Tetromino& tetromino)
{
    int x = tetromino.getX();
    int y = tetromino.getY();

    static int kicks[] = {-1, 1, -2, 2};

    for (int dx : kicks)
    {
        tetromino.setPosition(x + dx, y);
        if (!isCollide(tetromino))
            return true;
    }

    tetromino.setPosition(x, y);
    return false;
}

void Board::createCurrentTetromino()
{
    currentTetromino_ = Tetromino();
    currentTetromino_.setPosition(START_X, START_Y);
}

void Board::createCurrentTetromino(const Tetromino& tetromino)
{
    currentTetromino_ = tetromino;
}

bool Board::isCollide(const Tetromino& tetromino)
{
    array<array<bool, SIZE_SHAPE>, SIZE_SHAPE> shape = tetromino.getShape();
    for (int y = 0; y < SIZE_SHAPE; ++y)
        for (int x = 0; x < SIZE_SHAPE; ++x)
            if (shape[y][x])
            {
                int yFull = y + tetromino.getY();
                int xFull = x + tetromino.getX();

                if (yFull == BOARD_BLOCK_HEIGHT ||
                    xFull < 0 || xFull >= BOARD_BLOCK_WIDTH ||
                    matrixBlocks_[yFull][xFull].exist_)
                    return true;
            }
    return false;
}
