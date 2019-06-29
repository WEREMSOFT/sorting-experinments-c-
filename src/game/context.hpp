#pragma once

#include <SFML/Graphics.hpp>
#include "resource_definitions.hpp"


struct Context {
    sf::RenderWindow *window;
    TextureHolder *textureHolder;
    FontHolder *fontHolder;
    SoundHolder *soundHolder;
    int currentGameScreen;
    sf::Vector2f screenSize;
    bool fullscreen = false;

    Context(sf::RenderWindow &pWindow,
            TextureHolder &pTextureHolder,
            FontHolder &pFontHolder,
            SoundHolder &pSoundHolder,
            int gameScreen) :
            window(&pWindow),
            textureHolder(&pTextureHolder),
            fontHolder(&pFontHolder),
            soundHolder(&pSoundHolder),
            currentGameScreen(gameScreen){}

    Context(const Context& context) = delete;
};
