#include "../include/Info.h"

using namespace GameConfig;
using namespace std;
using namespace sf;

Info::Info() :
    fallSpeed_(SPEED_FREE_FALL),
    font_(Font("../res/fonts/consolas.ttf")),
    scoreText_(font_, "", 20),
    levelText_(font_, "", 20),
    nextText_(font_, "NEXT TETROMINO", 20),
    stateText_(font_, "", 40),
    namePromptText_(font_, "", 20),
    bestScoreText_(font_, "", 20)
{
    bestScoreText_.setPosition({PANEL_X, CELL_SIZE * 9});
    scoreText_.setPosition({PANEL_X, CELL_SIZE * 5});
    levelText_.setPosition({PANEL_X, CELL_SIZE * 6});
    nextText_.setPosition({PANEL_X + CELL_SIZE, CELL_SIZE});
    namePromptText_.setPosition({PANEL_X, CELL_SIZE * 8});

    stateText_.setFillColor(Color::Red);
    stateText_.setOutlineColor(Color::White);
    stateText_.setOutlineThickness(2);
    stateText_.setPosition({PANEL_X + CELL_SIZE / 2, WINDOW_HEIGHT / 2 + CELL_SIZE});

    calculateScore(0);
}

void Info::setPlayerName(const string& name)
{
    playerName_ = name;
    namePromptText_.setString("Player: " + playerName_);
    scoreManager_.setName(playerName_);
}

unsigned Info::getFallSpeed() const
{
    return fallSpeed_;
}

void Info::draw(RenderWindow& window)
{
    window.draw(scoreText_);
    window.draw(levelText_);
    window.draw(nextText_);
    window.draw(namePromptText_);
    window.draw(stateText_);

    auto [name, bestScore] = scoreManager_.getBestScore();
    bestScoreText_.setString("Best: " + name + " - " + to_string(bestScore));
    window.draw(bestScoreText_);
}

void Info::pauseOrResume()
{
    if (stateText_.getString() == "PAUSE")
        stateText_.setString("");
    else
        stateText_.setString("PAUSE");
}

void Info::gameOver()
{
    stateText_.setString("GAME OVER\n");
    scoreManager_.updateScore();
}

void Info::restart()
{
    scoreManager_.initScoreAndLevel();
    fallSpeed_ = SPEED_FREE_FALL;
    stateText_.setString("");
    calculateScore(0);
}

void Info::calculateScore(const int countLines)
{
    scoreManager_.calculateScore(countLines);

    const int score = scoreManager_.getScore();
    const int level = scoreManager_.getLevel();

    fallSpeed_ = SPEED_FREE_FALL / (1 + level / 10);

    scoreText_.setString("Score: " + to_string(score));
    levelText_.setString("Level: " + to_string(level));
}