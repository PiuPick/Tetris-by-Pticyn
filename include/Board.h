#pragma once
#include "Tetromino.h"
#include "DrawableEntity.h"
#include "ConfigurationConstants.h"
#include "Heap.h"
#include "SFML/Graphics/VertexArray.hpp"

class Board : public DrawableEntity
{
private:
    Tetromino tetromino_;
    Heap heap_;
    sf::VertexArray grid_;

    void createGrid();
    bool isCollide(const Tetromino& tetromino) const;
    Tetromino& tryWallKick(Tetromino& tetromino) const;

public:
    Board();

    bool fallTetromino();
    void action(const sf::Event& event);

    const Tetromino& getTetromino() const;
    unsigned getClearedLines() const;
    bool isOverFlowHeap() const;
    void setTetromino(const Tetromino& tetromino);

    void draw(sf::RenderWindow& window) const override;
};
