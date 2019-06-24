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
    void (* callback)(Context& context, int);

    Menu(Context& context ,int characterSize = 32, sf::Vector2f offset = {0, 0}): GameObject(), offset(offset), characterSize(characterSize), context(&context) {
    }

    void setMenuItems(std::vector<std::string>& menuItems) {
        for(int i = 0; i < menuItems.size(); i++){
            items.emplace_back();
            items[i].setFont(context->fontHolder->get(Fonts::PRESS_START));
            items[i].setString(menuItems[i]);
            items[i].setCharacterSize(characterSize);
            text_center_origin(items[i]);
            text_center_on_screen(items[i], *context->window);
            items[i].move(offset.x, items[0].getLocalBounds().height * i * 1.2 + offset.y);
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        GameObject::draw(target, states);
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
            callback(*context, selectedIndex);
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

/*
 namespace menu {
    struct Struct {
        std::vector<sf::Text> items;
        int selectedIndex = 0;
        void (* callback)(int, Context&) ;
    };

    void create(menu::Struct& menu, std::vector<std::string>& menuItems, Context& context, sf::Vector2f offset = {0, 0}, int characterSize = 50) {
        menu.items.reserve(menuItems.size());

        for(int i = 0; i < menuItems.size(); i++){
            menu.items.emplace_back();
            menu.items[i].setFont(context.fontHolder->get(Fonts::PRESS_START));
            menu.items[i].setString(menuItems[i]);
            menu.items[i].setCharacterSize(characterSize);
            text_center_origin(menu.items[i]);
            text_center_on_screen(menu.items[i], *context.window);
            menu.items[i].move(offset.x, menu.items[0].getLocalBounds().height * i * 1.2 + offset.y);
        }

    }

    void handle_menu_control(menu::Struct &menu, Context &context, const int& max_menu_items) {
        static int keys_state[255] = {0};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !keys_state[sf::Keyboard::Up]) {
            menu.selectedIndex--;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !keys_state[sf::Keyboard::Down]) {
            menu.selectedIndex++;
        }

        menu.selectedIndex = std::min(std::max(menu.selectedIndex, 0), max_menu_items - 1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !keys_state[sf::Keyboard::Enter]) {
            menu.callback(menu.selectedIndex, context);
        }

        keys_state[keys::Up] = isKeyDown(keys::Up);
        keys_state[keys::Down] = isKeyDown(keys::Down);
        keys_state[keys::Enter] = isKeyDown(keys::Enter);

        // Clear outlines on menu
        for (int i = 0; i < max_menu_items; i++) {
            menu.items[i].setOutlineThickness(0);
            menu.items[i].setFillColor(sf::Color::White);
        }

        menu.items[menu.selectedIndex].setOutlineColor(sf::Color::Black);
        menu.items[menu.selectedIndex].setOutlineThickness(5);
        menu.items[menu.selectedIndex].setFillColor(sf::Color::Yellow);
    }
};

 */