#pragma once
#include "Board.h"
#include "ScoreManager.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

enum class GameState
{
    EnterName,
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
    int score_, level_;
    float fallSpeed_;
    sf::RenderWindow window_;
    sf::Font font_;
    sf::Text scoreText_, levelText_, nextText_, stateText_, namePromptText_, nameValueText_, bestScoreText_;
    Tetromino nextTetromino_;
    std::string playerName_;
    ScoreManager scoreManager_;
    void processEvents();
    void update();
    void render();

public:
    Game();
    void run();
};
