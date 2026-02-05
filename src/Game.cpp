#include "../include/Game.h"
using namespace sf;
using namespace std;
using namespace GameConfig;

Game::Game() :
    window_(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tetris-by-Pticyn"),
    state_(GameState::Playing),
    score_(0),
    level_(1),
    fallSpeed_(SPEED_FREE_FALL)
{
    clock_.start();
}

void Game::run()
{
    while (window_.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    while (const optional event = window_.pollEvent())
    {
        if (event->is<Event::Closed>())
        {
            window_.close();
            continue;
        }

        if (!event->is<Event::KeyPressed>()) continue;

        const auto key = event->getIf<Event::KeyPressed>()->code;

        if (state_ == GameState::GameOver)
        {
            if (key == Keyboard::Key::Enter)
            {
                board_ = Board();
                state_ = GameState::Playing;
                clock_.restart();
            }
            continue;
        }

        if (key == Keyboard::Key::P)
        {
            if (state_ == GameState::Playing) state_ = GameState::Paused;
            else if (state_ == GameState::Paused) state_ = GameState::Playing;
            continue;
        }

        if (state_ == GameState::Playing) board_.action(*event);
    }
}

void Game::update()
{
    if (state_ != GameState::Playing) return;

    if (clock_.getElapsedTime().asSeconds() >= fallSpeed_)
    {
        bool moved = board_.fallCurrentTetromino();
        clock_.restart();

        if (!moved)
        {
            int lines = board_.clearFullLines();
            if (lines > 0)
            {
                static const int scores[] = {0, 100, 300, 500, 800};
                score_ += scores[lines];
                level_ = score_ / 1000 + 1;
                fallSpeed_ = SPEED_FREE_FALL / level_;
            }

            if (board_.isGameOver())
                state_ = GameState::GameOver;
        }
    }
}

void Game::render()
{
    window_.clear(Color::Black);
    board_.draw(window_);
    window_.display();
}
