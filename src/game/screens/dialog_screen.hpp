//
// Created by Pablo Weremczuk on 2019-05-31.
//


#pragma once

#include <math.h>

namespace dialog_screen {

    void menu_item_callback_go_to_main(int index, Context &context) {
        printf("Menu selected!!: %d\n", index);
    }

    void loop(Context &context) {
        sf::RenderWindow &window = *context.window;
        sf::Event event;
        sf::Clock clock;
        sf::Time timeDifference;
        sf::Sprite backGround;

        dialog::Struct dialog("");
        dialog.offsetY = 250;

        dialog.children.push_back(dialog::Struct("Hello 1!"));
        dialog.children.push_back(dialog::Struct("Hello 2!"));
        dialog.children.push_back(dialog::Struct("Hello 3!"));
        dialog.children.push_back(dialog::Struct("Hello 4!"));

        backGround.setTexture(context.textureHolder->get(Textures::BACKGROUND_DIALOG));
        backGround.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

        sf::Sprite panda;
        panda.setTexture(context.textureHolder->get(Textures::PANDA));
        panda.setScale(.4, .4);
        sprite_center_origin(panda);
        sprite_center_on_screen(panda, *context.window);

        sf::Vector2f finalPositionPanda = panda.getPosition();

        panda.move(sf::Vector2f(0, 500));


        sf::RectangleShape textBackground(sf::Vector2f(window.getSize().x, 250));
        textBackground.setFillColor(sf::Color(0, 0, 0, 128));
        textBackground.move(0, 600);

        while (gameIsRunning && context.currentGameScreen == Screens::DIALOG) {
            float dt = clock.restart().asSeconds();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    gameIsRunning = false;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                gameIsRunning = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                context.currentGameScreen = Screens::TITLE;
            }

            sf::Vector2f actualPositionLeft = panda.getPosition();
            actualPositionLeft = finalPositionPanda - actualPositionLeft;
            panda.move(actualPositionLeft * (dt * 3));

            window.draw(backGround);
            window.draw(panda);

            window.draw(textBackground);

            dialog::draw(dialog, window, context.fontHolder->get(Fonts::PRESS_START));

            window.display();

            timeDifference = clock.getElapsedTime();
            if (timeDifference.asSeconds() < DELAY_FRAME) {
                sf::sleep(sf::seconds(DELAY_FRAME - timeDifference.asSeconds()));
            }
        }
        transition_exit(window);
    }
}




