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

    printf("Space in memory %lu\n", sizeof(tables));

    Context context(window, textureHolder, fontHolder);

    {
        LoadScreen::Struct loadScreen(context);
        LoadScreen::utils::loadResources(loadScreen);
        LoadScreen::utils::run(loadScreen);
    }

    tables.textureID[Entities::BACKGROUND] = Textures::BACKGROUND;
    tables.textureID[Entities::CAT] = Textures::CAT_1_ANIMATION;
    tables.textureID[Entities::HOUSE] = Textures::HOUSE;
    tables.textureID[Entities::TILE] = Textures::TITLE_BACKGROUND_TILE;


    utilsFunctions::rotate(tables, Entities::TILE, 45.f);
    utilsFunctions::setParent(tables, Entities::TILE, Entities::HOUSE);
    utilsFunctions::setParent(tables, Entities::CAT, Entities::TILE);



    {
        sf::Clock clock;
        clock.restart();
        while (window.isOpen())
        {
            float dt = clock.restart().asSeconds();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            window.clear(sf::Color::Black);

            utilsFunctions::rotate(tables, Entities::HOUSE, 45 * dt);
            utilsFunctions::rotate(tables, Entities::TILE, 45 * dt);
            utilsFunctions::rotate(tables, Entities::CAT, 45 * dt);
            utilsFunctions::draw(tables, context);
            window.display();
        }
    }

    window.close();

    return 0;
}