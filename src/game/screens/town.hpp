//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once

struct Town: Screen {
    sf::IntRect textureRect;
    Menu menu;
    GameObject agretsuko;
    std::shared_ptr<TextContainerProgressive> dialogText;


    Town(Context& context): Screen(context.textureHolder->get(Textures::BACKGROUND_FIGHT), context), menu(context, *this), agretsuko(context.textureHolder->get(Textures::AGRETSUKO)) {
        menu.offset.y = 250;
        context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE).setRepeated(true);
        textureRect.top = 0;
        textureRect.left = 0;

        textureRect.height = context.window->getSize().y;
        textureRect.width = context.window->getSize().x;

        sprite.setTextureRect(textureRect);

        std::vector<std::string> menuItems = {
                "Go to main menu",
                "Go to Dialog"
        };

        menu.setMenuItems(menuItems);
        menu.callback = onMenuItemSelected;

        agretsuko.sprite.setScale(0.9f, 0.9f);

        layers[LAYER_MIDDLE].addChild(&agretsuko);
        layers[LAYER_MIDDLE].addChild(&menu);


        dialogText = std::make_shared<TextContainerProgressive>(context, "What do you want?\n LEAVE ME ALONE!!", 32, sf::Color::Green);
        dialogText.get()->text.move(300, -200);


        layers[LAYER_MIDDLE].addChild(dialogText.get());

    }

    void update(float dt) override {
        Screen::update(dt);
        if(isKeyDown(keys::BackSpace)) {
            passToStateTransitionOut(MAIN_MENU);
        }
    }

    static void onMenuItemSelected(Screen& screen, int itemSelected) {
        switch (itemSelected){
            case 0:
                screen.passToStateTransitionOut(MAIN_MENU);
                break;
            case 1:
                screen.passToStateTransitionOut(DIALOG);
                break;
        }
    }

    virtual void passToStateTransitionIn() override {
        Screen::passToStateTransitionIn();
        dialogText.get()->reset();
    }
};


