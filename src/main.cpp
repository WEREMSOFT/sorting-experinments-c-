#include <iostream>
#include <SFML/Graphics.hpp>
#include "game/game.hpp"
#include "context.hpp"
#include "game/load_screen.hpp"

#define OBBJECT_COUNT 5

int main() {
    sf::RenderWindow window(sf::VideoMode(1230, 768), "SFML Apllication", sf::Style::Default);

    TextureHolder textureHolder;
    FontHolder fontHolder;


    Context context(window, textureHolder, fontHolder);

    {
        LoadScreen::Struct loadScreen(context);
        LoadScreen::utils::loadResources(loadScreen);
        LoadScreen::utils::run(loadScreen);
    }


    Game::Struct game(context);
    Game::utils::createRecursiveHierarchy(game.gameObjects.back(), OBBJECT_COUNT);
    Game::utils::createRecursiveHierarchy(game.gameObjects[0], OBBJECT_COUNT);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
        }
        Game::utils::update(game);
    }

    return 0;
}