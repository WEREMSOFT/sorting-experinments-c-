//
// Created by Pablo Weremczuk on 2019-06-23.
//
#pragma once

struct TextContainer: GameObject {
    sf::Text text;
    TextContainer(Context& context, std::string pText, int charSize = 50, bool centered = true){
        text.setFont(context.fontHolder->get(Fonts::PRESS_START));
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(3);
        text.setCharacterSize(charSize);
        text.setString(pText);


        if(centered){
            text_center_origin(text);
            text_center_on_screen(text, *context.window);
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        GameObject::draw(target, states);
        target.draw(text, states);
    }
};