#pragma once
#include "ConfigurationConstants.h"
#include <array>
#include "SFML/Graphics/Color.hpp"

class Tetromino
{
private:
    int x_, y_;
    sf::Color color_;
    std::array<std::array<bool, GameConfig::SIZE_SHAPE>, GameConfig::SIZE_SHAPE> shape_{};

    enum Type
    {
        I, O, T, S, Z, J, L
    };

    void chooseType();

public:
    Tetromino();

    void moveLeft();
    void moveRight();
    void moveDown();
    void rotate();

    int getX() const;
    int getY() const;
    sf::Color getColor() const;
    const std::array<std::array<bool, GameConfig::SIZE_SHAPE>, GameConfig::SIZE_SHAPE>& getShape() const;

    void setPosition(int x, int y);
};