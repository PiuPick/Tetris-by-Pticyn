#pragma once
#include "SFML/Graphics/RenderWindow.hpp"

class DrawableEntity
{
public:
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual ~DrawableEntity() = default;
};
