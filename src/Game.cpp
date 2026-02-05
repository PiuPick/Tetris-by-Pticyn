#include "../include/Game.h"
using namespace sf;
using namespace std;
using namespace GameConfig;

Game::Game() :
    window_(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tetris-by-Pticyn"),
    font_(Font("../res/fonts/consolas.ttf")),
    scoreText_(font_, "", 15),
    levelText_(font_, "", 15),
    stateText_(font_, "", 70),
    state_(GameState::Playing),
    score_(0),
    level_(1),
    fallSpeed_(SPEED_FREE_FALL)
{
    clock_.start();

    levelText_.setPosition(Vector2f{0, 20});

    stateText_.setFillColor(Color::Red);
    stateText_.setOutlineColor(Color::White);
    stateText_.setOutlineThickness(10);
    stateText_.setPosition(Vector2f{40, WINDOW_HEIGHT / 2 - 100});
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
                fallSpeed_ = SPEED_FREE_FALL;
                clock_.restart();
                score_ = 0;
                level_ = 1;
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
            else
                board_.createCurrentTetromino();
        }
    }

    scoreText_.setString("Score: " + std::to_string(score_));
    levelText_.setString("Level: " + std::to_string(level_));

    if (state_ == GameState::Paused)
        stateText_.setString("PAUSED");
    else if (state_ == GameState::GameOver)
        stateText_.setString("GAME OVER\nPress Enter");
    else
        stateText_.setString("");
}

void Game::render()
{
    window_.clear(Color::Black);

    board_.draw(window_);

    window_.draw(scoreText_);
    window_.draw(levelText_);

    if (state_ != GameState::Playing)
        window_.draw(stateText_);

    window_.display();
}
