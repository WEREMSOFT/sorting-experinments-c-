//
// Created by Pablo Weremczuk on 2019-06-02.
//

#pragma once


namespace cat {

    enum CatStates {
        IDLE,
        WALKING,
        ATTACKING,
        STATE_COUNT
    };

    enum CatAnimations {
        ANIM_IDLE,
        ANIM_WALKING,
        ANIM_COUNT
    };

    typedef std::vector<Animation::Struct> Animations;
    // Cat animations

    void animations_init(Animations &animations, Context &context){
        animations[CatAnimations::ANIM_IDLE].maxFrames = 5;
        animations[CatAnimations::ANIM_IDLE].frameSize =  {0, 26, 135, 154};
        animations[CatAnimations::ANIM_IDLE].framesPerSeccond = 10;
        animations[CatAnimations::ANIM_IDLE].centered = true;
        animations[CatAnimations::ANIM_IDLE].state = Animation::AnimationState::PLAYING;

        animations[CatAnimations::ANIM_WALKING].maxFrames = 8;
        animations[CatAnimations::ANIM_WALKING].frameSize =  {0, 767, 148, 193};
        animations[CatAnimations::ANIM_WALKING].framesPerSeccond = 8;
        animations[CatAnimations::ANIM_WALKING].centered = true;
        animations[CatAnimations::ANIM_WALKING].state = Animation::AnimationState::PLAYING;
    }

    // TODO: Should this functions be here?
    void state_to_idle(Tables &tables, int id, cat::Animations &animations){
        tables[id].state = CatStates::IDLE;
        tables[id].animation = animations[CatAnimations::ANIM_IDLE];
        tables[id].sprite.setOrigin(tables[id].animation.frameSize.width / 2, 0.0);
        flagUtils::setDirty(tables, id);
    }

    void state_to_walking(Tables &tables, int id, Animations &animations){
        tables[id].state = CatStates::WALKING;
        tables[id].animation = animations[CatAnimations::ANIM_WALKING];
        tables[id].sprite.setOrigin(tables[id].animation.frameSize.width / 2, 0.0);
        flagUtils::setDirty(tables, id);
    }

    void state_process_idle(Tables &tables, int id, Animations &animations){
        if(tables[id].lastPosition != tables[id].sprite.getPosition()){
            state_to_walking(tables, id, animations);
        }
    }

    void state_process_walking(Tables &tables, int id, Animations &animations){
        if(tables[id].lastPosition == tables[id].sprite.getPosition()){
            state_to_idle(tables, id, animations);
        }
    }

}


