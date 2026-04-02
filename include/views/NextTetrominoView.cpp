#include "NextTetrominoView.h"
#include <SFML/Graphics/RectangleShape.hpp>
using namespace GameConfig;
using namespace sf;

void NextTetrominoView::draw(RenderWindow& window) const
{
    RectangleShape block(Vector2f(CELL_SIZE, CELL_SIZE));
    block.setFillColor(model_.getColor());

    const auto& shape = model_.getShape();
    for (int y = 0; y < SIZE_SHAPE; ++y)
        for (int x = 0; x < SIZE_SHAPE; ++x)
            if (shape[y][x])
            {
                block.setPosition(Vector2f((model_.getX() + x) * CELL_SIZE,
                                           (model_.getY() + y) * CELL_SIZE));
                window.draw(block);
            }
}