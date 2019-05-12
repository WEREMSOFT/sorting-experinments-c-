#pragma once

#include <SFML/Graphics.hpp>
#include "game/resource_definitions.hpp"


struct Context {
    sf::RenderWindow *window;
    TextureHolder *textureHolder;
    FontHolder *fontHolder;

    Context(sf::RenderWindow &pWindow,
            TextureHolder &pTextureHolder,
            FontHolder &pFontHolder) :
            window(&pWindow),
            textureHolder(&pTextureHolder),
            fontHolder(&pFontHolder) {}

    Context(const Context& context) = delete;
};
