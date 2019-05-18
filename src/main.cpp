#include <iostream>
#include <SFML/Graphics.hpp>
#include "game/context.hpp"
#include "game/load_screen.hpp"
#include "game/tables.hpp"
#include "core/debug/fps_counter.hpp"
#include <functional>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Purfectly Safe", sf::Style::Fullscreen);

    TextureHolder textureHolder;
    FontHolder fontHolder;
    Tables tables;

    printf("Space in memory %lu\n", sizeof(tables));

    Context context(window, textureHolder, fontHolder);
    // At the end of this scope, the loading screen will be removed from the stack.
    {
        LoadScreen::Struct loadScreen(context);
        LoadScreen::utils::loadResources(loadScreen);
        LoadScreen::utils::run(loadScreen);
    }


//    utilsFunctions::setParent(tables, Entities::TILE, Entities::CAT);
//    utilsFunctions::setParent(tables, Entities::TILE1, Entities::TILE);
//    utilsFunctions::setParent(tables, Entities::TILE2, Entities::TILE1);
//    utilsFunctions::setParent(tables, Entities::TILE3, Entities::TILE2);
//    utilsFunctions::setParent(tables, Entities::TILE4, Entities::TILE3);
//    utilsFunctions::setParent(tables, Entities::TILE5, Entities::TILE4);
//    utilsFunctions::setParent(tables, Entities::TILE6, Entities::TILE5);
//
//    utilsFunctions::move(tables, Entities::CAT, sf::Vector2f(200, 200));
//    utilsFunctions::move(tables, Entities::TILE, sf::Vector2f(64, 64));
//    utilsFunctions::move(tables, Entities::TILE1, sf::Vector2f(64, 64));
//    utilsFunctions::move(tables, Entities::TILE2, sf::Vector2f(64, 64));
//    utilsFunctions::move(tables, Entities::TILE3, sf::Vector2f(64, 64));
//    utilsFunctions::move(tables, Entities::TILE4, sf::Vector2f(64, 64));
//    utilsFunctions::move(tables, Entities::TILE5, sf::Vector2f(64, 64));
//    utilsFunctions::move(tables, Entities::TILE6, sf::Vector2f(64, 64));

    for(int i = 0; i < MAX_ENTITIES; i ++){
        utilsFunctions::move(tables, i, sf::Vector2f(utilsFunctions::PRNG(640), utilsFunctions::PRNG(640)));
    }


    // This is a scope, All objects created inside will be destroyed on the closing bracket.
    {
        FPSCounter::Struct fpsCounter;
        fpsCounter.font = &fontHolder.get(Fonts::PRESS_START);
        sf::Clock clock;
        float dt = clock.restart().asSeconds();

        FPSCounter::utils::initialize(fpsCounter);


        std::function<void(Tables&, sf::RenderWindow&)> updateR = [](Tables& tables, sf::RenderWindow& window) -> void {
            sf::Clock clock;
            while (window.isOpen()) {
                float dt = clock.restart().asSeconds();
//                utilsFunctions::rotate(tables, Entities::CAT, 45 * dt);
//                utilsFunctions::rotate(tables, Entities::TILE, 45 * dt);
//                utilsFunctions::rotate(tables, Entities::TILE1, 45 * dt);
//                utilsFunctions::rotate(tables, Entities::TILE2, 45 * dt);
//                utilsFunctions::rotate(tables, Entities::TILE3, 45 * dt);
//                utilsFunctions::rotate(tables, Entities::TILE4, 45 * dt);
//                utilsFunctions::rotate(tables, Entities::TILE5, 45 * dt);
//                utilsFunctions::rotate(tables, Entities::TILE6, 45 * dt);

                for(int i = 0; i < MAX_ENTITIES; i++){
                    utilsFunctions::rotate(tables, i, 45 * dt);
                }
            }
        };

        std::thread myUpdate(updateR, std::ref(tables), std::ref(window));
        while (window.isOpen())
        {
            dt = clock.restart().asSeconds();
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

//            utilsFunctions::rotate(tables, Entities::HOUSE, 45 * dt);
//            utilsFunctions::rotate(tables, Entities::TILE, 45 * dt);
//            utilsFunctions::rotate(tables, Entities::TILE1, 45 * dt);
//            utilsFunctions::rotate(tables, Entities::TILE2, 45 * dt);
//            utilsFunctions::rotate(tables, Entities::TILE3, 45 * dt);
//            utilsFunctions::rotate(tables, Entities::TILE4, 45 * dt);
//            utilsFunctions::rotate(tables, Entities::TILE5, 45 * dt);
//            utilsFunctions::rotate(tables, Entities::TILE6, 45 * dt);


            utilsFunctions::drawN(tables, context, HALF_MAX, MAX_ENTITIES);
            FPSCounter::utils::recalculateFPS(fpsCounter);
            FPSCounter::utils::draw(fpsCounter, window);
            window.display();
        }
        if(myUpdate.joinable()) myUpdate.join();
    }

    window.close();

    return 0;
}