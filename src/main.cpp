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
//
//namespace threads {
//    void printPosition(Tables& tables, int id) {
//        while(gameIsRunning){
//            printf("Position %f, %f\n", tables.transform[id].getMatrix()[12], tables.transform[id].getMatrix()[13]);
//        }
//    }
//
//    void handleAnimation(Tables& tables, uint id){
//        sf::Clock clock;
//        float dt = clock.restart().asSeconds();
//        while(gameIsRunning) {
//            dt = clock.restart().asSeconds();
//            Animation::utils::processAnimationFrame(tables.animations[id], dt);
//        }
//    }
//



Context &loadScreen(Context &context) {
    {
        LoadScreen::Struct loadScreen(context);
        LoadScreen::utils::loadResources(loadScreen);
        LoadScreen::utils::run(loadScreen);
    }
    return context;
}

void recalculateWorldTransfrorms() {

}

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WITH, SCREEN_HEIGHT), "Purfectly Safe", sf::Style::Default);
    sf::View view;
    sf::Clock clock;
    TextureHolder textureHolder;
    FontHolder fontHolder;
    Tables tables(MAX_ENTITIES);
    int entityIDs[MAX_ENTITIES] = {0};

    printf("Space in memory %lu\n", sizeof(tables));

    Context context(window, textureHolder, fontHolder);
    // At the end of this scope, the loading screen will be removed from the stack.
    context = loadScreen(context);

    // This is a scope, All objects created inside will be destroyed on the closing bracket.
    {
        // Build game objects;
        tables[Entities::BACKGROUND].textureID = Textures::BACKGROUND;
        tables[Entities::HOUSE].textureID = Textures::HOUSE;
        tables[Entities::TABLE].textureID = Textures::TABLE;
        tables[Entities::CAT].textureID = Textures::CAT_1_ANIMATION;

        // Set type = index for further reference
        gameUtils::setTypeEqualsIndex(tables);

        // Set some parent-child relationship
        utilsFunctions::move(tables, Entities::TABLE, sf::Vector2f(500, 446));
        utilsFunctions::setChild(tables, Entities::CAT, Entities::TABLE);
        utilsFunctions::setChild(tables, Entities::HOUSE, Entities::TABLE);


        sf::Clock clock;
        FPSCounter::Struct fpsCounter;
        fpsCounter.font = &fontHolder.get(Fonts::PRESS_START);
        float acumulatedDelta = 0;

        FPSCounter::utils::initialize(fpsCounter);

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

            sortUtils::sortByType(tables);

            gameUtils::handleKeyboardEvent(tables, Entities::TABLE, dt);
            utilsFunctions::recalculateWorldTransforms(tables, gameUtils::findFirstDirty(tables));



            if (acumulatedDelta >= FRAME_DELAY) {
                acumulatedDelta = 0;

                // recalculate transforms
                sortUtils::sortByDirty(tables);
                gameUtils::findFirstDirty(tables);

                sortUtils::sortByZIndex(tables);
                utilsFunctions::draw(tables, context, 0, Entities::ENTITIES_COUNT);

                FPSCounter::utils::recalculateFPS(fpsCounter);
                FPSCounter::utils::draw(fpsCounter, window);

                window.display();
            }

        }
    }
    window.close();
    return 0;
}



