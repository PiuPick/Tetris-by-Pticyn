#pragma once
#include "ConfigurationConstants.h"
#include <array>
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Tetromino
{
    enum Type
    {
        I, O, T, S, Z, J, L
    };

private:
    int x_;
    int y_;
    sf::Color color_;
    Type type_;
    std::array<std::array<bool, GameConfig::SIZE_SHAPE>, GameConfig::SIZE_SHAPE> shape_{};

public:
    Tetromino();
    void rotate();
    int getX() const;
    int getY() const;
    sf::Color getColor() const;
    std::array<std::array<bool, GameConfig::SIZE_SHAPE>, GameConfig::SIZE_SHAPE> getShape() const;
    void setPosition(int x, int y);
    void draw(sf::RenderWindow& window) const;
};
