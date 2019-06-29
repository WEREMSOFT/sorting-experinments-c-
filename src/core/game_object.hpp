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

struct AnimatedGameObject : public GameObject {
    std::vector<anim::Struct> animations;
    int currentAnimation = 0;

    AnimatedGameObject(): GameObject() {
    }

    AnimatedGameObject(const sf::Texture &texture) : GameObject(texture) {
        animations.reserve(10);
    }

    void update(float dt) override {
        GameObject::update(dt);
        anim::utils::animation_process_frame(animations[0], dt);
        sprite.setTextureRect(animations[0].textureRect);
        sprite_center_origin(sprite);
    }

    bool isPlaying() {
        return animations[currentAnimation].state == anim::PLAYING;
    }

    void play(int animation){
        currentAnimation = animation;
        anim::utils::animation_play(animations[currentAnimation]);
    }
};

/*
 //
// Created by Pablo Weremczuk on 2019-06-16.
//

#pragma once
#define isKeyDown sf::Keyboard::isKeyPressed
#define keys sf::Keyboard

namespace little_mac {

    enum States {
        IDLE,
        ATTACKING,
        STATE_COUNT,
    };

    enum Animations {
        ANIM_IDLE,
        ANIM_ATTACKING,
        ANIM_COUNT,
    };

    void animations_init(anim::AnimationVector &animations, Context &context) {
        animations[Animations::ANIM_IDLE].maxFrames = 5;
        animations[Animations::ANIM_IDLE].frameSize = {0, 135, 98, 135};
        animations[Animations::ANIM_IDLE].framesPerSeccond = 5;
        animations[Animations::ANIM_IDLE].centered = true;
        animations[Animations::ANIM_IDLE].state = anim::AnimationState::PLAYING;

        animations[Animations::ANIM_ATTACKING].maxFrames = 6;
        animations[Animations::ANIM_ATTACKING].frameSize = {0, 0, 98, 135};
        animations[Animations::ANIM_ATTACKING].framesPerSeccond = 20;
        animations[Animations::ANIM_ATTACKING].centered = true;
        animations[Animations::ANIM_ATTACKING].looped = false;
        animations[Animations::ANIM_ATTACKING].state = anim::AnimationState::PLAYING;
    }

    void keyboard_event_handler(GameObject& entity, float dt) {
        const float thingySpeed = 500;
        entity.lastPosition = entity.sprite.getPosition();
        if (isKeyDown(keys::Left)) {
            entity_move(entity, sf::Vector2f(-thingySpeed * dt, 0));
            entity.flags &= ~Flags::FLIPPED;
        }
        if (isKeyDown(keys::Right)) {
            entity_move(entity, sf::Vector2f(thingySpeed * dt, 0));
            entity.flags |= Flags::FLIPPED;
        }
        if (isKeyDown(keys::Up)) {
            entity_move(entity, sf::Vector2f(0, -thingySpeed * dt));
        }
        if (isKeyDown(keys::Down)) {
            entity_move(entity, sf::Vector2f(0, thingySpeed * dt));
        }
    }

    void state_to_idle(GameObject& littleMac, anim::AnimationVector &animations) {
        littleMac.state = States::IDLE;
        littleMac.animation = animations[Animations::ANIM_IDLE];
        littleMac.sprite.setOrigin(littleMac.animation.frameSize.width / 2, 0.0);
    }

    void state_to_attacking(Tables &tables, int id, anim::AnimationVector &animations) {
        tables[id].state = States::ATTACKING;
        tables[id].animation = animations[Animations::ANIM_ATTACKING];
        tables[id].sprite.setOrigin(tables[id].animation.frameSize.width / 2, 0.0);
    }

    void state_process_idle(Tables &tables, int id, anim::AnimationVector &animations) {
        tables[id].flags &= ~Flags::FLIPPED;

        static int keys_state[255] = {0};

        if(isKeyDown(keys::Left) && !keys_state[keys::Left]){
            keys_state[keys::Left] = true;
            state_to_attacking(tables, id, animations);
        }

        if(isKeyDown(keys::Right) && !keys_state[keys::Right]){
            tables[id].flags |= Flags::FLIPPED;
            state_to_attacking(tables, id, animations);
        }


        keys_state[keys::Left] = isKeyDown(keys::Left);
        keys_state[keys::Right] = isKeyDown(keys::Right);
    }

    void state_process_attacking(Tables &tables, int id, anim::AnimationVector &animations) {
        if(tables[id].animation.state == anim::STOPED){
            state_to_idle(tables[id], animations);
        }
    }

    void handle_states(Tables &tables, int id, anim::AnimationVector &cat_animations){
        switch (tables[id].state) {
            case States::IDLE:
                state_process_idle(tables, id, cat_animations);
                break;
            case States::ATTACKING:
                state_process_attacking(tables, id, cat_animations);
                break;
        }
    }

    void create(GameObject& littleMac, Context& context, anim::AnimationVector& animations) {
        animations.reserve(little_mac::ANIM_COUNT);
        littleMac.sprite.setTexture(context.textureHolder->get(Textures::LITTLE_MAC));
        littleMac.sprite.setOrigin(49, 0);
        entity_center_on_screen(littleMac, *context.window);
        animations_init(animations, context);
        state_to_idle(littleMac, animations);
        littleMac.sprite.setScale(3, 3);
        entity_set_animated(littleMac);
    }
}
 */