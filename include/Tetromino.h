#pragma once
#include "ConfigurationConstants.h"
#include <array>
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Tetromino
{
private:
    int x_;
    int y_;
    sf::Color color_;
    std::array<std::array<bool, GameConfig::SIZE_SHAPE>, GameConfig::SIZE_SHAPE> shape_{};

    enum Type
    {
        I, O, T, S, Z, J, L
    };

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
