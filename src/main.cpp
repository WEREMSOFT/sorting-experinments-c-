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
#define UPDATE_DELAY 0.014 //Milliseconds

bool gameIsRunning = true;

namespace threads {

    void printPosition(Tables& tables, int id) {
        while(gameIsRunning){
            printf("Position %f, %f\n", tables[id].transform.getMatrix()[12], tables[id].transform.getMatrix()[13]);
        }
    }

    #define FRAME_DELAY 0.016 // Millisecconds
    void draw(Tables& tables, Context& context){

            sf::Clock clock;
            sf::RenderWindow& window = *context.window;
            FPSCounter::Struct fpsCounter;
            fpsCounter.font = &context.fontHolder->get(Fonts::PRESS_START);


            sf::Time sleepInterval = sf::seconds(UPDATE_DELAY);

            while(gameIsRunning) {

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

                if(elapsedTime.asSeconds() < FRAME_DELAY) {
                    sf::sleep(sleepInterval - elapsedTime);
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

void handleAnimation(Tables& tables, uint id, float dt){
    Animation::utils::processAnimationFrame(tables[id].animations, dt);
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


        // Cat animations
        tables[Entities::CAT].animations.texture = &context.textureHolder->get(Textures::CAT_1_ANIMATION);
        tables[Entities::CAT].animations.maxFrames = 8;
        tables[Entities::CAT].animations.frameSize = {0, 767, 148, 193};
        tables[Entities::CAT].animations.textureRect = {0, 767, 148, 193};
        tables[Entities::CAT].animations.framesPerSeccond = 8;
        tables[Entities::CAT].animations.centered = true;
        tables[Entities::CAT].flags |= Flags::ANIMATED;


        transformUtils::move(tables, Entities::TABLE, sf::Vector2f(500, 446));


        sf::Clock clock;

        std::thread myDrawThread(threads::draw, std::ref(tables), std::ref(context));
        sf::Time sleepInterval = sf::seconds(.02f);

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

            sortUtils::sortByType(tables);
            handleAnimation(tables, Entities::CAT, dt);

            gameUtils::handleKeyboardEvent(tables, Entities::CAT, dt);
            sortUtils::sortByDirty(tables);
            transformUtils::recalculateWorldTransforms(tables, gameUtils::findFirstDirty(tables));

            sf::Time elapsedTime = clock.getElapsedTime();
            if(elapsedTime.asSeconds() < UPDATE_DELAY){
                sf::sleep(sf::seconds(UPDATE_DELAY));
            }

        }

        if(myDrawThread.joinable()) myDrawThread.join();
    }
    window.close();
    return 0;
}



