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
        menu::Struct menu;

        {
            std::vector<std::string> menu_items_text = {
                    "HI CUTIE!!",
                    "FUCK OFF CARPET FACE!!",
            };

            menu::create(menu, menu_items_text, context, {0, 270}, 30);
            menu.callback = menu_item_callback_go_to_main;
        }

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

        const int max_menu_items = menu.items.size();

        while (gameIsRunning && context.currentGameScreen == Screens::DIALOG) {
            float dt = clock.restart().asSeconds();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    gameIsRunning = false;
                }
            }

            handle_menu_control(menu, context, max_menu_items);

            sf::Vector2f actualPositionLeft = panda.getPosition();
            actualPositionLeft = finalPositionPanda - actualPositionLeft;
            panda.move(actualPositionLeft * (dt * 3));

            window.draw(backGround);
            window.draw(panda);

            window.draw(textBackground);
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




