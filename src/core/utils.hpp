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

void transition_exit(sf::RenderWindow &window) {
    sf::Clock clock;
    sf::Time timeDifference;
    sf::RectangleShape shade_up;
    sf::RectangleShape shade_down;

    bool shade_is_open = true;

    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);

    texture.update(window);

    sf::Sprite background;
    background.setTexture(texture);



    sf::Vector2f size_screen = sf::Vector2f(window.getDefaultView().getSize());

    shade_up.setSize(size_screen);
    shade_down.setSize(size_screen);

    shade_up.setFillColor(sf::Color::Black);
    shade_down.setFillColor(sf::Color::Black);

    shade_up.move(0, -shade_up.getSize().y);
    shade_down.move(0, window.getDefaultView().getSize().y);


    const int shade_speed = 1000;

    float scaleX = window.getDefaultView().getSize().x / window.getSize().x;
    float scaleY = window.getDefaultView().getSize().y / window.getSize().y;

    background.setScale(scaleX, scaleY);

    sf::Event event;
    while(gameIsRunning && shade_is_open){
        float dt = clock.restart().asSeconds();
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

            if(sf::Event::Resized) {
                scaleX = window.getDefaultView().getSize().x / window.getSize().x;
                scaleY = window.getDefaultView().getSize().y / window.getSize().y;

                background.setScale(scaleX, scaleY);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            gameIsRunning = false;
        }

        shade_down.move(0, -shade_speed * dt);
        shade_up.move(0, shade_speed * dt);

        if( shade_down.getPosition().y <= size_screen.y / 2 ){
            shade_is_open = false;
        }

        window.clear();
        window.draw(background);
        window.draw(shade_up);
        window.draw(shade_down);
        window.display();

        timeDifference = clock.getElapsedTime();
        if (timeDifference.asSeconds() < DELAY_FRAME) {
            sf::sleep(sf::seconds(DELAY_FRAME - timeDifference.asSeconds()));
        }
    }


}


void transition_enter(sf::RenderWindow &window) {
    sf::Clock clock;
    sf::Time timeDifference;
    sf::RectangleShape shade_up;
    sf::RectangleShape shade_down;

    bool shade_is_closed = true;

    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);

    texture.update(window);

    sf::Sprite background;
    background.setTexture(texture);



    sf::Vector2f size_screen = sf::Vector2f(window.getDefaultView().getSize());
    size_screen.y /= 2;

    shade_up.setSize(size_screen);
    shade_down.setSize(size_screen);

    shade_up.setFillColor(sf::Color::Black);
    shade_down.setFillColor(sf::Color::Black);

    shade_down.move(0, window.getDefaultView().getSize().y / 2);


    const int shade_speed = 1000;

    float scaleX = window.getDefaultView().getSize().x / window.getSize().x;
    float scaleY = window.getDefaultView().getSize().y / window.getSize().y;

    background.setScale(scaleX, scaleY);

    sf::Event event;
    while(gameIsRunning && shade_is_closed){
        float dt = clock.restart().asSeconds();
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

            if(sf::Event::Resized) {
                scaleX = window.getDefaultView().getSize().x / window.getSize().x;
                scaleY = window.getDefaultView().getSize().y / window.getSize().y;

                background.setScale(scaleX, scaleY);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            gameIsRunning = false;
        }

        shade_down.move(0, shade_speed * dt);
        shade_up.move(0, -shade_speed * dt);

        if( shade_up.getPosition().y <= -size_screen.y ){
            shade_is_closed = false;
        }

        window.clear();
        window.draw(background);
        window.draw(shade_up);
        window.draw(shade_down);
        window.display();

        timeDifference = clock.getElapsedTime();
        if (timeDifference.asSeconds() < DELAY_FRAME) {
            sf::sleep(sf::seconds(DELAY_FRAME - timeDifference.asSeconds()));
        }
    }


}