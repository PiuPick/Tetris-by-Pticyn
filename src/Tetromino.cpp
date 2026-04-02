#include "../include/Tetromino.h"
#include "SFML/Graphics/RectangleShape.hpp"

using namespace GameConfig;
using namespace std;
using namespace sf;

void Tetromino::chooseType()
{
    switch (static_cast<Type>(rand() % 7))
    {
    case Type::I:
        shape_[1][0] = true;
        shape_[1][1] = true;
        shape_[1][2] = true;
        shape_[1][3] = true;
        break;

    case Type::O:
        shape_[1][1] = true;
        shape_[1][2] = true;
        shape_[2][1] = true;
        shape_[2][2] = true;
        break;

    case Type::T:
        shape_[1][0] = true;
        shape_[1][1] = true;
        shape_[1][2] = true;
        shape_[2][1] = true;
        break;

    case Type::S:
        shape_[1][1] = true;
        shape_[1][2] = true;
        shape_[2][0] = true;
        shape_[2][1] = true;
        break;

    case Type::Z:
        shape_[1][0] = true;
        shape_[1][1] = true;
        shape_[2][1] = true;
        shape_[2][2] = true;
        break;

    case Type::J:
        shape_[1][0] = true;
        shape_[1][1] = true;
        shape_[1][2] = true;
        shape_[2][0] = true;
        break;

    case Type::L:
        shape_[1][0] = true;
        shape_[1][1] = true;
        shape_[1][2] = true;
        shape_[2][2] = true;
        break;
    }
}

Tetromino::Tetromino() : x_(0), y_(0)
{
    chooseType();

    std::array<Color, 7> colors = {
        Color::White,
        Color::Red,
        Color::Green,
        Color::Blue,
        Color::Yellow,
        Color::Magenta,
        Color::Cyan
    };

    color_ = colors[rand() % colors.size()];
}

void Tetromino::moveLeft()
{
    x_--;
}

void Tetromino::moveRight()
{
    x_++;
}

void Tetromino::moveDown()
{
    y_++;
}

void Tetromino::rotate()
{
    array<array<bool, SIZE_SHAPE>, SIZE_SHAPE> temp{};
    for (int i = 0; i < SIZE_SHAPE; ++i)
        for (int j = 0; j < SIZE_SHAPE; ++j)
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

Color Tetromino::getColor() const
{
    return color_;
}

const array<array<bool, SIZE_SHAPE>, SIZE_SHAPE>& Tetromino::getShape() const
{
    return shape_;
}

void Tetromino::setPosition(const int x, const int y)
{
    x_ = x;
    y_ = y;
}