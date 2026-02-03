#pragma once
#include "SFML/Graphics/Color.hpp"
#include <array>

#include "SFML/Graphics/RenderWindow.hpp"
using namespace sf;
using namespace std;

class Tetromino
{
    enum TetrominoType
    {
        I, O, T, S, Z, J, L
    };

private:
    int x_;
    int y_;
    Color color_;
    TetrominoType type_;
    array<array<bool, 4>, 4> shape_ {};

public:
    Tetromino();
    void rotate();
    int getX() const;
    int getY() const;
    char getType() const;
    Color getColor() const;
    TetrominoType getTetrominoType() const;
    array<array<bool, 4>, 4> getShape() const;
    void setPosition(int x, int y);
    void draw(RenderWindow& window, int cellSize, int offsetX, int offsetY) const;
};
