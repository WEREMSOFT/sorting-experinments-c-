//
// Created by Pablo Weremczuk on 2019-05-31.
//

#pragma once

namespace title_screen {
    void menu_item_callback_go_to_main(int index, Context &context) {
        context.currentGameScreen = index;
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
                    "Title!!",
                    "Town!!",
                    "Fight!!"
            };

            menu::create(menu, menu_items_text, context);
            menu.callback = menu_item_callback_go_to_main;
        }

        context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE).setRepeated(true);
        backGround.setTexture(context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE));
        backGround.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

        sf::Sprite titleImageRight;
        titleImageRight.setTexture(context.textureHolder->get(Textures::TITLE_MAIN_IMAGE));

        sf::Sprite titleImageLeft;
        titleImageLeft.setTexture(context.textureHolder->get(Textures::TITLE_MAIN_IMAGE));
        titleImageLeft.setScale(-1, 1);

        titleImageRight.move(sf::Vector2f(-100, 100.f));
        titleImageLeft.move(sf::Vector2f(1500, 100.f));

        sf::Vector2f finalPositionCharacterRight(600, 100);
        sf::Vector2f finalPositionCharacterLeft(600, 100);


        sf::Text introText;
        introText.setFont(context.fontHolder->get(Fonts::PRESS_START));
        introText.setString("GAME NAME");
        introText.setCharacterSize(50);
        text_center_origin(introText);
        text_center_on_screen(introText, *context.window);
        introText.move(0, -100);

        sf::Vector2f introTextFinalPosition = introText.getPosition();
        introText.setPosition(introTextFinalPosition.x, -500);

        static int keys_state[255] = {0};

        const int max_menu_items = menu.items.size();

        while (gameIsRunning && context.currentGameScreen == Screens::TITLE) {
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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                context.currentGameScreen = Screens::FIGHT;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                context.currentGameScreen = Screens::MENU;
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
            for(int i = 0; i < max_menu_items; i++){
                menu.items[i].setOutlineThickness(0);
            }

            menu.items[menu.selectedIndex].setOutlineColor(sf::Color::Black);
            menu.items[menu.selectedIndex].setOutlineThickness(5);

            sf::IntRect textureRect = backGround.getTextureRect();

            textureRect.left += 200.f * dt;
            textureRect.top += 80.f * dt;

            backGround.setTextureRect(textureRect);

            sf::Vector2f actualPositionRight = titleImageRight.getPosition();
            actualPositionRight = finalPositionCharacterRight - actualPositionRight;

            sf::Vector2f actualPositionLeft = titleImageLeft.getPosition();
            actualPositionLeft = finalPositionCharacterLeft - actualPositionLeft;

            sf::Vector2f actualPositionText = introText.getPosition();
            actualPositionText = introTextFinalPosition - actualPositionText;


            titleImageRight.move(actualPositionRight * (dt * 3));
            titleImageLeft.move(actualPositionLeft * (dt * 3));
            introText.move(actualPositionText * (dt * 3));

            window.draw(backGround);
            window.draw(titleImageRight);
            window.draw(titleImageLeft);
            window.draw(introText);

            for(int i = 0; i < max_menu_items; i++){
                window.draw(menu.items[i]);
            }

            window.display();

            keys_state[keys::Up] = isKeyDown(keys::Up);
            keys_state[keys::Down] = isKeyDown(keys::Down);
            keys_state[keys::Enter] = isKeyDown(keys::Enter);

            timeDifference = clock.getElapsedTime();
            if (timeDifference.asSeconds() < DELAY_FRAME) {
                sf::sleep(sf::seconds(DELAY_FRAME - timeDifference.asSeconds()));
            }
        }
    }
}



