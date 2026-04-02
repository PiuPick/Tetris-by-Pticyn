#include "../include/ConsoleMenu.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

//  Считывает int в диапазоне [min, max]; валидирует каждый ввод
int ConsoleMenu::readInt(const string& prompt, int min, int max)
{
    while (true)
    {
        cout << prompt;
        string line;

        if (!getline(cin, line))
        {
            cin.clear();
            continue;
        }

        // Пустая строка
        if (line.empty())
        {
            cout << "  [!] Пустой ввод. Введите число от " << min << " до " << max << ".\n";
            continue;
        }

        // Только цифры (допускается ведущий минус)
        bool valid = true;
        size_t start = (line[0] == '-') ? 1 : 0;
        if (start == line.size()) valid = false;
        for (size_t i = start; i < line.size() && valid; ++i)
            if (!isdigit(static_cast<unsigned char>(line[i])))
                valid = false;

        if (!valid)
        {
            cout << "  [!] Некорректный ввод «" << line  << "». Ожидается целое число.\n";
            continue;
        }

        // Парсим
        int value;
        istringstream iss(line);
        if (!(iss >> value))
        {
            cout << "  [!] Число выходит за допустимые пределы.\n";
            continue;
        }

        // Диапазон
        if (value < min || value > max)
        {
            cout << "  [!] Значение должно быть от " << min << " до " << max << ". Попробуйте ещё раз.\n";
            continue;
        }

        return value;
    }
}

//  Главное меню
MenuChoice ConsoleMenu::showMainMenu()
{
    cout << "\n";
    cout << "  ╔══════════════════════════════╗\n";
    cout << "  ║      TETRIS  by  Pticyn      ║\n";
    cout << "  ╠══════════════════════════════╣\n";
    cout << "  ║  1. Играть                   ║\n";
    cout << "  ║  2. Тестовые сценарии        ║\n";
    cout << "  ║  3. Таблица рекордов         ║\n";
    cout << "  ║  4. Выход                    ║\n";
    cout << "  ╚══════════════════════════════╝\n";

    int choice = readInt("  Ваш выбор [1-4]: ", 1, 4);

    switch (choice)
    {
    case 1: return MenuChoice::Play;
    case 2: return MenuChoice::RunTests;
    case 3: return MenuChoice::ShowScores;
    default: return MenuChoice::Exit;
    }
}

//  Запрос имени игрока с валидацией
string ConsoleMenu::askPlayerName()
{
    cout << "\n";
    while (true)
    {
        cout << "  Введите имя (1-10 символов, буквы и цифры): ";
        string name;

        if (!getline(cin, name))
        {
            cin.clear();
            continue;
        }

        // Пустое
        if (name.empty())
        {
            cout << "  [!] Имя не может быть пустым.\n";
            continue;
        }

        // Слишком длинное
        if (name.size() > 10)
        {
            cout << "  [!] Имя слишком длинное (максимум 10 символов).\n";
            continue;
        }

        // Недопустимые символы
        bool valid = true;
        for (char c : name)
            if (!isalnum(static_cast<unsigned char>(c)))
            {
                valid = false;
                break;
            }

        if (!valid)
        {
            cout << "  [!] Допускаются только буквы и цифры (без пробелов).\n";
            continue;
        }

        cout << "  Добро пожаловать, " << name << "!\n\n";
        return name;
    }
}