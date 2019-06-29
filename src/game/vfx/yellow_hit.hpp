#pragma once


struct YellowHit : public AnimatedGameObject {

    enum AnimationIds{
        BLIN,
        AIMATIONS_COUNT
    };

    YellowHit(): AnimatedGameObject() {
        animations.reserve(1);

        animations.emplace_back();

        // Specific code for test
        animations[BLIN].maxFrames = 16;
        animations[BLIN].frameSize = {0, 0, 1024, 1024};
        animations[BLIN].framesPerSeccond = 30;
        animations[BLIN].centered = true;
        animations[BLIN].looped = false;
        animations[BLIN].state = anim::AnimationState::PLAYING;

        currentAnimation = BLIN;
    }


};