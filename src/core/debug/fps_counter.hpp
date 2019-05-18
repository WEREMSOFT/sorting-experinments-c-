//
// Created by Pablo Weremczuk on 2019-05-11.
//

#pragma once

#include <SFML/Graphics.hpp>

namespace FPSCounter {

    struct Struct {
        sf::Transform transform;
        sf::Font* font;
        sf::Clock clock;
        int characterSize = 24;
        sf::Color color = sf::Color::White;
        float lastTime = 0;
        std::map<int, int> registeredFPS;
        const int MAX_REGISTERED_FPS = 10;
        unsigned int registeredFPSIndex = 0;
        std::string text = "FPS: ";
    };

    namespace utils {
        void initialize(FPSCounter::Struct& fps){
            fps.lastTime = fps.clock.restart().asSeconds();
        }

        void draw(FPSCounter::Struct& fpsCounter, sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default){
            sf::Text text;
            text.setFont(*fpsCounter.font);
            text.setCharacterSize(fpsCounter.characterSize);
            text.setString(fpsCounter.text);
            text.setFillColor(fpsCounter.color);
            target.draw(text, states.transform * fpsCounter.transform);
        }

        int calculateAVGFPS(FPSCounter::Struct& fps){
            int acumulator = 0;
            for(auto i: fps.registeredFPS){
                acumulator += i.second;
            }

            return acumulator / fps.MAX_REGISTERED_FPS;
        }

        void recalculateFPS(FPSCounter::Struct& fps){
            float currentTime = fps.clock.restart().asSeconds();
            fps.text = std::string("FPS: ");

            fps.registeredFPS[fps.registeredFPSIndex % fps.MAX_REGISTERED_FPS] = (int)(1.f / (currentTime - fps.lastTime));
            fps.registeredFPSIndex++;


            fps.text = fps.text + std::to_string((int) FPSCounter::utils::calculateAVGFPS(fps));

            fps.lastTime = fps.clock.restart().asSeconds();
        }


    }


};


