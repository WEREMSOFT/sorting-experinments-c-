//
// Created by Pablo Weremczuk on 2019-05-31.
//


#pragma once

namespace town_screen {

    enum MenuItems {
        FIGHT,
        MAIN,
        MENU_ITEMS_COUNT
    };

    void game_loop(Context &context) {
        sf::RenderWindow &window = *context.window;
        sf::Event event;
        sf::Clock clock;
        sf::Time timeDifference;
        sf::Sprite backGround;

        std::string menuItemsText[MENU_ITEMS_COUNT] = {
                "GO TO FIGHT!",
                "GO TO MAIN!"
        };

        std::vector<sf::Text> menuItems(MenuItems::MENU_ITEMS_COUNT);



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


        menuItems[MenuItems::FIGHT].setFont(context.fontHolder->get(Fonts::PRESS_START));
        menuItems[MenuItems::FIGHT].setString(menuItemsText[MenuItems::FIGHT]);
        menuItems[MenuItems::FIGHT].setCharacterSize(50);
        text_center_origin(menuItems[MenuItems::FIGHT]);
        text_center_on_screen(menuItems[MenuItems::FIGHT], *context.window);
        menuItems[MAIN].move(0, menuItems[FIGHT].getLocalBounds().height * FIGHT);

        menuItems[MenuItems::MAIN].setFont(context.fontHolder->get(Fonts::PRESS_START));
        menuItems[MenuItems::MAIN].setString(menuItemsText[MenuItems::MAIN]);
        menuItems[MenuItems::MAIN].setCharacterSize(50);
        text_center_origin(menuItems[MenuItems::MAIN]);
        text_center_on_screen(menuItems[MenuItems::MAIN], *context.window);
        menuItems[MAIN].move(0, menuItems[MAIN].getLocalBounds().height * MAIN);

        sf::RectangleShape menuSelector;

        menuSelector.setSize(sf::Vector2f(menuItems[MenuItems::FIGHT].getLocalBounds().width, menuItems[MenuItems::FIGHT].getLocalBounds().height));
        menuSelector.setFillColor(sf::Color::Black);

        menuSelector.setOrigin(menuSelector.getSize().x / 2, menuSelector.getSize().y / 2);

        menuSelector.setPosition(menuItems[MenuItems::FIGHT].getPosition().x, menuItems[MenuItems::FIGHT].getPosition().y);


        static int keys_state[255] = {0};

        while (gameIsRunning && context.currentGameScreen == Screens::TOWN) {
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

                menuSelector.move(0, -menuSelector.getSize().y);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !keys_state[sf::Keyboard::Down]) {
                menuSelector.move(0, menuSelector.getSize().y);
            }

            sf::Vector2f actualPositionRight = titleImageRight.getPosition();
            actualPositionRight = finalPositionCharacterRight - actualPositionRight;

            sf::Vector2f actualPositionLeft = titleImageLeft.getPosition();
            actualPositionLeft = finalPositionCharacterLeft - actualPositionLeft;




            titleImageRight.move(actualPositionRight * (dt * 3));
            titleImageLeft.move(actualPositionLeft * (dt * 3));

            window.draw(backGround);
            window.draw(titleImageRight);
            window.draw(titleImageLeft);
            window.draw(menuSelector);

            keys_state[keys::Up] = isKeyDown(keys::Up);
            keys_state[keys::Down] = isKeyDown(keys::Down);

            for(int i = 0; i < MENU_ITEMS_COUNT; i++){
                window.draw(menuItems[i]);
            }

            window.display();
            timeDifference = clock.getElapsedTime();
            if (timeDifference.asSeconds() < DELAY_FRAME) {
                sf::sleep(sf::seconds(DELAY_FRAME - timeDifference.asSeconds()));
            }
        }
    }
}




