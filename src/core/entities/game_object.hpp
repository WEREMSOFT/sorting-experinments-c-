//
// Created by Pablo Weremczuk on 2019-05-07.
//

#pragma once
#include <SFML/Graphics.hpp>

namespace GameObject {
    struct Struct{
        std::vector<Struct> children;
        sf::RenderStates states;
        const sf::Texture* texture;
        sf::Transform transform;

        Struct(){}

        Struct(const sf::Texture* pTexture) {
            texture = pTexture;
        }

    };

    namespace utils {
        void initialize(GameObject::Struct* go, const sf::Texture* pTexture){
            go->texture = pTexture;
        }

        void rotate(std::vector<Struct> &gos, std::vector<Struct>::iterator current, float angle, float dt) {
            if(gos.end() == current) return;
            current->transform.rotate(angle * dt);
            if(!current->children.empty())
                rotate(current->children, current->children.begin(), angle, dt);

            rotate(gos, ++current, angle, dt);
        }

        void draw(std::vector<Struct> &gos, std::vector<Struct>::iterator current, sf::RenderTarget &target,
                  sf::RenderStates states, sf::Sprite &sprite) {
            if(gos.end() == current) return;

            sprite.setTexture(*current->texture, true);
            target.draw(sprite, states.transform * current->transform);

            if(!current->children.empty()) {
                sf::RenderStates childTransformStates = states;
                childTransformStates.transform *= current->transform;
                draw(current->children, current->children.begin(), target, childTransformStates, sprite);
            }

            draw(gos, ++current, target, states, sprite);
        }
    }

}

