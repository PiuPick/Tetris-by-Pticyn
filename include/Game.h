#pragma once
#include "Board.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

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
    sf::Font font_;
    sf::Text scoreText_;
    sf::Text levelText_;
    sf::Text nextText_;
    sf::Text stateText_;
    Tetromino currentTetromino_;
    Tetromino nextTetromino_;
    void processEvents();
    void update();
    void render();
    void drawNextTetromino();

public:
    Game();
    void run();
};
