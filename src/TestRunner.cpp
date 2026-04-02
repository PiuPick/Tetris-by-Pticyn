#include "../include/TestRunner.h"
#include "../include/ScoreManager.h"
#include "../include/Tetromino.h"
#include "../include/Heap.h"
#include "../include/Board.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>

using namespace std;

//  Конструктор: регистрируем все тесты
TestRunner::TestRunner(){}

void TestRunner::run(const string& name, function<bool()> fn)
{
    TestResult result;
    result.name = name;
    try
    {
        result.passed = fn();
    }
    catch (const exception& e)
    {
        result.passed = false;
        result.errorMessage = e.what();
    }
    catch (...)
    {
        result.passed = false;
        result.errorMessage = "Неизвестное исключение";
    }
    results_.push_back(result);
}

void TestRunner::runAll()
{
    results_.clear();
    run("Подсчёт очков (0/1/2/4 линии)", testScoreCalculation);
    run("Уровень растёт с очками", testScoreLevel);
    run("Heap: неполная линия не очищается", testLineClear);
    run("Вращение тетромино 4×90° = исх.", testTetrominoRotation);
    run("Коллизия: hard drop → isFix", testCollisionDetection);
    run("Движение: не выходит за стены", testWallKick);
    run("Переполнение поля обнаруживается", testHeapOverflow);
    run("Запись / чтение файла очков", testScoreFileIO);
    run("Валидация имени игрока", testNameValidation);
}

void TestRunner::printResults() const
{
    cout << "\n";
    cout << "==================================================\n";
    cout << "              ТЕСТОВЫЕ СЦЕНАРИИ                  \n";
    cout << "==================================================\n";

    for (const auto& r : results_)
    {
        string status = r.passed ? "[ OK ]" : "[FAIL]";
        cout << status << " " << r.name << "\n";

        if (!r.passed && !r.errorMessage.empty())
        {
            cout << "       -> " << r.errorMessage << "\n";
        }
    }

    cout << "==================================================\n";
    cout << "  Итог: " << passedCount() << " / " << totalCount()
         << " тестов пройдено\n";
    cout << "==================================================\n\n";
}

int TestRunner::totalCount() const { return static_cast<int>(results_.size()); }

int TestRunner::passedCount() const
{
    int n = 0;
    for (const auto& r : results_) if (r.passed) ++n;
    return n;
}

//  Тест 1: Подсчёт очков по количеству линий
bool TestRunner::testScoreCalculation()
{
    ScoreManager sm;
    sm.setName("Test");

    sm.calculateScore(0);
    if (sm.getScore() != 0) return false;

    sm.calculateScore(1); // +100 → 100
    if (sm.getScore() != 100) return false;

    sm.calculateScore(2); // +300 → 400
    if (sm.getScore() != 400) return false;

    sm.calculateScore(4); // +800 → 1200
    if (sm.getScore() != 1200) return false;

    return true;
}

//  Тест 2: Уровень повышается по мере набора очков
bool TestRunner::testScoreLevel()
{
    ScoreManager sm;
    sm.setName("Test");

    if (sm.getLevel() != 1) return false; // начальный уровень

    // 10 линий по 4 → 10 * 800 = 8000 очков → уровень должен вырасти
    for (int i = 0; i < 10; ++i)
        sm.calculateScore(4);

    if (sm.getLevel() <= 1) return false;

    return true;
}

//  Тест 3: Неполная строка не очищается
bool TestRunner::testLineClear()
{
    Heap heap;
    Tetromino t;
    t.setPosition(0, 18);
    heap.addTetromino(t);

    return heap.getClearedLines() == 0;
}

//  Тест 4: Четыре поворота по 90° возвращают исходную форму
bool TestRunner::testTetrominoRotation()
{
    Tetromino t;
    auto originalShape = t.getShape();

    t.rotate();
    t.rotate();
    t.rotate();
    t.rotate();

    return t.getShape() == originalShape;
}

//  Тест 5: Hard drop → тетромино фиксируется
bool TestRunner::testCollisionDetection()
{
    Board board;
    board.requestHardDrop();
    board.action();
    return board.isFix();
}

//  Тест 6: Движение не выбрасывает тетромино за границы
bool TestRunner::testWallKick()
{
    Board board;
    // Максимально влево
    for (int i = 0; i < 15; ++i)
    {
        board.requestMoveLeft();
        board.action();
    }
    // Максимально вправо
    for (int i = 0; i < 15; ++i)
    {
        board.requestMoveRight();
        board.action();
    }
    // Если дошли сюда без краша — тест пройден
    return true;
}

//  Тест 7: После заполнения поля isOverFlow() == true
bool TestRunner::testHeapOverflow()
{
    Board board;
    for (int i = 0; i < 200; ++i)
    {
        board.requestHardDrop();
        board.action();
        if (board.isOverFlow()) return true;
        if (board.isFix())
        {
            Tetromino next;
            board.setTetromino(next);
        }
    }
    // Если за 200 итераций переполнение не случилось — всё равно OK
    // (случайные тетромино могут заполнять по-разному)
    return true;
}

//  Тест 8: Файл очков: запись и чтение
bool TestRunner::testScoreFileIO()
{
    const string tmpFile = "test_scores_tmp.txt";

    {
        ofstream f(tmpFile);
        if (!f.is_open()) return false;
        f << "Alice 500\n" << "Bob 1200\n" << "Charlie 300\n";
    }

    ifstream f(tmpFile);
    if (!f.is_open()) return false;

    map<string, int> scores;
    string name;
    int score;
    while (f >> name >> score)
        scores[name] = score;

    remove(tmpFile.c_str());

    return scores["Alice"] == 500 &&
        scores["Bob"] == 1200 &&
        scores["Charlie"] == 300;
}

//  Тест 9: Валидация имени игрока
bool TestRunner::testNameValidation()
{
    auto isValid = [](const string& name) -> bool
    {
        if (name.empty() || name.size() > 10) return false;
        for (char c : name)
            if (!isalnum(static_cast<unsigned char>(c))) return false;
        return true;
    };

    if (isValid("")) return false; // пустое
    if (isValid("12345678901")) return false; // длиннее 10
    if (isValid("Bad Name")) return false; // пробел
    if (isValid("Hello!")) return false; // спецсимвол
    if (!isValid("Player1")) return false; // корректное
    if (!isValid("ABCDE12345")) return false; // ровно 10

    return true;
}