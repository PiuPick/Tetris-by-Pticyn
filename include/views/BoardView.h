#pragma once
#include "../IDrawable.h"
#include "../Board.h"

class BoardView : public IDrawable
{
private:
    const Board& model_;
public:
    BoardView(const Board& board) : model_(board) {}
    void draw(sf::RenderWindow& window) const override;
};