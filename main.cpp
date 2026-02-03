#include <SFML/Graphics.hpp>
#include "include/Tetromino.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode({501, 1001}), "Tetris-by-Pticyn");

    // Создаем несколько тестовых фигур
    Tetromino pieces[] = {
        Tetromino(),
        Tetromino(),
        Tetromino(),
        Tetromino(),
        Tetromino(),
        Tetromino()
    };

    // Позиционируем их
    pieces[0].setPosition(1, 1);
    pieces[1].setPosition(6, 1);
    pieces[2].setPosition(1, 6);
    pieces[3].setPosition(6, 6);
    pieces[4].setPosition(1, 11);
    pieces[5].setPosition(6, 11);

    // Таймер для автоповорота
    Clock rotationClock;
    float rotationInterval = 1.0f;

    // Игровая сетка
    VertexArray grid(PrimitiveType::Lines);
    for (int x = 0; x < 11; ++x)
    {
        // Вертикальные линии (10 колонок + 1 граница = 11 линий)
        grid.append(Vertex(Vector2f(x * 50.0f, 0.0f), Color(100, 100, 100)));
        grid.append(Vertex(Vector2f(x * 50.0f, 1000.0f), Color(100, 100, 100)));
    }
    for (int y = 0; y < 21; ++y)
    {
        // Горизонтальные линии (20 строк + 1 граница = 21 линия)
        grid.append(Vertex(Vector2f(0.0f, y * 50.0f), Color(100, 100, 100)));
        grid.append(Vertex(Vector2f(500.0f, y * 50.0f), Color(100, 100, 100)));
    }

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();

            // Тест управления
            if (event->is<Event::KeyPressed>())
            {
                if (Keyboard::isKeyPressed(Keyboard::Key::R))
                {
                    // Вращаем все фигуры при нажатии R
                    for (auto& piece : pieces)
                        piece.rotate();
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Space))
                {
                    // Создаем новую случайную фигуру
                    pieces[5] = Tetromino();
                    pieces[5].setPosition(6, 11);
                }
            }
        }

        // Автоповорот по таймеру
        if (rotationClock.getElapsedTime().asSeconds() > rotationInterval)
        {
            pieces[0].rotate(); // Вращаем только первую фигуру
            rotationClock.restart();
        }

        window.clear(Color::Black);

        // Рисуем сетку
        window.draw(grid);

        // Рисуем все тетромино
        for (const auto& piece : pieces)
            piece.draw(window, 50, 0, 0); // Размер клетки 50 пикселей

        window.display();
    }
    return 0;
}