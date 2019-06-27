//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once
#include <spine/spine-sfml.h>

struct SpineGameObject: GameObject {
    uint state = 0;
    std::shared_ptr<spine::SkeletonDrawable> drawable;
    std::shared_ptr<spine::SkeletonData> raptorSkeletonData;
    std::shared_ptr<spine::Atlas> raptorAtlas;
    spine::SFMLTextureLoader spineTextureLoader;
    spine::SkeletonJson *raptorSkeleton;

    SpineGameObject(const char* atlasFileName, const char* jsonFileName){
        raptorAtlas = std::make_shared<spine::Atlas>(atlasFileName, &spineTextureLoader);

        raptorSkeleton = new spine::SkeletonJson(raptorAtlas.get());
        raptorSkeleton->setScale(1);
        auto skeletonData = raptorSkeleton->readSkeletonDataFile(jsonFileName);
        if (!skeletonData) {
            printf("%s\n", raptorSkeleton->getError().buffer());
            exit(0);
        }

        raptorSkeletonData = std::shared_ptr<spine::SkeletonData>(skeletonData);


        drawable = std::shared_ptr<spine::SkeletonDrawable>(new spine::SkeletonDrawable(raptorSkeletonData.get()));
        drawable.get()->timeScale = 1;
        drawable.get()->setUsePremultipliedAlpha(true);
        spine::Skeleton* skeleton = drawable.get()->skeleton;
        skeleton->setPosition(500, 700);
        skeleton->updateWorldTransform();

        drawable.get()->state->setAnimation(0, "stand", true);

    }

    void setPosition(float x, float y){
        drawable.get()->skeleton->setPosition(x, y);
    }

    virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
        renderTarget.draw(*drawable.get(), renderStates);
    }

    virtual void update(float dt) {
        drawable.get()->update(dt);
    }

    void setposition(sf::Vector2f position) { drawable.get()->skeleton->setPosition(position.x, position.y); };
};


struct Dialog: Screen {
    sf::IntRect textureRect;
    Menu menu;
    GameObject character;
    std::unique_ptr<SpineGameObject> dragon;


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
        character.sprite.setTexture(context.textureHolder->get(Textures::PANDA));
        character.sprite.setScale(0.45, 0.45);

        layers[LAYER_BACKGROUND].addChild(dragon.get());
//        layers[LAYER_BACKGROUND].addChild(&character);

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

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        Screen::draw(target, states);
    }
};


