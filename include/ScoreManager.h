#pragma once
#include <map>
#include <string>

class ScoreManager
{
private:
    std::map<std::string, int> scores_;
    std::string filename_;
    void loadFromFile();
    void saveToFile() const;

public:
    ScoreManager(const std::string& filename);
    void updateScore(const std::string& name, int score);
    std::pair<std::string, int> getBestScore() const;
};
