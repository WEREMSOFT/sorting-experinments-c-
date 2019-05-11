//
// Created by Pablo Weremczuk on 2019-05-07.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "../entities/game_object.hpp"

namespace utils {
    void draw(GameObject &entity, sf::RenderTarget &target, sf::RenderStates states, sf::Sprite& sprite) {
        sprite.setTexture(*entity.texture);
        target.draw(sprite, states.transform * entity.transform);

        if(entity.children.size() > 0){
            for(auto& child: entity.children){
                utils::draw(child, target, states.transform * entity.transform, sprite);
            }
        }
    }

    void rotateProportionalToDt(GameObject& entity, float angle, float dt) {
        entity.transform.rotate(angle * dt);
    }
}
