//
// Created by Pablo Weremczuk on 2019-05-31.
//

#pragma once


void thread_draw_game_screen(Tables &tables, Context &context) {

    sf::Clock clock;
    sf::RenderWindow &window = *context.window;
    FPSCounter::Struct fpsCounter;
    fpsCounter.font = &context.fontHolder->get(Fonts::PRESS_START);


    sf::Time sleepInterval = sf::seconds(DELAY_UPDATE);

    while (gameIsRunning && context.currentGameScreen == Screens::GAME) {

        clock.restart();

        // recalculate transforms
        sortUtils::sortByDirty(tables);
        gameUtils::findFirstDirty(tables);

        sortUtils::sortByZIndex(tables);

        window.clear(sf::Color::Black);

        utilsFunctions::draw(tables, context, 0, Entities::ENTITIES_COUNT);

        FPSCounter::utils::recalculateFPS(fpsCounter);
        FPSCounter::utils::draw(fpsCounter, window);

        window.display();

        sf::Time elapsedTime = clock.restart();

        if (elapsedTime.asSeconds() < DELAY_FRAME) {
            sf::sleep(sleepInterval - elapsedTime);
        }
    }
}


void game_screen(Tables &tables, Context &context) {
    sf::RenderWindow &window = *context.window;
    sortUtils::sortByType(tables);


    transformUtils::setPosition(tables, Entities::TABLE, sf::Vector2f(500, 446));

    sf::Clock clock;

    std::thread myDrawThread(thread_draw_game_screen, std::ref(tables), std::ref(context));
    sf::Time sleepInterval = sf::seconds(.02f);

    sf::Event event;
    while (gameIsRunning && context.currentGameScreen == Screens::GAME) {
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


        float dt = clock.restart().asSeconds();

        sortUtils::sortByType(tables);
        gameUtils::handleAnimation(tables, Entities::CAT, dt);

        gameUtils::handleKeyboardEvent(tables, Entities::CAT, dt);
        sortUtils::sortByDirty(tables);
        transformUtils::recalculateWorldTransforms(tables, gameUtils::findFirstDirty(tables));

        sf::Time elapsedTime = clock.getElapsedTime();
        if (elapsedTime.asSeconds() < DELAY_UPDATE) {
            sf::sleep(sf::seconds(DELAY_UPDATE));
        }

    }

    if (myDrawThread.joinable()) myDrawThread.join();
}
