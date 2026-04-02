#pragma once
#include "ConfigurationConstants.h"
#include "ScoreManager.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include <string>

class Info
{
private:
    float fallSpeed_;
    sf::Font font_;
    sf::Text scoreText_, levelText_, nextText_, stateText_, namePromptText_, bestScoreText_;
    std::string playerName_;
    ScoreManager scoreManager_;

public:
    Info();

    void setPlayerName(const std::string& name);

    void pauseOrResume();
    void gameOver();
    void restart();

    void calculateScore(int countLines);

    unsigned getFallSpeed() const;

    void draw(sf::RenderWindow& window);
};