#pragma once
#include "Board.h"
#include "Info.h"
#include "Tetromino.h"
#include "IDrawable.h"
#include "views/BoardView.h"
#include "views/TetrominoView.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <string>

class Game
{
private:
    enum GameState { Playing, Paused, GameOver };

    Board board_;
    Info info_;
    Tetromino nextTetromino_;

    BoardView boardView_;
    TetrominoView nextTetrominoView_;

    std::vector<IDrawable*> drawables_;

    sf::Clock clock_;
    GameState state_;
    sf::RenderWindow window_;

    void handle();
    void action();
    void draw();
    void pause();
    void resume();
    void gameOver();
    void restart();
    void createNextTetromino();

public:
    explicit Game(const std::string& playerName);
    void run();
};