#include <iostream>
#include <SFML/Graphics.hpp>
#include "game/context.hpp"
#include "game/load_screen.hpp"
#include "game/tables.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1230, 768), "Purfectly Safe", sf::Style::Default);

    TextureHolder textureHolder;
    FontHolder fontHolder;
    Tables tables;
    printf("Space in memory %d", sizeof(tables));
    Entity entities[3];

    Context context(window, textureHolder, fontHolder);

    {
        LoadScreen::Struct loadScreen(context);
        LoadScreen::utils::loadResources(loadScreen);
        LoadScreen::utils::run(loadScreen);
    }

    {
        
    }

    window.close();

    return 0;
}