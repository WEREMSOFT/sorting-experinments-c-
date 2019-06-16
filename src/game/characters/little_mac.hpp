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

    void keyboard_event_handler(Tables &tables, int id, float dt) {
        const float thingySpeed = 500;
        tables[id].lastPosition = tables[id].sprite.getPosition();
        if (isKeyDown(keys::Left)) {
            entity_move(tables, id, sf::Vector2f(-thingySpeed * dt, 0));
            tables[id].flags &= ~Flags::FLIPPED;
        }
        if (isKeyDown(keys::Right)) {
            entity_move(tables, id, sf::Vector2f(thingySpeed * dt, 0));
            tables[id].flags |= Flags::FLIPPED;
        }
        if (isKeyDown(keys::Up)) {
            entity_move(tables, id, sf::Vector2f(0, -thingySpeed * dt));
        }
        if (isKeyDown(keys::Down)) {
            entity_move(tables, id, sf::Vector2f(0, thingySpeed * dt));
        }
    }

    void state_to_idle(Tables &tables, int id, anim::AnimationVector &animations) {
        tables[id].state = States::IDLE;
        tables[id].animation = animations[Animations::ANIM_IDLE];
        tables[id].sprite.setOrigin(tables[id].animation.frameSize.width / 2, 0.0);
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
            state_to_idle(tables, id, animations);
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
}