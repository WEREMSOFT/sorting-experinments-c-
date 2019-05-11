//
// Created by Pablo Weremczuk on 2019-05-07.
//

#pragma once


#include <SFML/Graphics.hpp>
#include "../core/entities/game_object.hpp"
#include "../core/entities/fps_counter.hpp"

#define ANGLE 45

namespace Game{
    struct Struct {
        sf::Texture texture;
        sf::Font font;
        std::vector<GameObject::Struct> gameObjects;
        sf::Sprite sprite;
        FPSCounter::Struct fpsCounter;
        unsigned int steps = 0;
        sf::Clock clock;
        sf::RenderWindow &window;

        Struct(sf::RenderWindow &pWindow) : window(pWindow) {
            gameObjects.reserve(2);
            clock.restart();

            font.loadFromFile("assets/fonts/PressStart2P-Regular.ttf");
            texture.loadFromFile("assets/pattern_background.png");

            fpsCounter.font = &font;

            gameObjects.emplace_back(&texture);
            gameObjects.back().transform.translate(200, 300);

            gameObjects.emplace_back(&texture);
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



