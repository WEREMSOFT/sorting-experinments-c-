//
// Created by Pablo Weremczuk on 2019-05-07.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../entities/game_object.hpp"
namespace utils {
    void draw(GameObject& entity, sf::RenderTarget& target, sf::RenderStates states) {
        target.draw(entity, states);
        if(entity.children.size() > 0){
            for(auto child: entity.children){
                states.transform *= entity.getTransform();
                utils::draw(child, target, states);
            }
        }
    }
}
