//
// Created by Pablo Weremczuk on 2019-05-07.
//

#pragma once


#include <SFML/Graphics.hpp>
#include "../core/entities/game_object.hpp"
#include "../core/debug/fps_counter.hpp"
#include "../context.hpp"
#include "../core/resources/animation.hpp"
#include "characters/cat.hpp"

#define ANGLE 45

namespace Game{


    struct Struct {
        Context& context;
        std::vector<GameObject::Struct> gameObjects;
        sf::Sprite sprite;
        sf::Sprite spriteBackground;
        sf::Sprite spriteHouse;
        Cat::Struct cat;
        FPSCounter::Struct fpsCounter;
        sf::Clock clock;
        sf::RenderWindow &window;

        Struct(Context& context) : context(context), window(*context.window) {
            gameObjects.reserve(3);
            clock.restart();

            Cat::utils::initializeAnimations(cat, context);

            cat.transform.translate(100, 100);
            gameObjects.emplace_back(cat);

            fpsCounter.font = &context.fontHolder->get(Fonts::PRESS_START);

            gameObjects.emplace_back(&context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE));
            gameObjects.back().transform.translate(200, 300);

            gameObjects.emplace_back(&context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE));
            gameObjects.back().transform.translate(600, 300);

            FPSCounter::utils::initialize(fpsCounter);

            spriteBackground.setTexture(context.textureHolder->get(Textures::BACKGROUND), true);
            spriteHouse.setTexture(context.textureHolder->get(Textures::HOUSE), true);

        }

        Struct(const Struct& other) = delete;
        Struct(const Struct&& other) = delete;
    };

    namespace utils {
        void update(Struct& game) {
            auto dt = game.clock.restart().asSeconds();
            GameObject::utils::rotate(game.gameObjects, game.gameObjects.begin(), ANGLE, dt);
            Animation::utils::processAnimationFrame(game.cat.animations[game.cat.currentAnimation], dt, game.cat);
        }

        void createRecursiveHierarchy(GameObject::Struct &go, int ammount, int direction = 1) {
            if (ammount == 0) return;

            go.children.emplace_back(go.texture);
            go.children.back().transform.translate(64 * direction, 64 * direction);
            createRecursiveHierarchy(go.children.back(), --ammount);
        }

        void draw(Game::Struct& game){
            game.window.draw(game.spriteBackground);
            game.window.draw(game.spriteHouse);

            GameObject::utils::draw(game.gameObjects, game.gameObjects.begin(), game.window, sf::RenderStates::Default, game.sprite);
            FPSCounter::utils::recalculateFPS(game.fpsCounter);
//            game.window.draw(game.cat.animations[game.cat.currentAnimation].sprite);
            FPSCounter::utils::draw(game.fpsCounter, game.window);

            game.window.display();
        }

        void run(Game::Struct& game){
            sf::RenderWindow& window = *game.context.window;
            unsigned int finished = false;
            // run the program as long as the window is open
            while (window.isOpen() && !finished)
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                        finished = true;
                    }
                }
                Game::utils::update(game);
                Game::utils::draw(game);
            }
        }
    }
}



