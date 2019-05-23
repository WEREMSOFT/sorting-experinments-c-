//
// Created by Pablo Weremczuk on 2019-05-11.
//

#pragma once

#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "resource_definitions.hpp"
#include "../core/utils.hpp"

namespace LoadScreen {
    struct Struct {
        Context &context;
        int finshed = false;
        int resourceConunter = 0;
        std::mutex lockScopeHandler;
        std::vector<std::thread> threads;
        sf::Text loadingText;
        sf::Text pressSpaceText;
        sf::RectangleShape progressBarBackgroud;
        sf::RectangleShape progressBar;
        float percentajeLoaded = 0.f;
        std::function<void(Textures::ID id, const std::string &filename)> loadTexture = [&](Textures::ID id,
                                                                                            const std::string &filename) -> void {
            lockScopeHandler.lock();
            resourceConunter++;
            lockScopeHandler.unlock();


            context.textureHolder->load(id, filename);
            printf("%s loaded\n", filename.c_str());
            lockScopeHandler.lock();
            resourceConunter--;
            lockScopeHandler.unlock();
        };

        Struct(Context &context) : context(context) {

        }

        ~Struct(){
            printf("Destroying loading screen\n");
        }

        Struct(const Struct& other) = delete;
        Struct(const Struct&& other) = delete;
    };

    namespace utils {

        void showIndicators(LoadScreen::Struct &loadScreen) {
            std::cout << "Loading assets..." << std::endl;
            loadScreen.context.fontHolder->load(Fonts::PRESS_START, "../assets/fonts/PressStart2P-Regular.ttf");

            loadScreen.loadingText.setFont(loadScreen.context.fontHolder->get(Fonts::PRESS_START));
            loadScreen.loadingText.setString("Loading Resources");
            utilsFunctions::centerOrigin(loadScreen.loadingText);
            utilsFunctions::centerTextOnScreen(loadScreen.loadingText, *loadScreen.context.window);

            loadScreen.pressSpaceText.setFont(loadScreen.context.fontHolder->get(Fonts::PRESS_START));
            loadScreen.pressSpaceText.setString("Press Space to continue");
            utilsFunctions::centerOrigin(loadScreen.pressSpaceText);
            utilsFunctions::centerTextOnScreen(loadScreen.pressSpaceText, *loadScreen.context.window);
            loadScreen.pressSpaceText.move(0.f, 150.f);

            loadScreen.progressBarBackgroud.setFillColor(sf::Color::White);
            loadScreen.progressBarBackgroud.setSize(sf::Vector2f(loadScreen.context.window->getView().getSize().x - 20, 40.f));
            loadScreen.progressBarBackgroud.setPosition(15, loadScreen.loadingText.getPosition().y + 40);

            loadScreen.progressBar.setFillColor(sf::Color::Red);
            loadScreen.progressBar.setSize(sf::Vector2f(200, 30));
            loadScreen.progressBar.setPosition(20, loadScreen.loadingText.getPosition().y + 45);
        }

        void loadResources(LoadScreen::Struct &loadScreen) {
            loadScreen.threads.reserve(Textures::TEXTURE_COUNT);

            LoadScreen::utils::showIndicators(loadScreen);

            loadScreen.threads.emplace_back(loadScreen.loadTexture, Textures::BACKGROUND,
                                            "./assets/images/background.jpg");
            loadScreen.threads.emplace_back(loadScreen.loadTexture, Textures::LIGHT_O_TABLE,
                                            "./assets/images/light-o-table.png");
            loadScreen.threads.emplace_back(loadScreen.loadTexture, Textures::TABLE, "./assets/images/table.png");
            loadScreen.threads.emplace_back(loadScreen.loadTexture, Textures::HOUSE, "./assets/images/house.png");
            loadScreen.threads.emplace_back(loadScreen.loadTexture, Textures::TITLE_BACKGROUND_TILE,
                                            "../assets/images/pattern_background.png");
            loadScreen.threads.emplace_back(loadScreen.loadTexture, Textures::TITLE_MAIN_IMAGE,
                                            "../assets/images/title.png");
            loadScreen.threads.emplace_back(loadScreen.loadTexture, Textures::CAT_1_ANIMATION,
                                            "../assets/images/characters/cat1.png");


            std::cout << "...assets loaded" << std::endl;
        }

        void draw(sf::RenderWindow &window, LoadScreen::Struct &loadScreen) {
            window.clear(sf::Color::Black);
            window.draw(loadScreen.loadingText);
            window.draw(loadScreen.progressBarBackgroud);
            window.draw(loadScreen.progressBar);

            if(loadScreen.finshed){
                window.draw(loadScreen.pressSpaceText);
            }

            window.display();
        }

        void update(LoadScreen::Struct &loadScreen) {
            loadScreen.percentajeLoaded = (float) loadScreen.resourceConunter / (float) Textures::TEXTURE_COUNT;
            auto substraction = loadScreen.context.window->getView().getSize().x * loadScreen.percentajeLoaded + 30;
            loadScreen.progressBar.setSize(sf::Vector2f(loadScreen.context.window->getView().getSize().x - substraction, 30));

            if (loadScreen.resourceConunter != 0) {
                loadScreen.percentajeLoaded =
                        (float) loadScreen.resourceConunter / (float) Textures::TEXTURE_COUNT * 100.0f;
            } else {
                for (int i = 0; i < Textures::TEXTURE_COUNT; i++) {
                    if (loadScreen.threads[i].joinable())
                        loadScreen.threads[i].join();
                }
                loadScreen.finshed = true;
                printf("All loading threads joined\n");
            }
        }

        void run(LoadScreen::Struct& loadScreen){
            sf::RenderWindow& window = *loadScreen.context.window;
            unsigned int loadFinishedAndSpasePressed = false;
            while (window.isOpen() && !loadFinishedAndSpasePressed)
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                if(!loadScreen.finshed){
                    LoadScreen::utils::update(loadScreen);
                } else {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                        loadFinishedAndSpasePressed = true;
                    }
                }
                LoadScreen::utils::draw(window, loadScreen);
            }
        }

    }
};


