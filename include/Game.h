#pragma once
#include "Board.h"

enum class GameState
{
    Playing,
    Paused,
    GameOver
};

class Game
{
private:
    Board board_;
    sf::Clock clock_;
    GameState state_;
    int score_;
    int level_;
    float fallSpeed_;
    sf::RenderWindow window_;
    void processEvents();
    void update();
    void render();

public:
    Game();
    void run();
};
