//
// Created by Pablo Weremczuk on 2019-06-23.
//
#pragma once

struct TextContainer : GameObject {
    sf::Text text;

    TextContainer(Context &context, std::string pText, int charSize = 50, sf::Color color = sf::Color::White,
                  bool centered = true) {
        text.setFont(context.fontHolder->get(Fonts::PRESS_START));
        text.setFillColor(color);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(5);
        text.setCharacterSize(charSize);
        text.setString(pText);


        if (centered) {
            text_center_origin(text);
            text_center_on_screen(text, context.screenSize);
        }
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        GameObject::draw(target, states);
        target.draw(text, states);
    }
};

struct TextContainerProgressive : GameObject {
    sf::Sound soundTypeWriter;
    sf::Text text;
    std::string textString;
    float accumulatedElapsedTime = 0;
    int charCounter = 1;

    TextContainerProgressive(Context &context, std::string pText, int charSize = 50, sf::Color color = sf::Color::White,
                             bool centered = true) : textString(pText) {
        text.setFont(context.fontHolder->get(Fonts::PRESS_START));
        text.setFillColor(color);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(5);
        text.setCharacterSize(charSize);
        text.setLineSpacing(1.5);

        soundTypeWriter.setBuffer(context.soundHolder->get(SoundFX::TYPEWRITER));

        if (centered) {
            text_center_origin(text);
            text_center_on_screen(text, context.screenSize);
        }
    }

    void update(float dt) override {
        GameObject::update(dt);

        accumulatedElapsedTime += dt;

        if (accumulatedElapsedTime >= 0.05f) {
            text.setString(textString.substr(0, charCounter));
            text_center_origin(text);
            if (charCounter < textString.size()) {
                charCounter++;
                if(soundTypeWriter.getStatus() == sf::Sound::Status::Stopped){
                    if(textString[charCounter] != ' '){
                        soundTypeWriter.play();
                    }
                }
            }
            accumulatedElapsedTime = 0;
        }

    }

    void reset() {
        charCounter = 0;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        GameObject::draw(target, states);
        target.draw(text, states);
    }
};