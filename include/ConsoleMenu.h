#pragma once
#include <string>

enum class MenuChoice
{
    Play,
    RunTests,
    ShowScores,
    Exit
};

class ConsoleMenu
{
public:
    // Показывает главное меню и возвращает выбор пользователя
    static MenuChoice showMainMenu();

    // Запрашивает имя игрока через консоль с полной валидацией
    static std::string askPlayerName();

    // Считывает целое число из консоли; повторяет запрос при некорректном вводе
    static int readInt(const std::string& prompt, int min, int max);
};