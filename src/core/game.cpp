//
// Created by Pablo Weremczuk on 2019-05-07.
//

#include "game.hpp"
#include "stdio.h"
#include "entities/game_object.hpp"
#include "functions/functions.hpp"
#include <SFML/Graphics.hpp>

void rotate(sf::Shape& entity, float dt){
    entity.rotate(30.f * dt);
}


Game::Game(sf::RenderWindow& pWindow): window(pWindow) {
    clock.restart();

    texture.loadFromFile("assets/pattern_background.png");
    gameObjects.emplace_back(texture);
    gameObjects.back().move(30, 30);
    gameObjects.back().children.emplace_back(texture);
    gameObjects.back().children.back().setPosition(50, 50);

    printf("size %d\n", gameObjects.size());
}

void Game::update() {
    auto dt = clock.restart().asSeconds();
    window.clear(sf::Color::Black);

    for(auto go: gameObjects){
        utils::draw(go, window, sf::RenderStates::Default);
    }


    window.display();

}


