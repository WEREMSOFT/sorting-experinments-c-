//
// Created by Pablo Weremczuk on 2019-05-11.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../game/tables.hpp"

typedef unsigned int uint;

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

    void centerOnScreen(sf::Text &text, sf::Window& window){
        text.setPosition(window.getSize().x / 2u, window.getSize().y / 2u);
    }

    void setDirty(Tables& tables, uint id) {
        if(!(tables.flags[id] & Flags::HAS_CHILDS)) {
            setDirtyFlag(tables, id);
            return;
        }

        for(uint i = 0; i < Entities::ENTITIES_COUNT; i++){
            if( tables.parent[i] == id && !isDirty(tables, i)) {
                setDirty(tables, i);
            }
        }
        setDirtyFlag(tables, id);
    }

    void recalculateWorldTransform(Tables& tables, const unsigned int id){
        if(tables.parent[id] == 0) {
            tables.worldTransform[id] = tables.transform[id];
            return;
        };

        if(tables.flags[tables.parent[id]] & Flags::DIRTY) {
            recalculateWorldTransform(tables, tables.parent[id]);
        }

        tables.worldTransform[id] = tables.worldTransform[tables.parent[id]] * tables.transform[id];
        clearDirtyFlag(tables, id);
    }

    void move(Tables& tables, const unsigned int id, const sf::Vector2f& moveVector) {
        tables.transform[id].translate(moveVector);
        setDirty(tables, id);
    }

    void rotate(Tables& tables, const unsigned int id, float angle) {
        tables.transform[id].rotate(angle);
        setDirty(tables, id);
    }

    void setParent(Tables& tables, const uint id, const uint parentID){
        tables.parent[id] = static_cast<Entities>(parentID);
        setDirty(tables, id);
        tables.flags[parentID] |= Flags::HAS_CHILDS;
    }



    void draw(Tables& tables, Context& context){
        sf::RenderWindow& window = *context.window;
        sf::Sprite sprite;
        for(int i = 0; i < Entities::ENTITIES_COUNT; i++){

            if(tables.flags[i] & Flags::DIRTY){
                recalculateWorldTransform(tables, i);
            }

            sprite.setTexture(context.textureHolder->get(tables.textureID[i]), true);
            window.draw(sprite, tables.worldTransform[i]);
        }


    }
};


