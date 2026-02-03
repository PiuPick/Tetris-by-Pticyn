#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode({1080, 720}), "Window Title");

    Font font("../res/fonts/consolas.ttf");
    Text text(font, "Hello world!", 50);

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
            if (event->is<Event::Closed>())
                window.close();

        window.draw(text);
        window.display();
    }
}