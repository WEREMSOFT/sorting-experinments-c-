#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

namespace Animation {

    enum AnimationState {
        PLAYING,
        STOPED
    };

    struct Struct {
        AnimationState state = AnimationState::PLAYING;
        int maxFrames = 0;
        float frame = 0.f;
        float framesPerSeccond = 30.f;
        sf::Rect<int> frameSize;
        sf::Rect<int> textureRect;
        bool looped = true;
        bool centered = false;

        Struct() {
        }
    };

    namespace utils {

        typedef std::vector<Animation::Struct> Animations;
        typedef std::vector<sf::Texture> Textures;
        typedef std::vector<sf::FloatRect> TextureRects;

        void animation_play(Animation::Struct &anim) {
            anim.state = AnimationState::PLAYING;
        }

        void stopAnimation(Animation::Struct& anim) {
            anim.state = AnimationState::STOPED;
        }

        void animation_goto_frame(Animation::Struct &anim, int frame) {
            anim.textureRect.left = anim.frameSize.left + anim.frameSize.width * (int)anim.frame;
            anim.textureRect.top = anim.frameSize.top;
            anim.textureRect.width = anim.frameSize.width;
            anim.textureRect.height = anim.frameSize.height;
        }

        void animation_process_frame(Animation::Struct &anim, const float delta) {
            if (anim.state == AnimationState::PLAYING) {
                anim.frame += anim.framesPerSeccond * delta;

                if (anim.frame > anim.maxFrames) {
                    anim.frame = 0;
                    if (!anim.looped) {
                        stopAnimation(anim);
                    }
                }
            }

            Animation::utils::animation_goto_frame(anim, int(anim.frame));
        }


        void animation_goto_and_stop(Animation::Struct &anim, int frame) {
            stopAnimation(anim);
            anim.frame = (anim.frame > anim.maxFrames) ? anim.maxFrames : anim.frame;
            anim.frame = frame;
            animation_goto_frame(anim, frame);
        }


    };

}
