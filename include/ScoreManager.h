#pragma once
#include <map>
#include <string>

class ScoreManager
{
private:
    static constexpr unsigned SCORES[] = {0, 100, 300, 500, 800};

    std::string name_;
    unsigned score_, level_;
    std::map<std::string, unsigned> scores_;
    std::string filename_;
    void loadFromFile();
    void saveToFile() const;

public:
    ScoreManager();
    void initScoreAndLevel();

    void updateScore();
    void calculateScore(unsigned countLines);

    std::pair<std::string, unsigned> getBestScore() const;
    unsigned getScore() const;
    unsigned getLevel() const;
    void setName(const std::string& name);
};