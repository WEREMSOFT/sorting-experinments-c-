//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once

struct MainMenu: Screen {
    sf::IntRect textureRect;
    GameObject pandaLeft;
    GameObject pandaRight;
    TextContainer gameName;
    Menu menu;

    MainMenu(Context& context): Screen(context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE), context), gameName(context, "Game Name"), menu(context) {

        gameName.text.move({0, -150});

        context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE).setRepeated(true);
        textureRect.top = 0;
        textureRect.left = 0;

        textureRect.height = context.window->getSize().y;
        textureRect.width = context.window->getSize().x;

        pandaRight.sprite.setTexture(context.textureHolder->get(Textures::PANDA));
        pandaLeft.sprite.setTexture(context.textureHolder->get(Textures::PANDA));

        addChild(&pandaRight);
        addChild(&pandaLeft);

        addChild(&gameName);

        sprite.setTextureRect(textureRect);
        addChild(&shutters);
        shutters.passToStateClosed();
        shutters.passToStateOpenning();


        pandaRight.sprite.setScale(-.35, .35);
        pandaLeft.sprite.setScale(.35, .35);

        pandaRight.sprite.move(context.window->getSize().x, 0);

        std::vector<std::string> menuItems = {
                "Uno",
                "Dos",
                "Tres"
        };

        menu.setMenuItems(menuItems);
        menu.callback = onMenuItemSelected;

        addChild(&menu);
    }

    void update(float dt) override {
        GameObject::update(dt);
        textureRect.top = textureRect.top + 100 * dt;
        textureRect.left = textureRect.left + 150 * dt;
        sprite.setTextureRect(textureRect);
    }

    static void onMenuItemSelected(Context& context, int itemSelected) {
        printf("Item selected %d\n", itemSelected);
        context.currentGameScreen = itemSelected;

    }
};


