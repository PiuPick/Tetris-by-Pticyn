#pragma once
#include "../IDrawable.h"
#include "../Tetromino.h"
#include <SFML/Graphics/RectangleShape.hpp>

class NextTetrominoView : public IDrawable
{
private:
    const Tetromino& model_;
public:
    NextTetrominoView(const Tetromino& tetromino) : model_(tetromino) {}
    void draw(sf::RenderWindow& window) const override;
};