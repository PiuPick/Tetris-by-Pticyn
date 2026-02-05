#pragma once
#include "Board.h"

class Game
{
private:
    Board board_;
    sf::Clock clock_;
    sf::RenderWindow window_;
    void processEvents();
    void update();
    void render();

public:
    Game();
    void run();
};
