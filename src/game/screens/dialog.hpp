//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once
#include <spine/spine-sfml.h>

struct Dialog: Screen {
    sf::IntRect textureRect;
    Menu menu;
    GameObject character;
    std::shared_ptr<spine::SkeletonDrawable> raptor;
    std::shared_ptr<spine::SkeletonData> raptorSkeletonData;
    std::shared_ptr<spine::Atlas> raptorAtlas;
    std::shared_ptr<spine::SFMLTextureLoader> spineTextureLoader;
    spine::SkeletonJson *raptorSkeleton;

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


        // SPINE
//        "data/raptor-pro.json", "data/raptor-pro.skel", "data/raptor-pma.atlas", 0.5f);
        spineTextureLoader = std::make_shared<spine::SFMLTextureLoader>();


        raptorAtlas = std::make_shared<spine::Atlas>("assets/spine/raptor/raptor-pma.atlas", spineTextureLoader.get());

        auto test = raptorAtlas.get();

//        raptorSkeleton = std::make_shared<spine::Skeleton>(test);

//        spine::SkeletonJson json(raptorAtlas.get());
        raptorSkeleton = new spine::SkeletonJson(raptorAtlas.get());
        raptorSkeleton->setScale(1);
        auto skeletonData = raptorSkeleton->readSkeletonDataFile("assets/spine/raptor/raptor-pro.json");
        if (!skeletonData) {
            printf("%s\n", raptorSkeleton->getError().buffer());
            exit(0);
        }

        raptorSkeletonData = std::shared_ptr<spine::SkeletonData>(skeletonData);


        raptor = std::shared_ptr<spine::SkeletonDrawable>(new spine::SkeletonDrawable(raptorSkeletonData.get()));
        raptor.get()->timeScale = 1;
        raptor.get()->setUsePremultipliedAlpha(true);
//
        spine::Skeleton* skeleton = raptor.get()->skeleton;
        skeleton->setPosition(320, 1000);
        skeleton->updateWorldTransform();

        raptor.get()->state->setAnimation(0, "walk", true);
//        raptor.get()->state->addAnimation(1, "gun-grab", false, 2);


    }

    void update(float dt) override {
        Screen::update(dt);
        if(isKeyDown(keys::BackSpace)) {
            passToStateTransitionOut(MAIN_MENU);
        }
        raptor.get()->update(dt);
    }

    static void onMenuItemSelected(Screen& screen, int itemSelected) {
        screen.passToStateTransitionOut(itemSelected);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        Screen::draw(target, states);
        target.draw(*raptor.get());
    }
};


