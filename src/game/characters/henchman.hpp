//
// Created by Pablo Weremczuk on 2019-06-16.
//

#pragma once
#define isKeyDown sf::Keyboard::isKeyPressed
#define keys sf::Keyboard

namespace henchman {

    enum States {
        IDLE,
        HIT,
        STATE_COUNT,
    };

    enum Animations {
        ANIM_IDLE,
        ANIM_HIT,
        ANIM_COUNT,
    };

    void animations_init(anim::AnimationVector &animations, Context &context) {
        animations[Animations::ANIM_IDLE].maxFrames = 1;
        animations[Animations::ANIM_IDLE].frameSize = {0, 0, 92, 157};
        animations[Animations::ANIM_IDLE].framesPerSeccond = 5;
        animations[Animations::ANIM_IDLE].centered = true;
        animations[Animations::ANIM_IDLE].state = anim::AnimationState::PLAYING;

        animations[Animations::ANIM_HIT].maxFrames = 1;
        animations[Animations::ANIM_HIT].frameSize = {0, 157, 92, 157};;
        animations[Animations::ANIM_HIT].framesPerSeccond = 3;
        animations[Animations::ANIM_HIT].centered = true;
        animations[Animations::ANIM_HIT].looped = false;
        animations[Animations::ANIM_HIT].state = anim::AnimationState::PLAYING;

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

    void state_to_idle(GameObject& henchman, anim::AnimationVector &animations) {
        henchman.state = States::IDLE;
        henchman.animation = animations[Animations::ANIM_IDLE];
        henchman.sprite.setOrigin(henchman.animation.frameSize.width / 2, 0.0);
    }

    void state_to_hit(GameObject& entity, anim::AnimationVector &animations) {
        entity.state = States::HIT;
        entity.animation = animations[Animations::ANIM_HIT];
        entity.sprite.setOrigin(entity.animation.frameSize.width / 2, 0.0);
    }

    void state_process_idle(GameObject& henchman, anim::AnimationVector &animations) {
        henchman.flags &= ~Flags::FLIPPED;

        static int keys_state[255] = {0};

        if(isKeyDown(keys::Left) && !keys_state[keys::Left]){
            keys_state[keys::Left] = true;
            state_to_hit(henchman, animations);
        }

        if(isKeyDown(keys::Right) && !keys_state[keys::Right]){
            henchman.flags |= Flags::FLIPPED;
            state_to_hit(henchman, animations);
        }


        keys_state[keys::Left] = isKeyDown(keys::Left);
        keys_state[keys::Right] = isKeyDown(keys::Right);
    }

    void state_process_hit(GameObject& henchman, anim::AnimationVector &animations) {
        if(henchman.animation.state == anim::STOPED){
            state_to_idle(henchman, animations);
        }
    }

    void handle_states(GameObject& henchman, anim::AnimationVector &cat_animations){
        switch (henchman.state) {
            case States::IDLE:
                state_process_idle(henchman, cat_animations);
                break;
            case States::HIT:
                state_process_hit(henchman, cat_animations);
                break;
        }
    }

    void create(GameObject& henchman, Context& context, anim::AnimationVector& animations){
        animations.reserve(henchman::ANIM_COUNT);
        henchman.sprite.setTexture(context.textureHolder->get(Textures::HENCHMAN));
        entity_center_on_screen(henchman, *context.window);
        entity_move(henchman, sf::Vector2f(0, -70.f));
        henchman::animations_init(animations, context);
        henchman::state_to_idle(henchman, animations);
        henchman.sprite.setScale(3, 3);
        entity_set_animated(henchman);
    }
}