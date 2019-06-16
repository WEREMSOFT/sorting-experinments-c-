//
// Created by Pablo Weremczuk on 2019-05-11.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../game/tables.hpp"

// ## SORTING

inline int sort_by_dirty(Tables &tables) {
    auto compareLambda = [](const GameObject &a, const GameObject &b) -> bool {
        return ((a.flags & Flags::DIRTY) < (b.flags & Flags::DIRTY));
    };

    std::sort(tables.begin(), tables.end(), compareLambda);

    for (int i = 0; i < tables.size(); i++) {
        if (tables[i].flags & Flags::DIRTY) return i;
    }
    return 0;
}

int sort_by_animated(Tables &tables) {
    auto compareLambda = [](const GameObject &a, const GameObject &b) -> bool {
        return ((a.flags & Flags::ANIMATED) < (b.flags & Flags::ANIMATED));
    };

    std::sort(tables.begin(), tables.end(), compareLambda);

    for (int i = 0; i < tables.size(); i++) {
        if (tables[i].flags & Flags::ANIMATED) return i;
    }
    return 0;
}

namespace threads {
    void thread_print_position(Tables &tables, int id) {
        while (gameIsRunning) {
            sf::Vector2f position = tables[id].sprite.getPosition();
            printf("Position %f, %f\n", position.x, position.y);
        }
    }
}

unsigned int PRNG(int max) {
    // our initial starting seed is 5323
    static unsigned int seed = 5323;

    // Take the current seed and generate a new value from it
    // Due to our use of large constants and overflow, it would be
    // hard for someone to casually predict what the next number is
    // going to be from the previous one.
    seed = 8253729 * seed + 2396403;

    // Take the seed and return a value between 0 and 32767
    return seed % 32768 % max;
}

// ## ENTITY

void entity_center_on_screen(Tables &tables, uint id, sf::RenderWindow &window) {
    tables[id].sprite.move(sf::Vector2f(window.getView().getSize().x / 2u, window.getView().getSize().y / 2u));
}

void entity_handle_animation(Tables &tables, uint id, float dt) {
    Animation::utils::animation_process_frame(tables[id].animation, dt);
}

void entity_move(Tables &tables, const int id, const sf::Vector2f &moveVector) {
    tables[id].sprite.move(moveVector);
}

void entity_recalculate_world_transform(Tables &tables, int id) {

    if (tables[id].parent > -1) {
        entity_recalculate_world_transform(tables, tables[id].parent);
        tables[id].worldTransform =
                tables[tables[id].parent].worldTransform * tables[tables[id].parent].sprite.getTransform();
    } else {
        tables[id].worldTransform = sf::Transform::Identity;
    }

}

void entity_recalculate_world_transforms(Tables &tables) {
    for (int i = 0; i < tables.size(); i++) {
        entity_recalculate_world_transform(tables, i);
    }
}

void entity_rotate(Tables &tables, const uint id, float angle) {
    tables[id].sprite.rotate(angle);
}

void entity_set_child(Tables &tables, const uint id, const int parentID) {
    assert(id != parentID);
    tables[id].parent = parentID;
}

void entity_set_position(Tables &tables, int id, const sf::Vector2f &moveVector) {
    tables[id].sprite.setPosition(moveVector);
}

void entity_set_scale_based_on_flipped_flag(Tables& tables){
    for (int i = 0; i < tables.size(); i++) {
        if (tables[i].flags & Flags::FLIPPED) {
            tables[i].sprite.setScale(-1, tables[i].sprite.getScale().y);
        } else {
            tables[i].sprite.setScale(1, tables[i].sprite.getScale().y);
        }
    }
}
void entity_set_type_equals_index(Tables &tables) {
    for (int i = 0; i < tables.size(); i++) {
        tables[i].entity_type = i;
    }
}

void entity_set_zindex_equals_y(Tables &tables) {
    for (int i = 0; i < tables.size(); i++) {
        tables[i].zIndex = tables[i].sprite.getPosition().y;
    }
}

// ## CAT

typedef std::vector<Animation::Struct> AnimationVector;


void draw(std::vector<GameObject> &tables, Context &context, int begin, int end) {
    for (int i = begin; i < end; i++) {
        context.window->draw(tables[i].sprite, tables[i].worldTransform);
    }
}

void print_position(Tables &tables, int id) {
    sf::Vector2f position = tables[id].sprite.getPosition();
    printf("Position %f, %f\n", position.x, position.y);
}

void print_zindex(Tables &tables, int id) {
    printf("Z-Index %d\n", tables[id].zIndex);
}

void process_animations(Tables &tables, int firstAnimated) {
    {
        for (int i = firstAnimated; i < tables.size(); i++) {
            tables[i].sprite.setTextureRect(tables[i].animation.textureRect);
        }
    }
}

void sort_by_entity_type(Tables &tables) {
    auto compareLambda = [](const GameObject &a, const GameObject &b) -> bool {
        return (a.entity_type < b.entity_type);
    };

    std::sort(tables.begin(), tables.end(), compareLambda);
}

void sort_by_z_index(Tables &tables) {
    auto compareLambda = [](const GameObject &a, const GameObject &b) -> bool {
        return (a.zIndex < b.zIndex);
    };

    std::sort(tables.begin(), tables.end(), compareLambda);
}

void text_center_on_screen(sf::Text &text, sf::RenderWindow &window) {
    text.setPosition(window.getView().getSize().x / 2u, window.getView().getSize().y / 2u);
}


void text_center_origin(sf::Text &text) {
    sf::FloatRect bounds{text.getLocalBounds()};
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void tile_keyboard_event_handler(Tables &tables, int id) {
    tables[id].lastPosition = tables[id].sprite.getPosition();
    int thingySpeed = 128;

    static int lastStatusKeys[sf::Keyboard::KeyCount] = {0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !lastStatusKeys[sf::Keyboard::Left]) {
        entity_move(tables, id, sf::Vector2f(-thingySpeed, 0));
        tables[id].flags &= ~Flags::FLIPPED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !lastStatusKeys[sf::Keyboard::Right]) {
        entity_move(tables, id, sf::Vector2f(thingySpeed, 0));
        tables[id].flags |= Flags::FLIPPED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !lastStatusKeys[sf::Keyboard::Up]) {
        entity_move(tables, id, sf::Vector2f(0, -thingySpeed));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !lastStatusKeys[sf::Keyboard::Down]) {
        entity_move(tables, id, sf::Vector2f(0, thingySpeed));
    }

    lastStatusKeys[sf::Keyboard::Left] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    lastStatusKeys[sf::Keyboard::Right] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    lastStatusKeys[sf::Keyboard::Up] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    lastStatusKeys[sf::Keyboard::Down] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

