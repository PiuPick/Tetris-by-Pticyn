#include "BoardView.h"
#include <SFML/Graphics/VertexArray.hpp>
#include "HeapView.h"
#include "TetrominoView.h"

void BoardView::draw(sf::RenderWindow& window) const
{
    TetrominoView(model_.getTetromino()).draw(window);
    HeapView(model_.getHeap()).draw(window);
    window.draw(model_.getGrid());
}
