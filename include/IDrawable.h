#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class IDrawable
{
public:
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual ~IDrawable() = default;
};