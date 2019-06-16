//
// Created by Pablo Weremczuk on 2019-06-16.
//

#pragma once

namespace cat {

    void animations_init(AnimationVector &animations, Context &context) {
        animations[cat::Animations::ANIM_IDLE].maxFrames = 5;
        animations[cat::Animations::ANIM_IDLE].frameSize = {0, 26, 135, 154};
        animations[cat::Animations::ANIM_IDLE].framesPerSeccond = 10;
        animations[cat::Animations::ANIM_IDLE].centered = true;
        animations[cat::Animations::ANIM_IDLE].state = Animation::AnimationState::PLAYING;

        animations[cat::Animations::ANIM_WALKING].maxFrames = 8;
        animations[cat::Animations::ANIM_WALKING].frameSize = {0, 767, 148, 193};
        animations[cat::Animations::ANIM_WALKING].framesPerSeccond = 8;
        animations[cat::Animations::ANIM_WALKING].centered = true;
        animations[cat::Animations::ANIM_WALKING].state = Animation::AnimationState::PLAYING;
    }

    void keyboard_event_handler(Tables &tables, int id, float dt) {
        const float thingySpeed = 500;
        tables[id].lastPosition = tables[id].sprite.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            entity_move(tables, id, sf::Vector2f(-thingySpeed * dt, 0));
            tables[id].flags &= ~Flags::FLIPPED;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            entity_move(tables, id, sf::Vector2f(thingySpeed * dt, 0));
            tables[id].flags |= Flags::FLIPPED;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            entity_move(tables, id, sf::Vector2f(0, -thingySpeed * dt));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            entity_move(tables, id, sf::Vector2f(0, thingySpeed * dt));
        }
    }

    void state_to_idle(Tables &tables, int id, AnimationVector &animations) {
        tables[id].state = cat::States::IDLE;
        tables[id].animation = animations[cat::Animations::ANIM_IDLE];
        tables[id].sprite.setOrigin(tables[id].animation.frameSize.width / 2, 0.0);
    }

    void state_to_walking(Tables &tables, int id, AnimationVector &animations) {
        tables[id].state = cat::States::WALKING;
        tables[id].animation = animations[cat::Animations::ANIM_WALKING];
        tables[id].sprite.setOrigin(tables[id].animation.frameSize.width / 2, 0.0);
    }

    void state_process_idle(Tables &tables, int id, AnimationVector &animations) {
        if (tables[id].lastPosition != tables[id].sprite.getPosition()) {
            state_to_walking(tables, id, animations);
        }
    }

    void state_process_walking(Tables &tables, int id, AnimationVector &animations) {
        if (tables[id].lastPosition == tables[id].sprite.getPosition()) {
            state_to_idle(tables, id, animations);
        }
    }

    void handle_states(Tables &tables, int id, AnimationVector &cat_animations){
        switch (tables[id].state) {
            case cat::States::IDLE:
                cat::state_process_idle(tables, id, cat_animations);
                break;
            case cat::States::WALKING:
                cat::state_process_walking(tables, id, cat_animations);
                break;
        }
    }
}