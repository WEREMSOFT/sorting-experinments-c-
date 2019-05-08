//
// Created by Pablo Weremczuk on 2019-05-07.
//

#pragma once
#include <SFML/Graphics.hpp>

struct GameObject: sf::Sprite {
    std::vector<GameObject> children;
    sf::RenderStates states;

    explicit GameObject(const sf::Texture& texture);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates pStates);

    void addChild(sf::Texture& texture);

};
