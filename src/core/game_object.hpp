//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once

#include <spine/spine-sfml.h>
#include "resources/animation.hpp"

struct GameObject : sf::Drawable, sf::NonCopyable {
    uint state = 0;
    sf::Sprite sprite;
    uint childCounter = 0;
    GameObject *children[10] = {0};

    GameObject(const sf::Texture &texture) {
        sprite.setTexture(texture);
    }

    GameObject() {
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
        renderTarget.draw(sprite, renderStates);
        for (int i = 0; i < childCounter; i++) {
            renderTarget.draw(*children[i], renderStates.transform * sprite.getTransform());
        }
    }

    void addChild(GameObject *gameObject) {
        children[childCounter++] = gameObject;
    }

    virtual void update(float dt) {
        for (int i = 0; i < childCounter; i++) {
            children[i]->update(dt);
        }
    }

    const sf::Vector2f &getposition() { return sprite.getPosition(); };

    const void setposition(sf::Vector2f position) { sprite.setPosition(position); };


};

struct AnimatedGameObject : public GameObject {

    AnimatedGameObject(const sf::Texture &texture) : GameObject(texture) {

    }
};

struct SpineGameObject : GameObject {
    uint state = 0;
    std::shared_ptr<spine::SkeletonDrawable> drawable;
    std::shared_ptr<spine::SkeletonData> raptorSkeletonData;
    std::shared_ptr<spine::Atlas> raptorAtlas;
    spine::SFMLTextureLoader spineTextureLoader;
    spine::SkeletonJson *raptorSkeleton;

    SpineGameObject(const char *atlasFileName, const char *jsonFileName) {
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
        spine::Skeleton *skeleton = drawable.get()->skeleton;
        skeleton->setPosition(500, 700);
        skeleton->updateWorldTransform();

        drawable.get()->state->setAnimation(0, "stand", true);

    }

    void setPosition(float x, float y) {
        drawable.get()->skeleton->setPosition(x, y);
    }

    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
        renderTarget.draw(*drawable.get(), renderStates);
    }

    virtual void update(float dt) {
        drawable.get()->update(dt);
    }

    void setposition(sf::Vector2f position) { drawable.get()->skeleton->setPosition(position.x, position.y); };
};
