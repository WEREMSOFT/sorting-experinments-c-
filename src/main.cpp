#include <iostream>
#include <SFML/Graphics.hpp>
#include "game/context.hpp"
#include "game/load_screen.hpp"
#include "game/tables.hpp"
#include "core/debug/fps_counter.hpp"
#include <functional>
#include <mutex>

#define SCREEN_WITH 800
#define SCREEN_HEIGHT 600
#define FRAME_DELAY 0.016 // Millisecconds

namespace threads {
    void rotateAll(Tables &tables, sf::RenderWindow &window) {
        sf::Clock clock;
        std::mutex lockScopeHandler;
        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            lockScopeHandler.lock();
            for (int i = 0; i < MAX_ENTITIES; i++) {
                    utilsFunctions::rotate(tables, i, 45 * dt);
            }
            lockScopeHandler.unlock();
        }
    }

    void recalculateTransforms(Tables& tables, sf::RenderWindow &window){
        sf::Clock clock;

        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            for (int i = 0; i < MAX_ENTITIES; i++) {
                if (tables.flags[i] & Flags::DIRTY) {
                    utilsFunctions::recalculateWorldTransform(tables, i);
                }
            }
        }
    }
}


Context &loadScreen(Context &context) {
    {
        LoadScreen::Struct loadScreen(context);
        LoadScreen::utils::loadResources(loadScreen);
        LoadScreen::utils::run(loadScreen);
    }
    return context;
}


int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WITH, SCREEN_HEIGHT), "Purfectly Safe", sf::Style::Fullscreen);
    sf::View view;
    sf::Clock clock;
    TextureHolder textureHolder;
    FontHolder fontHolder;
    Tables tables;

    printf("Space in memory %lu\n", sizeof(tables));

    Context context(window, textureHolder, fontHolder);
    // At the end of this scope, the loading screen will be removed from the stack.
    context = loadScreen(context);
    // Move all 32 pixels down and right
    {
        sf::Vector2f moveVector(32, 32);

        utilsFunctions::centerOnScreen(tables, 0, window);

        for(int i = 1; i < MAX_ENTITIES; i++){
            utilsFunctions::move(tables, i, moveVector);
        }
    }

    // set parent child for all
    {
        for(int i = 0; i < MAX_ENTITIES; i += 10){
            utilsFunctions::move(tables, i, sf::Vector2f(i / 20, 100));
            for(int j=i; j < i + 9; j++){
                utilsFunctions::setChild(tables, j + 1, j);
            }
        }
    }

    // This is a scope, All objects created inside will be destroyed on the closing bracket.
    {
        sf::Clock clock;
        FPSCounter::Struct fpsCounter;
        fpsCounter.font = &fontHolder.get(Fonts::PRESS_START);
        float acumulatedDelta = 0;

        FPSCounter::utils::initialize(fpsCounter);

        std::thread myUpdate(threads::rotateAll, std::ref(tables), std::ref(window));
        std::thread myRecalculateTransforms(threads::recalculateTransforms, std::ref(tables), std::ref(window));

        while (window.isOpen()) {
            float dt = clock.restart().asSeconds();
            acumulatedDelta += dt;
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            if (acumulatedDelta >= FRAME_DELAY) {
                acumulatedDelta = 0;
                window.clear(sf::Color::Black);
                utilsFunctions::draw(tables, context);
                FPSCounter::utils::recalculateFPS(fpsCounter);
                FPSCounter::utils::draw(fpsCounter, window);
                window.display();
            }

        }

        // release the threads
        if (myUpdate.joinable()) myUpdate.join();
        if (myRecalculateTransforms.joinable()) myRecalculateTransforms.join();
    }

    window.close();

    return 0;
}



