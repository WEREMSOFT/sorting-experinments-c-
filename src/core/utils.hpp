//
// Created by Pablo Weremczuk on 2019-05-11.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../game/tables.hpp"

namespace utilsFunctions {

    inline void setDirtyFlag(Tables& tables, uint id){
        tables.flags[id] |= Flags::DIRTY;
    }

    inline void clearDirtyFlag(Tables& tables, uint id){
        tables.flags[id] &= ~Flags::DIRTY;
    }

    inline bool isDirty(Tables& tables, uint id){
        return tables.flags[id] & Flags::DIRTY;
    }

    void centerOrigin(sf::Text &sprite) {
        sf::FloatRect bounds{sprite.getLocalBounds()};
        sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    void centerTextOnScreen(sf::Text &text, sf::RenderWindow &window){
        text.setPosition(window.getView().getSize().x / 2u, window.getView().getSize().y / 2u);
    }



    void setDirty(Tables& tables, uint id) {
        if(tables.childs.size() > 0) {
            for(auto child: tables.childs[id]){
                setDirty(tables, child);
            }
        }
        setDirtyFlag(tables, id);
    }

    void recalculateWorldTransform(Tables& tables, const uint id){
        if(tables.parent[id] != 0){
            tables.worldTransform[id] = tables.worldTransform[tables.parent[id]] * tables.transform[id];
        } else {
            tables.worldTransform[id] = tables.transform[id];
        }


        clearDirtyFlag(tables, id);

        if(tables.childs.size() > 0){
            for(int child: tables.childs[id]){
                recalculateWorldTransform(tables, child);
            }
        }

    }

    void move(Tables& tables, const uint id, const sf::Vector2f& moveVector) {
        tables.transform[id].translate(moveVector);
        setDirty(tables, id);
    }

    void centerOnScreen(Tables& tables, uint id, sf::RenderWindow &window){
        tables.transform[id] = sf::Transform::Identity;
        utilsFunctions::move(tables, id, sf::Vector2f(window.getView().getSize().x / 2u, window.getView().getSize().y / 2u));
    }

    void rotate(Tables& tables, const uint id, float angle) {
        tables.transform[id].rotate(angle, 32, 32);
        setDirty(tables, id);
    }

    void setChild(Tables& tables, const uint id, const int parentID){
        tables.parent[id] = parentID;
        tables.childs[parentID].emplace_back(id);
        setDirty(tables, id);
    }



    void draw(Tables& tables, Context& context){
        sf::RenderWindow& window = *context.window;
        sf::Sprite sprite;
        for(int i = 0; i < MAX_ENTITIES; i++){
            sprite.setTexture(context.textureHolder->get(tables.textureID[i]), true);
            window.draw(sprite, tables.worldTransform[i]);
        }
    }

    unsigned int PRNG(int max)
    {
        // our initial starting seed is 5323
        static unsigned int seed = 5323;

        // Take the current seed and generate a new value from it
        // Due to our use of large constants and overflow, it would be
        // hard for someone to casually predict what the next number is
        // going to be from the previous one.
        seed = 8253729 * seed + 2396403;

        // Take the seed and return a value between 0 and 32767
        return seed  % 32768 % max;
    }
};


