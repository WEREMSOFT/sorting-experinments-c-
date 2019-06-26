//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once
#include <math.h>

#define keys sf::Keyboard
#define isKeyDown sf::Keyboard::isKeyPressed

struct Menu: GameObject{
    std::vector<sf::Text> items;
    Context* context;
    int characterSize;
    sf::Vector2f offset;
    int selectedIndex = 0;
    void (* callback)(Screen&, int);
    Screen* screen;
    sf::RectangleShape background;

    Menu(Context& context, Screen& containerScreen, int characterSize = 32, sf::Vector2f offset = {0, 0}): GameObject(), offset(offset), characterSize(characterSize), context(&context), screen(&containerScreen) {
        background.setSize((sf::Vector2f)context.window->getSize());
        background.setFillColor(sf::Color(0, 0, 0, 200));
    }

    void setMenuItems(std::vector<std::string>& menuItems) {
        float backgroundHeight = 0;
        for(int i = 0; i < menuItems.size(); i++){
            items.emplace_back();
            items[i].setFont(context->fontHolder->get(Fonts::PRESS_START));
            items[i].setString(menuItems[i]);
            items[i].setCharacterSize(characterSize);
            text_center_on_screen(items[i], *context->window);
            text_center_origin(items[i]);
            items[i].move(offset.x, items[0].getLocalBounds().height * i * 1.2 + offset.y);
            backgroundHeight += items[i].getLocalBounds().height + offset.y;
        }
        background.setPosition(0, items[0].getPosition().y - items[0].getLocalBounds().height);
        background.setSize({background.getSize().x, backgroundHeight * 1.5f});
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        GameObject::draw(target, states);
        target.draw(background);
        for(int i = 0; i < items.size(); i++){
            target.draw(items[i], states);
        }
    }

    void update(float dt) override {
        GameObject::update(dt);

        static int keys_state[255] = {0};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !keys_state[sf::Keyboard::Up]) {
            selectedIndex--;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !keys_state[sf::Keyboard::Down]) {
            selectedIndex++;
        }

        selectedIndex = std::min(std::max(selectedIndex, 0), (int)items.size() - 1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !keys_state[sf::Keyboard::Enter]) {
            callback(*screen, selectedIndex);
        }

        keys_state[keys::Up] = isKeyDown(keys::Up);
        keys_state[keys::Down] = isKeyDown(keys::Down);
        keys_state[keys::Enter] = isKeyDown(keys::Enter);

        // Clear outlines on menu
        for (int i = 0; i < items.size(); i++) {
            items[i].setOutlineThickness(0);
            items[i].setFillColor(sf::Color::White);
        }

        items[selectedIndex].setOutlineColor(sf::Color::Black);
        items[selectedIndex].setOutlineThickness(5);
        items[selectedIndex].setFillColor(sf::Color::Yellow);
    }
};
