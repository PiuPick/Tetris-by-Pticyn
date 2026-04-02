#include "../include/Game.h"

using namespace GameConfig;
using namespace std;
using namespace sf;

Game::Game(const string& playerName) :
    state_(Playing),
    window_(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tetris-by-Pticyn"),
    boardView_(board_),
    nextTetrominoView_(nextTetromino_)
{
    drawables_.push_back(&boardView_);
    drawables_.push_back(&nextTetrominoView_);

    info_.setPlayerName(playerName);

    createNextTetromino();
    clock_.start();
}

void Game::createNextTetromino()
{
    nextTetromino_ = Tetromino();
    nextTetromino_.setPosition(BOARD_BLOCK_WIDTH + 1, 1);
}

void Game::run()
{
    while (window_.isOpen())
    {
        handle();
        action();
        draw();
    }
}

void Game::pause()
{
    state_ = Paused;
    clock_.stop();
    info_.pauseOrResume();
}

void Game::resume()
{
    state_ = Playing;
    clock_.start();
    info_.pauseOrResume();
}

void Game::gameOver()
{
    state_ = GameOver;
    clock_.stop();
    info_.gameOver();
}

void Game::restart()
{
    board_ = Board();
    state_ = Playing;
    clock_.restart();
    info_.restart();
    createNextTetromino();
}

void Game::handle()
{
    while (const optional event = window_.pollEvent())
    {
        if (event->is<Event::Closed>())
        {
            window_.close();
            return;
        }

        if (event->is<Event::KeyPressed>())
        {
            const auto key = event->getIf<Event::KeyPressed>()->code;

            if (state_ == Playing)
            {
                if (key == Keyboard::Key::Left) board_.requestMoveLeft();
                else if (key == Keyboard::Key::Right) board_.requestMoveRight();
                else if (key == Keyboard::Key::Up) board_.requestRotate();
                else if (key == Keyboard::Key::Down) board_.requestSoftDrop();
                else if (key == Keyboard::Key::Space) board_.requestHardDrop();
                else if (key == Keyboard::Key::P) pause();
            }
            else if (state_ == GameOver && key == Keyboard::Key::Enter) restart();
            else if (state_ == Paused && key == Keyboard::Key::P) resume();
        }
    }
}

void Game::action()
{
    if (state_ != Playing)
        return;

    board_.action();

    if (clock_.getElapsedTime().asMilliseconds() >= info_.getFallSpeed())
    {
        board_.requestSoftDrop();
        clock_.restart();
    }
    else
    {
        if (board_.isFix())
        {
            if (board_.isOverFlow())
            {
                gameOver();
                return;
            }

            info_.calculateScore(board_.getClearedLines());
            board_.setTetromino(nextTetromino_);
            createNextTetromino();
        }
    }
}

void Game::draw()
{
    window_.clear(Color::Black);

    for (const auto* drawable : drawables_)
        drawable->draw(window_);
    info_.draw(window_);

    window_.display();
}