#include "../include/Game.h"
using namespace sf;
using namespace std;
using namespace GameConfig;

Game::Game() : window_(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tetris-by-Pticyn")
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
            window_.close();

        board_.action(*event);
    }
}

void Game::update()
{
    if (clock_.getElapsedTime().asSeconds() >= SPEED_FREE_FALL)
    {
        board_.fallCurrentTetromino();
        clock_.restart();
    }
}

void Game::render()
{
    window_.clear(Color::Black);
    board_.draw(window_);
    window_.display();
}
