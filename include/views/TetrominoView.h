#pragma once
#include "../IDrawable.h"
#include "../Tetromino.h"

class TetrominoView : public IDrawable
{
private:
    const Tetromino& model_;
public:
    TetrominoView(const Tetromino& tetromino) : model_(tetromino) {}
    void draw(sf::RenderWindow& window) const override;
};