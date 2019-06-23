//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once

struct Shutters: GameObject{
    enum States {
        SHUTTERS_OPEN,
        SHUTTERS_CLOSED,
        SHUTTERS_STATE_COUNT
    };

    sf::RectangleShape shade_up;
    sf::RectangleShape shade_down;
    bool isOpen = false;

    Shutters(Context& context){

        sf::RenderWindow& window = *context.window;

        sf::Vector2f size_screen = sf::Vector2f(window.getDefaultView().getSize());
        size_screen.y /= 2;

        shade_up.setSize(size_screen);
        shade_down.setSize(size_screen);

        shade_up.setFillColor(sf::Color::Black);
        shade_down.setFillColor(sf::Color::Black);

        shade_down.setPosition({0, size_screen.y});
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        GameObject::draw(target, states);
        target.draw(shade_up, states);
        target.draw(shade_down, states);
    }


    void update(float dt) override {
        GameObject::update(dt);

        switch ()
    }
};


struct Screen: GameObject {

    Screen(){
        bool shade_is_closed = true;

    }
};

struct MainMenu: GameObject {
    Shutters shutters;
    sf::IntRect textureRect;
    MainMenu(Context& context): GameObject(context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE)), shutters(context) {
        context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE).setRepeated(true);
        textureRect.top = 0;
        textureRect.left = 0;

        textureRect.height = context.window->getSize().y;
        textureRect.width = context.window->getSize().x;

        sprite.setTextureRect(textureRect);
        addChild(&shutters);
    }

    void update(float dt){
        GameObject::update(dt);
        textureRect.top = textureRect.top + 100 * dt;
        textureRect.left = textureRect.left + 150 * dt;
        sprite.setTextureRect(textureRect);
    }
};


