#include "include/Game.h"
#include "include/ConsoleMenu.h"
#include "include/TestRunner.h"
#include "include/ScoreManager.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

static void showScores()
{
    ScoreManager sm;
    auto [bestName, bestScore] = sm.getBestScore();

    cout << "\n";
    cout << "  " << string(40, '=') << "\n";
    cout << "       Таблица рекордов\n";
    cout << "  " << string(40, '=') << "\n";

    if (bestName.empty())
        cout << "  Рекордов пока нет.\n";
    else
    {
        cout << "  Лучший результат:\n";
        cout << "    Игрок: " << bestName << "\n";
        cout << "    Очки:  " << bestScore << "\n";
    }

    cout << "  " << string(40, '=') << "\n";
    cout << "\n  Нажмите Enter...";
    string tmp;
    getline(cin, tmp);
}

static void runTests()
{
    cout << "\n  Запуск тестов...\n";
    TestRunner runner;
    runner.runAll();
    runner.printResults();
    cout << "  Нажмите Enter...";
    string tmp;
    getline(cin, tmp);
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    while (true)
    {
        MenuChoice choice = ConsoleMenu::showMainMenu();

        switch (choice)
        {
        case MenuChoice::Play:
            {
                string name = ConsoleMenu::askPlayerName();
                Game game(name);
                game.run();
                break;
            }
        case MenuChoice::RunTests:
            runTests();
            break;
        case MenuChoice::ShowScores:
            showScores();
            break;
        case MenuChoice::Exit:
            cout << "\n  До свидания!\n\n";
            return 0;
        }
    }
}