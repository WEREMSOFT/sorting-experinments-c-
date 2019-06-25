//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once

struct Town: Screen {
    sf::IntRect textureRect;
    Menu menu;

    Town(Context& context): Screen(context.textureHolder->get(Textures::BACKGROUND_FIGHT), context), menu(context, *this, 50) {

        context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE).setRepeated(true);
        textureRect.top = 0;
        textureRect.left = 0;

        textureRect.height = context.window->getSize().y;
        textureRect.width = context.window->getSize().x;

        sprite.setTextureRect(textureRect);

        std::vector<std::string> menuItems = {
                "OPTION 1",
                "OPTION 2",
                "OPTION 3"
        };

        menu.setMenuItems(menuItems);
        menu.callback = onMenuItemSelected;

        layers[LAYER_MIDDLE].addChild(&menu);
    }

    void update(float dt) override {
        Screen::update(dt);
        if(isKeyDown(keys::BackSpace)) {
            passToStateTransitionOut(MAIN_MENU);
        }
    }

    static void onMenuItemSelected(Context& context, Screen& screen, int itemSelected) {
        printf("Item selected %d\n", itemSelected);
    }
};


