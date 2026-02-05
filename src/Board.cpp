#include "../include/Board.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/VertexArray.hpp"
using namespace GameConfig;

Board::Board()
{
    createCurrentTetromino();

    VertexArray grid(PrimitiveType::Lines, (BOARD_WIDTH + BOARD_HEIGHT + 2) * 2);
    for (int x = 0; x < BOARD_WIDTH + 1; ++x)
    {
        grid.append(Vertex(Vector2f(x * CELL_SIZE, 0), Color::White));
        grid.append(Vertex(Vector2f(x * CELL_SIZE, WINDOW_HEIGHT), Color::White));
    }
    for (int y = 0; y < BOARD_HEIGHT + 1; ++y)
    {
        grid.append(Vertex(Vector2f(0, y * CELL_SIZE), Color::White));
        grid.append(Vertex(Vector2f(WINDOW_WIDTH, y * CELL_SIZE), Color::White));
    }
    grid_ = grid;
}

void Board::draw(RenderWindow& window) const
{
    currentTetromino_.draw(window);

    for (int y = BOARD_HEIGHT - 1; y >= 0; --y)
        for (int x = BOARD_WIDTH - 1; x >= 0; --x)
            if (matrixBlocks_[y][x].exist_)
            {
                RectangleShape block(Vector2f(CELL_SIZE, CELL_SIZE));
                block.setFillColor(matrixBlocks_[y][x].color_);
                block.setPosition(Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                window.draw(block);
            }

    window.draw(grid_);
}

Tetromino Board::getCurrentTetromino() const
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
        blocksInLine();

        for (Block block : matrixBlocks_[0])
            if (block.exist_)
                return false;

        createCurrentTetromino();
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
        else if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) while (fallCurrentTetromino());
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

void Board::blocksInLine()
{
    for (int y = BOARD_HEIGHT - 1; y >= 0; --y)
    {
        bool lineFull = true;

        for (int x = 0; x < BOARD_WIDTH; ++x)
            if (!matrixBlocks_[y][x].exist_)
            {
                lineFull = false;
                break;
            }

        if (lineFull)
        {
            for (int i = 0; i < BOARD_WIDTH; ++i)
                matrixBlocks_[y][i].exist_ = false;

            for (int row = y; row > 0; --row)
                for (int i = 0; i < BOARD_WIDTH; ++i)
                    matrixBlocks_[row][i] = matrixBlocks_[row - 1][i];
            y++;
        }
    }
}

void Board::fillBoardMatrixTetrominos()
{
    array<array<bool, 4>, 4> shape = currentTetromino_.getShape();
    int tetrominoX = currentTetromino_.getX();
    int tetrominoY = currentTetromino_.getY();
    for (int y = 0; y < 4; ++y)
        for (int x = 0; x < 4; ++x)
            if (shape[y][x])
            {
                matrixBlocks_[tetrominoY + y][tetrominoX + x].exist_ = true;
                matrixBlocks_[tetrominoY + y][tetrominoX + x].color_ = currentTetromino_.getColor();
            }
}

bool Board::tryWallKick(Tetromino& tetromino)
{
    int x = tetromino.getX();
    int y = tetromino.getY();

    static const int kicks[] = {-1, 1, -2, 2};

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

bool Board::isCollide(Tetromino& tetromino)
{
    array<array<bool, 4>, 4> shape = tetromino.getShape();
    for (int y = 0; y < 4; ++y)
        for (int x = 0; x < 4; ++x)
            if (shape[y][x])
            {
                int yFull = y + tetromino.getY();
                int xFull = x + tetromino.getX();

                if (yFull == BOARD_HEIGHT ||
                    xFull < 0 || xFull >= BOARD_WIDTH ||
                    matrixBlocks_[yFull][xFull].exist_)
                    return true;
            }
    return false;
}
