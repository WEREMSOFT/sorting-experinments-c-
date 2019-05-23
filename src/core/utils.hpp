//
// Created by Pablo Weremczuk on 2019-05-11.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../game/tables.hpp"

namespace utilsFunctions {

    inline void setDirtyFlag(Tables& tables, int id){
        tables.flags[id] |= Flags::DIRTY;
    }

    inline void clearDirtyFlag(Tables& tables, int id){
        tables.flags[id] &= ~Flags::DIRTY;
    }

    inline bool isDirty(Tables& tables, int id){
        return tables.flags[id] & Flags::DIRTY;
    }

    void centerOrigin(sf::Text &sprite) {
        sf::FloatRect bounds{sprite.getLocalBounds()};
        sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    void centerTextOnScreen(sf::Text &text, sf::RenderWindow &window){
        text.setPosition(window.getView().getSize().x / 2u, window.getView().getSize().y / 2u);
    }



    void setDirty(Tables& tables, int id) {
        if(tables.childCount[id] > 0) {
            for(int i = 0; i < tables.childCount[id]; i++){
                setDirty(tables, tables.childs[id][i]);
            }
        }
        setDirtyFlag(tables, id);
    }

    void recalculateWorldTransform(Tables& tables, const unsigned int id){
        if(tables.parent[id] != 0){
            printf("Parent Id %d\n", tables.parent[id]);
            tables.worldTransform[id] = tables.worldTransform[tables.parent[id]] * tables.transform[id];
        } else {
            tables.worldTransform[id] = tables.transform[id];
        }


        clearDirtyFlag(tables, id);

        if(tables.childCount[id] > 0){
            for(int i = 0; i < tables.childCount[id]; i++){
                recalculateWorldTransform(tables, tables.childs[id][i]);
            }
        }

    }

    void move(Tables& tables, const unsigned int id, const sf::Vector2f& moveVector) {
        tables.transform[id].translate(moveVector);
        setDirty(tables, id);
    }

    void centerOnScreen(Tables& tables, int id, sf::RenderWindow &window){
        tables.transform[id] = sf::Transform::Identity;
        utilsFunctions::move(tables, id, sf::Vector2f(window.getView().getSize().x / 2u, window.getView().getSize().y / 2u));
    }

    void rotate(Tables& tables, const unsigned int id, float angle) {
        tables.transform[id].rotate(angle, 32, 32);
        setDirty(tables, id);
    }

    void setChild(Tables& tables, const int id, const int parentID){
        tables.parent[id] = parentID;
        tables.childs[parentID][tables.childCount[parentID]] = id;
        tables.childCount[parentID]++;
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


