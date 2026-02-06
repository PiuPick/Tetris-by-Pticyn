#include "../include/ScoreManager.h"
#include <fstream>
using namespace std;

ScoreManager::ScoreManager(const string& filename) : filename_(filename)
{
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

    while (file >> name >> score)
        scores_[name] = score;
}

void ScoreManager::saveToFile() const
{
    ofstream file(filename_, ios::trunc);
    for (const auto& [name, score] : scores_)
        file << name << " " << score << "\n";
}

void ScoreManager::updateScore(const string& name, int score)
{
    if (!scores_.contains(name) || scores_[name] < score)
    {
        scores_[name] = score;
        saveToFile();
    }
}

pair<string, int> ScoreManager::getBestScore() const
{
    if (scores_.empty())
        return {"---", 0};

    auto best = scores_.begin();
    for (auto it = scores_.begin(); it != scores_.end(); ++it)
        if (it->second > best->second)
            best = it;

    return *best;
}
