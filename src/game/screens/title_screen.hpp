//
// Created by Pablo Weremczuk on 2019-05-31.
//

#pragma once


void title_screen(Context &context) {
    sf::RenderWindow &window = *context.window;
    sf::Event event;
    sf::Clock clock;
    sf::Time timeDifference;
    sf::Sprite backGround;

    context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE).setRepeated(true);
    backGround.setTexture(context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE));
    backGround.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            context.currentGameScreen = Screens::FIGHT;
        }

        sf::IntRect textureRect = backGround.getTextureRect();

        textureRect.left += 200.f * dt;
        textureRect.top += 80.f * dt;

        backGround.setTextureRect(textureRect);

        sf::Sprite titleImage;
        titleImage.setTexture(context.textureHolder->get(Textures::TITLE_MAIN_IMAGE));


        window.clear(sf::Color::Black);
        window.draw(backGround);
        window.draw(titleImage);
        window.display();
        timeDifference = clock.getElapsedTime();
        if (timeDifference.asSeconds() < DELAY_FRAME) {
            sf::sleep(sf::seconds(DELAY_FRAME - timeDifference.asSeconds()));
        }
    }
}




