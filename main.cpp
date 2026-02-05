#include "include/Board.h"
using namespace sf;
using namespace std;
using namespace GameConfig;

int main()
{
    RenderWindow window(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tetris-by-Pticyn");

    Board board;
    Clock clock;
    clock.start();

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
            board.action(*event);
        }

        if (clock.getElapsedTime().asSeconds() >= SPEED_FREE_FALL)
        {
            board.fallCurrentTetromino();
            clock.restart();
        }

        window.clear(Color::Black);
        board.draw(window);
        window.display();
    }
    return 0;
}
