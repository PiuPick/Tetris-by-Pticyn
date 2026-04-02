#pragma once
#include "../IDrawable.h"
#include "../Heap.h"

class HeapView : public IDrawable
{
private:
    const Heap& model_;
public:
    HeapView(const Heap& heap) : model_(heap) {}
    void draw(sf::RenderWindow& window) const override;
};