//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once

struct MainMenu: Screen {
    sf::FloatRect textureRect;
    GameObject pandaLeft;
    GameObject pandaRight;
    TextContainer gameName;
    YellowHit hit;
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

        hit.sprite.setTexture(context.textureHolder->get(Textures::VFX_YELLOW_HIT));
        hit.sprite.setScale(.75, .75);
        hit.sprite.move(100, 100);

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
        layers[LAYER_MIDDLE].addChild(&hit);
    }

    void update(float dt) override {
        Screen::update(dt);
        textureRect.top = textureRect.top + 100 * dt;
        textureRect.left = textureRect.left + 150 * dt;
        sprite.setTextureRect((sf::IntRect)textureRect);

//        if(!hit.isPlaying()) {
//            printf("is not playing\n");
//            hit.play(0);
//        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(*context->window);
            float scaleX = (float)SCREEN_WITH / (float)context->window->getSize().x;
            float scaleY = (float)SCREEN_HEIGHT / (float)context->window->getSize().y;
            hit.sprite.setPosition(scaleX * mousePosition.x, scaleY * mousePosition.y);
            hit.play(YellowHit::BLIN);
        }

    }

    static void onMenuItemSelected(Screen& screen, int itemSelected) {
        if(itemSelected + 1 < SCREEN_COUNT) {
            screen.passToStateTransitionOut(itemSelected + 1);
        }

    }
};


