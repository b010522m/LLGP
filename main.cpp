#include <SFML/Graphics.hpp>
#include <iostream>

/*
    This version of the SFML "hello world" is statically linked, you may wish to try the dynamically linked version as well.
*/
int WinMain()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML works!");

    while (window.isOpen())
    {
        window.setFramerateLimit(60);
        // Event polling section of code - this must be done in the thread which created the window
        // we will talk about threading later, but essentially this must be done here
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            window.clear();
            window.display();
        }
    }
}