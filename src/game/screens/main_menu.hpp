//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once

struct MainMenu: Screen {
    sf::FloatRect textureRect;
    GameObject pandaLeft;
    GameObject pandaRight;
    TextContainer gameName;
    Menu menu;

    MainMenu(Context& context): Screen(context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE), context), gameName(context, "Game Name"), menu(context, *this) {
        menu.screen = this;
        menu.offset.y = 250;
        gameName.text.move({0, -250});

        context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE).setRepeated(true);
        textureRect.top = 0;
        textureRect.left = 0;

        textureRect.height = context.screenSize.y;
        textureRect.width = context.screenSize.x;

        pandaRight.sprite.setTexture(context.textureHolder->get(Textures::PANDA));
        pandaLeft.sprite.setTexture(context.textureHolder->get(Textures::PANDA));

        layers[LAYER_MIDDLE].addChild(&pandaRight);
        layers[LAYER_MIDDLE].addChild(&pandaLeft);

        layers[LAYER_MIDDLE].addChild(&gameName);

        sprite.setTextureRect((sf::IntRect)textureRect);



        pandaRight.sprite.setScale(-.35, .35);
        pandaLeft.sprite.setScale(.35, .35);

        pandaRight.sprite.move(context.screenSize.x, 0);

        std::vector<std::string> menuItems = {
                "Go To Town",
                "Go To Dialog",
                "Do Nothing"
        };

        menu.setMenuItems(menuItems);
        menu.callback = onMenuItemSelected;

        layers[LAYER_MIDDLE].addChild(&menu);
    }

    void update(float dt) override {
        Screen::update(dt);
        textureRect.top = textureRect.top + 100 * dt;
        textureRect.left = textureRect.left + 150 * dt;
        sprite.setTextureRect((sf::IntRect)textureRect);
    }

    static void onMenuItemSelected(Screen& screen, int itemSelected) {
        if(itemSelected + 1 < SCREEN_COUNT) {
            screen.passToStateTransitionOut(itemSelected + 1);
        }

    }
};


