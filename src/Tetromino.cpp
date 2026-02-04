#include <array>
#include <cctype>
#include "../include/Tetromino.h"
#include "SFML/Graphics/RectangleShape.hpp"

namespace sf
{
    class RenderWindow;
}

Tetromino::Tetromino() : x_(0), y_(0)
{
    std::array<Color, 7> colors = {
        Color::White,
        Color::Red,
        Color::Green,
        Color::Blue,
        Color::Yellow,
        Color::Magenta,
        Color::Cyan
    };

    // Случайный выбор цвета и типа тетромино
    color_ = colors[rand() % colors.size()];
    type_ = TetrominoType(rand() % 7);

    switch (type_)
    {
    case TetrominoType::I:
        shape_[1][0] = true;
        shape_[1][1] = true;
        shape_[1][2] = true;
        shape_[1][3] = true;
        break;

    case TetrominoType::O:
        shape_[1][1] = true;
        shape_[1][2] = true;
        shape_[2][1] = true;
        shape_[2][2] = true;
        break;

    case TetrominoType::T:
        shape_[1][0] = true;
        shape_[1][1] = true;
        shape_[1][2] = true;
        shape_[2][1] = true;
        break;

    case TetrominoType::S:
        shape_[1][1] = true;
        shape_[1][2] = true;
        shape_[2][0] = true;
        shape_[2][1] = true;
        break;

    case TetrominoType::Z:
        shape_[1][0] = true;
        shape_[1][1] = true;
        shape_[2][1] = true;
        shape_[2][2] = true;
        break;

    case TetrominoType::J:
        shape_[1][0] = true;
        shape_[1][1] = true;
        shape_[1][2] = true;
        shape_[2][0] = true;
        break;

    case TetrominoType::L:
        shape_[1][0] = true;
        shape_[1][1] = true;
        shape_[1][2] = true;
        shape_[2][2] = true;
        break;
    }
}

void Tetromino::rotate()
{
    array<array<bool, 4>, 4> temp;
    // Транспонирование и реверсирование матрицы для поворота на 90 градусов по часовой стрелке
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            temp[j][3 - i] = shape_[i][j];

    shape_ = temp;
}

int Tetromino::getX() const
{
    return x_;
}

int Tetromino::getY() const
{
    return y_;
}

char Tetromino::getType() const
{
    return type_;
}

Color Tetromino::getColor() const
{
    return color_;
}

Tetromino::TetrominoType Tetromino::getTetrominoType() const
{
    return type_;
}

array<array<bool, 4>, 4> Tetromino::getShape() const
{
    return shape_;
}

void Tetromino::setPosition(int x, int y)
{
    x_ = x;
    y_ = y;
}

void Tetromino::draw(RenderWindow& window) const
{
    RectangleShape block(Vector2f(50, 50));
    block.setFillColor(color_);

    for (int y = 0; y < 4; ++y)
        for (int x = 0; x < 4; ++x)
            if (shape_[y][x])
            {
                block.setPosition(
                    Vector2f(
                        (x_ + x) * 50,
                        (y_ + y) * 50));
                window.draw(block);
            }
}
