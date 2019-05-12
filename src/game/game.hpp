//
// Created by Pablo Weremczuk on 2019-05-07.
//

#pragma once


#include <SFML/Graphics.hpp>
#include "../core/entities/game_object.hpp"
#include "../core/debug/fps_counter.hpp"
#include "../context.hpp"

#define ANGLE 45

namespace Game{
    struct Struct {
        Context& context;
        std::vector<GameObject::Struct> gameObjects;
        sf::Sprite sprite;
        FPSCounter::Struct fpsCounter;
        sf::Clock clock;
        sf::RenderWindow &window;

        Struct(Context& context) : context(context), window(*context.window) {
            gameObjects.reserve(2);
            clock.restart();

            fpsCounter.font = &context.fontHolder->get(Fonts::PRESS_START);

            gameObjects.emplace_back(&context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE));
            gameObjects.back().transform.translate(200, 300);

            gameObjects.emplace_back(&context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE));
            gameObjects.back().transform.translate(600, 300);

            FPSCounter::utils::initialize(fpsCounter);
        }
    };

    namespace utils {
        void update(Struct& game) {

            auto dt = game.clock.restart().asSeconds();
            game.window.clear(sf::Color::Black);

            GameObject::utils::rotate(game.gameObjects, game.gameObjects.begin(), ANGLE, dt);

            GameObject::utils::draw(game.gameObjects, game.gameObjects.begin(), game.window, sf::RenderStates::Default, game.sprite);
            FPSCounter::utils::recalculateFPS(game.fpsCounter);
            FPSCounter::utils::draw(game.fpsCounter, game.window);

            game.window.display();

        }

        void createRecursiveHierarchy(GameObject::Struct &go, int ammount, int direction = 1) {
            if (ammount == 0) return;

            go.children.emplace_back(go.texture);
            go.children.back().transform.translate(64 * direction, 64 * direction);
            createRecursiveHierarchy(go.children.back(), --ammount);
        }
    }
}



