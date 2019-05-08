//
// Created by Pablo Weremczuk on 2019-05-07.
//

#pragma once


#include <SFML/Graphics.hpp>
#include "entities/game_object.hpp"

struct Game {
    sf::Texture texture;
    std::vector<GameObject> gameObjects;

    sf::RectangleShape shape;
    sf::CircleShape circleShape;
    sf::Clock clock;
    sf::RenderWindow& window;
    Game(sf::RenderWindow& pWindow);
    Game(const Game& other) = delete;
    Game(const Game&& other) = delete;
    void update();
};


