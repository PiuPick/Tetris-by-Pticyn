#include "../include/Game.h"

#include "SFML/Graphics/RectangleShape.hpp"
using namespace sf;
using namespace std;
using namespace GameConfig;

Game::Game() :
    window_(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tetris-by-Pticyn"),
    scoreManager_("scores.txt"),
    font_(Font("../res/fonts/consolas.ttf")),
    namePromptText_(font_, "Enter name for\nstart game:", 100),
    nameValueText_(font_, "", 100),
    bestScoreText_(font_, "", 20),
    scoreText_(font_, "", 20),
    levelText_(font_, "", 20),
    nextText_(font_, "NEXT TETROMINO", 20),
    stateText_(font_, "", 40),
    state_(GameState::EnterName),
    score_(0),
    level_(1),
    fallSpeed_(SPEED_FREE_FALL)
{
    clock_.start();

    nameValueText_.setPosition({CELL_SIZE, WINDOW_HEIGHT / 2});
    bestScoreText_.setPosition({PANEL_X, CELL_SIZE * 9});

    scoreText_.setPosition({PANEL_X, CELL_SIZE * 5});
    levelText_.setPosition({PANEL_X, CELL_SIZE * 6});
    nextText_.setPosition({PANEL_X + CELL_SIZE, CELL_SIZE});

    stateText_.setFillColor(Color::Red);
    stateText_.setOutlineColor(Color::White);
    stateText_.setOutlineThickness(2);

    createNextTetromino();
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

        if (state_ == GameState::EnterName)
        {
            if (event->is<Event::TextEntered>())
            {
                char c = static_cast<char>(event->getIf<Event::TextEntered>()->unicode);

                if (isalnum(c) && playerName_.size() < 10)
                    playerName_ += c;
                else if (c == '\b' && !playerName_.empty())
                    playerName_.pop_back();

                nameValueText_.setString(playerName_);
            }

            if (event->is<Event::KeyPressed>() &&
                event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Enter &&
                !playerName_.empty())
            {
                state_ = GameState::Playing;
                namePromptText_.setPosition({PANEL_X, CELL_SIZE * 8});
                namePromptText_.setCharacterSize(20);
                namePromptText_.setString("Your name: " + playerName_);
            }
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
            stateText_.setPosition({PANEL_X + CELL_SIZE, WINDOW_HEIGHT / 2 + CELL_SIZE});
        }
        else if (state_ == GameState::GameOver)
        {
            stateText_.setString("GAME OVER");
            stateText_.setPosition({PANEL_X + CELL_SIZE / 2, WINDOW_HEIGHT / 2 + CELL_SIZE});
            scoreManager_.updateScore(playerName_, score_);
        }
        return;
    }

    if (clock_.getElapsedTime().asSeconds() >= fallSpeed_)
    {
        bool moved = board_.fallTetromino();
        clock_.restart();

        if (!moved)
        {
            int lines = board_.getClearedLines();
            if (lines > 0)
            {
                static const int scores[] = {0, 100, 300, 500, 800};
                score_ += scores[lines];
                level_ = score_ / 1000 + 1;
                fallSpeed_ = SPEED_FREE_FALL / level_;
            }

            nextTetromino_.setPosition(START_X, START_Y);
            board_.setTetromino(nextTetromino_);
            createNextTetromino();

            if (board_.isOverFlowHeap())
                state_ = GameState::GameOver;
        }
    }

    scoreText_.setString("Score: " + to_string(score_));
    levelText_.setString("Level: " + to_string(level_));
}

void Game::render()
{
    if (state_ == GameState::EnterName)
    {
        window_.clear(Color::Black);
        window_.draw(namePromptText_);
        window_.draw(nameValueText_);
        window_.display();
        return;
    }

    window_.clear(Color::Black);

    board_.draw(window_);

    window_.draw(scoreText_);
    window_.draw(levelText_);
    window_.draw(nextText_);
    window_.draw(namePromptText_);
    nextTetromino_.draw(window_);

    auto [bestName, bestScore] = scoreManager_.getBestScore();
    bestScoreText_.setString("Best: " + bestName + " - " + to_string(bestScore));
    window_.draw(bestScoreText_);

    if (state_ != GameState::Playing)
        window_.draw(stateText_);

    window_.display();
}

void Game::createNextTetromino()
{
    nextTetromino_ = Tetromino();
    nextTetromino_.setPosition(BOARD_BLOCK_WIDTH + 1, 1);
}
