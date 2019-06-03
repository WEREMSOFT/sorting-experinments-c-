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

        sortUtils::sortByZIndex(tables);

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


    cat::Animations cat_animations(cat::CatAnimations::ANIM_COUNT);
    cat::animations_init(cat_animations, context);

    cat::state_to_idle(tables, Entities::CAT, cat_animations);

    tables[Entities::CAT].animation = cat_animations[cat::CatAnimations::ANIM_IDLE];


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

        gameUtils::handleKeyboardEvent(tables, Entities::CAT, dt);

        switch(tables[Entities::CAT].state){
            case cat::CatStates::IDLE:
                cat::state_process_idle(tables, Entities::CAT, cat_animations);
                break;
            case cat::CatStates::WALKING:
                cat::state_process_walking(tables, Entities::CAT, cat_animations);
                break;
        }
        gameUtils::handleAnimation(tables, Entities::CAT, dt);

        sortUtils::sortByDirty(tables);
        transformUtils::recalculateWorldTransforms(tables, gameUtils::findFirstDirty(tables));

        // If I updated too fast, then sleep for the rest of the frame (saves battery)
        sf::Time elapsedTime = clock.getElapsedTime();

        if (elapsedTime.asSeconds() < DELAY_UPDATE) {
            sf::sleep(sf::seconds(DELAY_UPDATE));
        }

    }

    if (myDrawThread.joinable()) myDrawThread.join();
}
