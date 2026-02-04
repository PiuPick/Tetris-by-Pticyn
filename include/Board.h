#pragma once
#include <vector>
#include "Tetromino.h"
#include "ConfigurationConstants.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/VertexArray.hpp"
using namespace sf;
using namespace std;

class Board
{
private:
    unsigned short width_;
    unsigned short height_;
    Color colorBackground_;
    vector<Tetromino> tetrominos_;
    VertexArray grid_;

public:
    Board();
    unsigned short getWidth() const;
    unsigned short getHeight() const;
    Color getColorBackground() const;
    void addTetromino(const Tetromino& tetromino);
    VertexArray getGrid() const;
    void draw(RenderWindow& window) const;
};
