#include <iostream>
#include <SFML/Graphics.hpp>
#include "game/context.hpp"
#include "game/load_screen.hpp"
#include "game/tables.hpp"
#include "core/debug/fps_counter.hpp"
#include <functional>
#include <mutex>

#define SCREEN_WITH 1230
#define SCREEN_HEIGHT 768
#define FRAME_DELAY 0.016 // Millisecconds

bool gameIsRunning = true;

namespace threads {
    void printPosition(Tables& tables, int id) {
        while(gameIsRunning){
            printf("Position %f, %f\n", tables.transform[id].getMatrix()[12], tables.transform[id].getMatrix()[13]);
        }
    }

    void handleAnimation(Tables& tables, uint id){
        sf::Clock clock;
        float dt = clock.restart().asSeconds();
        while(gameIsRunning) {
            dt = clock.restart().asSeconds();
            Animation::utils::processAnimationFrame(tables.animations[id], dt);
        }
    }

    void handleKeyboardEvent(Tables& tables, std::vector<int> ids){
        const float thingySpeed = 1000;
        sf::Clock clock;
        float dt;
        while(gameIsRunning){
            for(int id: ids){
                dt = clock.restart().asSeconds();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    utilsFunctions::move(tables, id, sf::Vector2f(-thingySpeed * dt, 0));
                    tables.flags[id] &= ~Flags::FLIPPED;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    utilsFunctions::move(tables, id, sf::Vector2f(thingySpeed * dt, 0));
                    tables.flags[id] |= Flags::FLIPPED;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    utilsFunctions::move(tables, id, sf::Vector2f(0, -thingySpeed * dt));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    utilsFunctions::move(tables, id, sf::Vector2f(0, thingySpeed * dt));
                }
            }

        }
    }

    void recalculateTransforms(Tables& tables, sf::RenderWindow &window){
        sf::Clock clock;
        while (gameIsRunning) {
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
    sf::RenderWindow window(sf::VideoMode(SCREEN_WITH, SCREEN_HEIGHT), "Purfectly Safe", sf::Style::Default);
    sf::View view;
    sf::Clock clock;
    TextureHolder textureHolder;
    FontHolder fontHolder;
    Tables tables;

    printf("Space in memory %lu\n", sizeof(tables));

    Context context(window, textureHolder, fontHolder);
    // At the end of this scope, the loading screen will be removed from the stack.
    context = loadScreen(context);

    // This is a scope, All objects created inside will be destroyed on the closing bracket.
    {
        // Build game objects;
        tables.textureID[Entities::BACKGROUND] = Textures::BACKGROUND;
        tables.textureID[Entities::HOUSE] = Textures::HOUSE;
        tables.textureID[Entities::CAT] = Textures::CAT_1_ANIMATION;
        tables.textureID[Entities::TABLE] = Textures::TABLE;
        tables.textureID[Entities::TILE] = Textures::TITLE_BACKGROUND_TILE;


        // Cat animations
        tables.animations[Entities::CAT].texture = &context.textureHolder->get(Textures::CAT_1_ANIMATION);
        tables.animations[Entities::CAT].maxFrames = 8;
        tables.animations[Entities::CAT].frameSize = {0, 767, 148, 193};
        tables.animations[Entities::CAT].textureRect = {0, 767, 148, 193};
        tables.animations[Entities::CAT].framesPerSeccond = 8;
        tables.animations[Entities::CAT].centered = true;
        tables.flags[Entities::CAT] |= Flags::ANIMATED;

        utilsFunctions::move(tables, Entities::TABLE, sf::Vector2f(596, 446));


        //Add table as a child of the guy
        utilsFunctions::setChild(tables, Entities::TILE, Entities::CAT);

        sf::Clock clock;
        FPSCounter::Struct fpsCounter;
        fpsCounter.font = &fontHolder.get(Fonts::PRESS_START);
        float acumulatedDelta = 0;

        FPSCounter::utils::initialize(fpsCounter);

        std::thread myRecalculateTransforms(threads::recalculateTransforms, std::ref(tables), std::ref(window));
        std::thread myThingyUpdate(threads::handleKeyboardEvent, std::ref(tables), std::vector<int> {Entities::CAT});
        std::thread myCatAnimationHAndler(threads::handleAnimation, std::ref(tables), Entities::CAT);

        sf::Event event;
        while (gameIsRunning) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed){
                    window.close();
                    gameIsRunning = false;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                gameIsRunning = false;
            }

            float dt = clock.restart().asSeconds();
            acumulatedDelta += dt;

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
        if (myRecalculateTransforms.joinable()) myRecalculateTransforms.join();
        if (myThingyUpdate.joinable()) myThingyUpdate.join();
        if (myCatAnimationHAndler.joinable()) myCatAnimationHAndler.join();
    }
    window.close();
    return 0;
}



