//
// Created by Pablo Weremczuk on 2019-05-07.
//

#pragma once


#include <SFML/Graphics.hpp>
#include "entities/game_object.hpp"
#include "functions/functions.hpp"

struct Game {
    sf::Texture texture;
    std::vector<GameObject> gameObjects;
    sf::Sprite sprite;

    sf::RectangleShape shape;
    sf::CircleShape circleShape;
    sf::Clock clock;
    sf::RenderWindow &window;

    void rotate(sf::Shape &entity, float dt) {
        entity.rotate(30.f * dt);
    }

    void rotateRecursive(GameObject &go, float angle, float dt) {
        go.transform.rotate(angle * dt);
        for (std::vector<GameObject>::iterator it = go.children.begin(); it != go.children.end(); ++it) {
            rotateRecursive(*it, angle, dt);
        }
    }

    void createRecursiveHierarchy(GameObject &go, int ammount, int direction = 1) {
        if (ammount == 0) return;

        go.children.emplace_back(go.texture);
        go.children.back().transform.translate(64 * direction, 64 * direction);
        createRecursiveHierarchy(go.children.back(), --ammount);
    }

    Game(sf::RenderWindow &pWindow) : window(pWindow) {
        clock.restart();

        texture.loadFromFile("assets/pattern_background.png");
        gameObjects.emplace_back(&texture);
        gameObjects.back().transform.translate(400, 300);

        createRecursiveHierarchy(gameObjects.back(), 5);

    }

    void update() {
        auto dt = clock.restart().asSeconds();
        window.clear(sf::Color::Black);

        rotateRecursive(gameObjects.back(), 45, dt);

        for (std::vector<GameObject>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
            utils::draw(*it, window, sf::RenderStates::Default, sprite);
        }

        window.display();

    }
};


