#pragma once
#include <string>
#include <vector>
#include <functional>

struct TestResult
{
    bool passed;
    std::string name;
    std::string errorMessage;
};

class TestRunner
{
public:
    TestRunner();

    void runAll();
    void printResults() const;

    int totalCount() const;
    int passedCount() const;

private:
    std::vector<TestResult> results_;

    void run(const std::string& name, std::function<bool()> fn);

    // Тестовые сценарии
    static bool testScoreCalculation();
    static bool testScoreLevel();
    static bool testLineClear();
    static bool testTetrominoRotation();
    static bool testCollisionDetection();
    static bool testWallKick();
    static bool testHeapOverflow();
    static bool testScoreFileIO();
    static bool testNameValidation();
};