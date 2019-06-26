#pragma once

#include <SFML/Graphics.hpp>
#include "resource_definitions.hpp"


struct Context {
    sf::RenderWindow *window;
    TextureHolder *textureHolder;
    FontHolder *fontHolder;
    int currentGameScreen;
    sf::Vector2f screenSize;

    Context(sf::RenderWindow &pWindow,
            TextureHolder &pTextureHolder,
            FontHolder &pFontHolder,
            int gameScreen) :
            window(&pWindow),
            textureHolder(&pTextureHolder),
            fontHolder(&pFontHolder),
            currentGameScreen(gameScreen){}

    Context(const Context& context) = delete;
};
