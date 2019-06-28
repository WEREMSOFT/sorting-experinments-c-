//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once

struct Dialog: Screen {
    sf::IntRect textureRect;
    Menu menu;
    std::unique_ptr<SpineGameObject> dragon;
    std::shared_ptr<TextContainerProgressive> dialogText;

    Dialog(Context& context): Screen(context.textureHolder->get(Textures::BACKGROUND_DIALOG), context), menu(context, *this) {
        dragon = std::make_unique<SpineGameObject>("assets/spine/dragon/NewDragon.atlas", "assets/spine/dragon/NewDragon.json");

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

        layers[LAYER_BACKGROUND].addChild(dragon.get());

        dialogText = std::make_shared<TextContainerProgressive>(context, "Look at me, I'm a DRAGON!!!\n          ARRRH!", 32, sf::Color::Red);
        dialogText.get()->text.move(150, -200);
        layers[LAYER_MIDDLE].addChild(dialogText.get());

    }

    void update(float dt) override {
        Screen::update(dt);
        if(isKeyDown(keys::BackSpace)) {
            passToStateTransitionOut(MAIN_MENU);
        }

    }

    virtual void passToStateTransitionIn() override {
        Screen::passToStateTransitionIn();
        dialogText.get()->reset();
    }

    static void onMenuItemSelected(Screen& screen, int itemSelected) {
        screen.passToStateTransitionOut(itemSelected);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        Screen::draw(target, states);
    }
};


