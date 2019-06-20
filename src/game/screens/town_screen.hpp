//
// Created by Pablo Weremczuk on 2019-05-31.
//


#pragma once

#include <math.h>

namespace town_screen {

    void menu_item_callback_go_to_main(int index, Context &context) {
        printf("Menu selected!!: %d\n", index);
    }

    void loop(Context &context) {
        sf::RenderWindow &window = *context.window;
        sf::Event event;
        sf::Clock clock;
        sf::Time timeDifference;
        sf::Sprite backGround;
        menu::Struct menu;

        {
            std::vector<std::string> menu_items_text = {
                "OPTION 1",
                "OPTION 2",
                "OPTION 3",
                "OPTION 4",
                "OPTION 5"
            };

            menu::create(menu, menu_items_text, context);
            menu.callback = menu_item_callback_go_to_main;
        }

        backGround.setTexture(context.textureHolder->get(Textures::BACKGROUND_MENU));
        backGround.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

        sf::Sprite titleImageRight;
        titleImageRight.setTexture(context.textureHolder->get(Textures::MENU_SIDE_IMAGE));
        titleImageRight.setScale(1.5, 1.5);

        sf::Sprite titleImageLeft;
        titleImageLeft.setTexture(context.textureHolder->get(Textures::MENU_SIDE_IMAGE));
        titleImageLeft.setScale(-1.5, 1.5);

        titleImageRight.move(sf::Vector2f(-100, 100.f));
        titleImageLeft.move(sf::Vector2f(1500, 100.f));

        sf::Vector2f finalPositionCharacterRight(700, 100);
        sf::Vector2f finalPositionCharacterLeft(500, 100);

        static int keys_state[255] = {0};

        const int max_menu_items = menu.items.size();

        while (gameIsRunning && context.currentGameScreen == Screens::MENU) {
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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !keys_state[sf::Keyboard::Up]) {
                menu.selectedIndex--;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !keys_state[sf::Keyboard::Down]) {
                menu.selectedIndex++;
            }

            menu.selectedIndex = std::min(std::max(menu.selectedIndex, 0), max_menu_items - 1);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !keys_state[sf::Keyboard::Enter]) {
                menu.callback(menu.selectedIndex, context);
            }

            // Clear outlines on menu
            for (int i = 0; i < max_menu_items; i++) {
                menu.items[i].setOutlineThickness(0);
                menu.items[i].setFillColor(sf::Color::White);
            }

            menu.items[menu.selectedIndex].setOutlineColor(sf::Color::Black);
            menu.items[menu.selectedIndex].setOutlineThickness(5);
            menu.items[menu.selectedIndex].setFillColor(sf::Color::Yellow);


            sf::Vector2f actualPositionRight = titleImageRight.getPosition();
            actualPositionRight = finalPositionCharacterRight - actualPositionRight;

            sf::Vector2f actualPositionLeft = titleImageLeft.getPosition();
            actualPositionLeft = finalPositionCharacterLeft - actualPositionLeft;


            titleImageRight.move(actualPositionRight * (dt * 3));
            titleImageLeft.move(actualPositionLeft * (dt * 3));

            window.draw(backGround);
            window.draw(titleImageRight);
            window.draw(titleImageLeft);

            keys_state[keys::Up] = isKeyDown(keys::Up);
            keys_state[keys::Down] = isKeyDown(keys::Down);
            keys_state[keys::Enter] = isKeyDown(keys::Enter);

            for (int i = 0; i < max_menu_items; i++) {
                window.draw(menu.items[i]);
            }

            window.display();
            timeDifference = clock.getElapsedTime();
            if (timeDifference.asSeconds() < DELAY_FRAME) {
                sf::sleep(sf::seconds(DELAY_FRAME - timeDifference.asSeconds()));
            }
        }
    }
}




