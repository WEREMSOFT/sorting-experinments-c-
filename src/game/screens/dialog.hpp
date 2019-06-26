//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once

struct Dialog: Screen {
    sf::IntRect textureRect;
    Menu menu;
    GameObject character;

    Dialog(Context& context): Screen(context.textureHolder->get(Textures::BACKGROUND_DIALOG), context), menu(context, *this) {

        menu.offset.y = 250;
        context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE).setRepeated(true);
        textureRect.top = 0;
        textureRect.left = 0;

        textureRect.height = context.window->getSize().y;
        textureRect.width = context.window->getSize().x;

        sprite.setTextureRect(textureRect);

        std::vector<std::string> menuItems = {
                "Go to main menu",
                "Go to town"
        };

        menu.setMenuItems(menuItems);
        menu.callback = onMenuItemSelected;

        layers[LAYER_MIDDLE].addChild(&menu);
        character.sprite.setTexture(context.textureHolder->get(Textures::PANDA));
        character.sprite.setScale(0.45, 0.45);
        layers[LAYER_BACKGROUND].addChild(&character);
    }

    void update(float dt) override {
        Screen::update(dt);
        if(isKeyDown(keys::BackSpace)) {
            passToStateTransitionOut(MAIN_MENU);
        }
    }

    static void onMenuItemSelected(Screen& screen, int itemSelected) {
        screen.passToStateTransitionOut(itemSelected);
    }
};


