//
// Created by Pablo Weremczuk on 2019-05-11.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../game/tables.hpp"

namespace utilsFunctions {
    sf::Sprite sprite;
    void draw(std::vector<GameObject>& tables, Context& context, int begin, int end){
        for(int i = begin; i < end; i++){
            sprite.setTexture(context.textureHolder->get(tables[i].textureID));
            context.window->draw(sprite, tables[i].worldTransform);
        }
    }

    void centerOrigin(sf::Text &sprite) {
        sf::FloatRect bounds{sprite.getLocalBounds()};
        sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    void centerTextOnScreen(sf::Text &text, sf::RenderWindow &window){
        text.setPosition(window.getView().getSize().x / 2u, window.getView().getSize().y / 2u);
    }


    inline void setDirtyFlag(Tables& tables, uint id){
        tables[id].flags |= Flags::DIRTY;
    }

    inline void clearDirtyFlag(Tables& tables, uint id){
        tables[id].flags &= ~Flags::DIRTY;
    }

    inline bool isDirty(Tables& tables, uint id){
        return tables[id].flags & Flags::DIRTY;
    }


    void setDirty(Tables& tables, uint id) {
        if(tables[id].children.size() > 0) {
            for(auto child: tables[id].children){
                setDirty(tables, child);
            }
        }
        setDirtyFlag(tables, id);
    }

    void move(Tables& tables, const uint id, const sf::Vector2f& moveVector) {
        tables[id].transform.translate(moveVector);
        setDirty(tables, id);
    }

    void recalculateWorldTransform(Tables& tables, const uint id){
        if(tables[id].parent != 0){
            tables[id].worldTransform = tables[tables[id].parent].worldTransform * tables[id].transform;
        } else {
            tables[id].worldTransform = tables[id].transform;
        }


        clearDirtyFlag(tables, id);

        if(tables[id].children.size() > 0){
            for(int child: tables[id].children){
                recalculateWorldTransform(tables, child);
            }
        }

    }

    void recalculateWorldTransforms(Tables& tables, int firstDirty){
        for(int i = firstDirty; i < Entities::ENTITIES_COUNT; i++){
            recalculateWorldTransform(tables, i);
        }
    }

    void centerOnScreen(Tables& tables, uint id, sf::RenderWindow &window){
        tables[id].transform = sf::Transform::Identity;
        utilsFunctions::move(tables, id, sf::Vector2f(window.getView().getSize().x / 2u, window.getView().getSize().y / 2u));
    }

    void rotate(Tables& tables, const uint id, float angle) {
        tables[id].transform.rotate(angle, 32, 32);
        setDirty(tables, id);
    }

    void setChild(Tables& tables, const uint id, const int parentID){
        assert(id != parentID);
        tables[id].parent = parentID;
        tables[parentID].children.emplace_back(id);
        setDirty(tables, id);
    }

    void draw(Tables& tables, Context& context){
        sf::RenderWindow& window = *context.window;
        sf::Sprite sprite;
        if(window.isOpen()){
            for(int i = 0; i < MAX_ENTITIES_SOA; i++){
                sprite.setTexture(context.textureHolder->get(tables[i].textureID), true);
                if(tables[i].flags & Flags::ANIMATED){
                    sprite.setTextureRect(tables[i].animations.textureRect);
                    sprite.setOrigin(tables[i].animations.textureRect.width / 2.f, 0.f);
                    if(tables[i].flags & Flags::FLIPPED){
                        sprite.scale(-1, 1);
                    } else {
                        sprite.scale(1, 1);
                    }
                }
                window.draw(sprite, tables[i].worldTransform);
                sprite.setScale(1, 1);
            }
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
}

namespace sortUtils {

    void sortByDirty(Tables& tables){
        auto compareLambda = [](const GameObject& a, const GameObject& b) -> bool {
            return ((a.flags & Flags::DIRTY) < (b.flags & Flags::DIRTY));
        };

        std::sort(tables.begin(), tables.begin() + Entities::ENTITIES_COUNT, compareLambda);
    }

    void sortByType(Tables& tables) {
        auto compareLambda = [](const GameObject& a, const GameObject& b) -> bool {
            return (a.type < b.type);
        };

        std::sort(tables.begin(), tables.begin() + Entities::ENTITIES_COUNT, compareLambda);
    }

    void sortByZIndex(Tables& tables){
        auto compareLambda = [](const GameObject& a, const GameObject& b) -> bool {
            return (a.zIndex < b.zIndex);
        };

        std::sort(tables.begin(), tables.begin() + (int)Entities::ENTITIES_COUNT, compareLambda);
    }
}

namespace gameUtils {
    void setTypeEqualsIndex(Tables &tables) {
        for(int i = 0; i < Entities::ENTITIES_COUNT; i++){
            tables[i].type = i;
        }
    }

    void handleKeyboardEvent(Tables& tables, int id, float dt){
        const float thingySpeed = 1000;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            utilsFunctions::move(tables, id, sf::Vector2f(-thingySpeed * dt, 0));
            tables[id].flags &= ~Flags::FLIPPED;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            utilsFunctions::move(tables, id, sf::Vector2f(thingySpeed * dt, 0));
            tables[id].flags |= Flags::FLIPPED;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            utilsFunctions::move(tables, id, sf::Vector2f(0, -thingySpeed * dt));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            utilsFunctions::move(tables, id, sf::Vector2f(0, thingySpeed * dt));
        }

    }

    int findFirstDirty(Tables& tables){
        for(int i = Entities::ENTITIES_COUNT - 1; i >= 0; i--) {
            if(!utilsFunctions::isDirty(tables, i)) return i;
        }

        return -1;
    }
}