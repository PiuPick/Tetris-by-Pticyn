#include "../include/Game.h"

#include "SFML/Graphics/RectangleShape.hpp"
using namespace sf;
using namespace std;
using namespace GameConfig;

Game::Game() :
    window_(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tetris-by-Pticyn"),
    font_(Font("../res/fonts/consolas.ttf")),
    scoreText_(font_, "", 20),
    levelText_(font_, "", 20),
    nextText_(font_, "NEXT TETROMINO", 20),
    stateText_(font_, "", 40),
    state_(GameState::Playing),
    score_(0),
    level_(1),
    fallSpeed_(SPEED_FREE_FALL)
{
    clock_.start();

    scoreText_.setPosition(Vector2f{PANEL_X, CELL_SIZE * 5});
    levelText_.setPosition(Vector2f{PANEL_X, CELL_SIZE * 6});
    nextText_.setPosition(Vector2f{PANEL_X, CELL_SIZE});

    stateText_.setFillColor(Color::Red);
    stateText_.setOutlineColor(Color::White);
    stateText_.setOutlineThickness(2);

    currentTetromino_ = Tetromino();
    nextTetromino_ = Tetromino();

    currentTetromino_.setPosition(START_X, START_Y);
    board_.setCurrentTetromino(currentTetromino_);
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
    if (state_ != GameState::Playing)
    {
        if (state_ == GameState::Paused)
        {
            stateText_.setString("PAUSE");
            stateText_.setPosition(Vector2f{PANEL_X + CELL_SIZE, WINDOW_HEIGHT / 2});
        }
        else if (state_ == GameState::GameOver)
        {
            stateText_.setString("GAME OVER");
            stateText_.setPosition(Vector2f{PANEL_X, WINDOW_HEIGHT / 2});
        }
        return;
    }

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

            currentTetromino_ = nextTetromino_;
            currentTetromino_.setPosition(START_X, START_Y);
            nextTetromino_ = Tetromino();

            board_.setCurrentTetromino(currentTetromino_);

            if (board_.isGameOver())
                state_ = GameState::GameOver;
        }
    }

    scoreText_.setString("Score: " + std::to_string(score_));
    levelText_.setString("Level: " + std::to_string(level_));
}

void Game::render()
{
    window_.clear(Color::Black);

    board_.draw(window_);

    window_.draw(scoreText_);
    window_.draw(levelText_);
    window_.draw(nextText_);
    drawNextTetromino();


    if (state_ != GameState::Playing)
        window_.draw(stateText_);

    window_.display();
}

void Game::drawNextTetromino()
{
    RectangleShape block(Vector2f(CELL_SIZE, CELL_SIZE));
    block.setFillColor(nextTetromino_.getColor());

    auto shape = nextTetromino_.getShape();

    for (int y = 0; y < SIZE_SHAPE; ++y)
        for (int x = 0; x < SIZE_SHAPE; ++x)
            if (shape[y][x])
            {
                block.setPosition(Vector2f(PANEL_X + x * CELL_SIZE, PANEL_Y + y * CELL_SIZE));
                window_.draw(block);
            }
}
