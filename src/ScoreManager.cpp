#include "../include/ScoreManager.h"
#include <fstream>

using namespace std;

ScoreManager::ScoreManager() : filename_("scores.txt")
{
    initScoreAndLevel();
    loadFromFile();
}

void ScoreManager::loadFromFile()
{
    ifstream file(filename_);

    if (!file.is_open())
    {
        ofstream createFile(filename_);
        return;
    }

    string name;
    int score;

    while (file >> name)
    {
        if (!(file >> score))
            break;

        scores_[name] = score;
    }
}

void ScoreManager::saveToFile() const
{
    ofstream file(filename_, ios::trunc);
    for (const auto& [name, score] : scores_)
        file << name << " " << score << "\n";
}

void ScoreManager::initScoreAndLevel()
{
    score_ = 0;
    level_ = 1;
}

void ScoreManager::updateScore()
{
    if (!scores_.contains(name_) || scores_[name_] < score_)
    {
        scores_[name_] = score_;
        saveToFile();
    }
}

void ScoreManager::calculateScore(const unsigned countLines)
{
    score_ += SCORES[countLines];
    level_ = score_ / 1000 + 1;
}

pair<string, unsigned> ScoreManager::getBestScore() const
{
    if (scores_.empty())
        return {"", 0};

    string name;
    unsigned score = 0;

    for (const auto line : scores_)
    {
        if (score < line.second)
        {
            name = line.first;
            score = line.second;
        }
    }

    return {name, score};
}

unsigned ScoreManager::getScore() const
{
    return score_;
}

unsigned ScoreManager::getLevel() const
{
    return level_;
}

void ScoreManager::setName(const std::string& name)
{
    name_ = name;
}