#include "HeapView.h"
#include "../ConfigurationConstants.h"
#include <SFML/Graphics/RectangleShape.hpp>

void HeapView::draw(sf::RenderWindow& window) const
{
    for (int y = 0; y < GameConfig::BOARD_BLOCK_HEIGHT; ++y)
        for (int x = 0; x < GameConfig::BOARD_BLOCK_WIDTH; ++x)
        {
            if (model_.isBlockExist(x, y))
            {
                sf::RectangleShape block(sf::Vector2f(GameConfig::CELL_SIZE, GameConfig::CELL_SIZE));
                block.setFillColor(model_.getColorAt(x, y));
                block.setPosition(sf::Vector2f(x * GameConfig::CELL_SIZE, y * GameConfig::CELL_SIZE));
                window.draw(block);
            }
        }
}