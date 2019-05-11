//
// Created by Pablo Weremczuk on 2019-05-07.
//

#pragma once
#include <SFML/Graphics.hpp>

struct GameObject{
    std::vector<GameObject> children;
    sf::RenderStates states;
    const sf::Texture* texture;
    sf::Transform transform;

    GameObject(){}

    GameObject(const sf::Texture* pTexture) {
        texture = pTexture;
    }

};
