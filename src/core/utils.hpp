//
// Created by Pablo Weremczuk on 2019-05-11.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../game/tables.hpp"

// ## SORTING

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

// ## SPRITE

void sprite_center_origin(sf::Sprite &sprite) {
    sf::FloatRect bounds{sprite.getLocalBounds()};
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void sprite_center_on_screen(sf::Sprite& sprite, sf::RenderWindow &window) {
    sprite.move(sf::Vector2f(window.getView().getSize().x / 2u, window.getView().getSize().y / 2u));
}

// ## ENTITY


// ## Text

void text_center_on_screen(sf::Text &text, sf::RenderWindow &window) {
    text.setPosition(window.getView().getSize().x / 2u, window.getView().getSize().y / 2u);
}


void text_center_origin(sf::Text &text) {
    sf::FloatRect bounds{text.getLocalBounds()};
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}
