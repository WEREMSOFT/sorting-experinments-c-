//
// Created by Pablo Weremczuk on 2019-05-12.
//

#pragma once


#include "../../core/entities/game_object.hpp"
#include "../../core/resources/animation.hpp"
#include "../../context.hpp"

namespace Cat {

    enum CatAnimations {
        ANIM_IDLE,
        ANIM_RUNNING,
        ANIM_ATTACKING,
        ANIM_AMMOUNT
    };


    struct Struct: public GameObject::Struct {
        Animation::Struct animations[CatAnimations::ANIM_AMMOUNT];
        CatAnimations currentAnimation;

        Struct(){

        }

        Struct(const Cat::Struct& other) = delete;
    };

    namespace utils {
        void initializeAnimations(Struct& cat, Context& context){
            cat.texture = &context.textureHolder->get(Textures::CAT_1_ANIMATION);
//            cat.animations[CatAnimations::ANIM_IDLE].texture = &context.textureHolder->get(Textures::CAT_1_ANIMATION);
            cat.animations[CatAnimations::ANIM_IDLE].maxFrames = 5;
            cat.animations[CatAnimations::ANIM_IDLE].frameSize =  {0, 26, 135, 154};
            cat.animations[CatAnimations::ANIM_IDLE].framesPerSeccond = 10;
            Animation::utils::playAnimation(cat.animations[CatAnimations::ANIM_IDLE]);
        }

        void playAnimation(Cat::Struct& cat, CatAnimations animationId){
            cat.currentAnimation = animationId;
            Animation::utils::playAnimation(cat.animations[animationId]);
        }
    }
}



