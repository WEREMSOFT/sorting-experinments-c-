//
// Created by Pablo Weremczuk on 2019-05-31.
//

#pragma once

#include "game_screen.hpp"
#define ENTITIES_TILE_SCREEN 25

void thread_draw_game_screen_tile(Tables &tables, Context &context) {

    sf::Clock clock;
    sf::RenderWindow &window = *context.window;
    FPSCounter::Struct fpsCounter;
    fpsCounter.font = &context.fontHolder->get(Fonts::PRESS_START);


    sf::Time sleepInterval = sf::seconds(DELAY_UPDATE);

    while (gameIsRunning && context.currentGameScreen == Screens::GAME_TILE) {

        clock.restart();

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

void game_screen_tile(Tables &tables, Context &context) {
    sf::RenderWindow &window = *context.window;

    std::thread thread_draw_local = std::thread(thread_draw_game_screen_tile, std::ref(tables), std::ref(context));
    sf::Event event;
    while (gameIsRunning && context.currentGameScreen == Screens::GAME_TILE) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                gameIsRunning = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            context.currentGameScreen = Screens::GAME;
        }
    }

    if (thread_draw_local.joinable()) thread_draw_local.join();
}


