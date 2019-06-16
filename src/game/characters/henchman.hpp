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
        animations[Animations::ANIM_HIT].framesPerSeccond = 1;
        animations[Animations::ANIM_HIT].centered = true;
        animations[Animations::ANIM_HIT].looped = false;
        animations[Animations::ANIM_HIT].state = anim::AnimationState::PLAYING;

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

    void state_to_hit(Tables &tables, int id, anim::AnimationVector &animations) {
        tables[id].state = States::HIT;
        tables[id].animation = animations[Animations::ANIM_HIT];
        tables[id].sprite.setOrigin(tables[id].animation.frameSize.width / 2, 0.0);
    }

    void state_process_idle(Tables &tables, int id, anim::AnimationVector &animations) {
        tables[id].flags &= ~Flags::FLIPPED;

        static int keys_state[255] = {0};

        if(isKeyDown(keys::Left) && !keys_state[keys::Left]){
            keys_state[keys::Left] = true;
            state_to_hit(tables, id, animations);
        }

        if(isKeyDown(keys::Right) && !keys_state[keys::Right]){
            tables[id].flags |= Flags::FLIPPED;
            state_to_hit(tables, id, animations);
        }


        keys_state[keys::Left] = isKeyDown(keys::Left);
        keys_state[keys::Right] = isKeyDown(keys::Right);
    }

    void state_process_hit(Tables &tables, int id, anim::AnimationVector &animations) {
        if(tables[id].animation.state == anim::STOPED){
            state_to_idle(tables, id, animations);
        }
    }

    void handle_states(Tables &tables, int id, anim::AnimationVector &cat_animations){
        switch (tables[id].state) {
            case States::IDLE:
                state_process_idle(tables, id, cat_animations);
                break;
            case States::HIT:
                state_process_hit(tables, id, cat_animations);
                break;
        }
    }
}