#include "TetrominoView.h"
#include "../ConfigurationConstants.h"
#include "SFML/Graphics/RectangleShape.hpp"

void TetrominoView::draw(sf::RenderWindow& window) const
{
    sf::RectangleShape block(sf::Vector2f(GameConfig::CELL_SIZE, GameConfig::CELL_SIZE));
    block.setFillColor(model_.getColor());

    const auto& shape = model_.getShape();
    for (int y = 0; y < GameConfig::SIZE_SHAPE; ++y)
        for (int x = 0; x < GameConfig::SIZE_SHAPE; ++x)
            if (shape[y][x])
            {
                block.setPosition(sf::Vector2f((model_.getX() + x) * GameConfig::CELL_SIZE,
                                               (model_.getY() + y) * GameConfig::CELL_SIZE));
                window.draw(block);
            }
}