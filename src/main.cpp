#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/game.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "DOD Game");

    Game game(window);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
        }

        game.update();
    }

    return 0;
}