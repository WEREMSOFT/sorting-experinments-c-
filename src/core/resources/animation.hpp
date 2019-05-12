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
        AnimationState state = AnimationState::STOPED;
        int maxFrames = 0;
        float frame = 0.f;
        float framesPerSeccond = 30.f;
        sf::Sprite sprite;
        sf::Rect<int> frameSize;
        bool looped = true;
        bool centered = false;

        Struct() {
            std::cout << "building animation " << std::endl;
            if (centered) {
                sprite.setOrigin(frameSize.width / 2, 0.0);
            } else {
                sprite.setOrigin(0.0, 0.0);
            }
        }

        Struct (const Struct &other) = delete;
        Struct(const Struct &&other) = delete;
    };

    namespace utils {

        void playAnimation(Animation::Struct& anim) {
            anim.state = AnimationState::PLAYING;
        }

        void stopAnimation(Animation::Struct& anim) {
            anim.state = AnimationState::STOPED;
        }

        void setTexture(Animation::Struct& anim, sf::Texture &pTexture) {
            anim.sprite.setTexture(pTexture);
        }

        void gotoFrame(Animation::Struct& anim, int frame) {
            anim.sprite.setTextureRect({
                                               anim.frameSize.left + anim.frameSize.width * (int)anim.frame,
                                               anim.frameSize.top,
                                               anim.frameSize.width,
                                               anim.frameSize.height});
        }

        void processAnimationFrame(Animation::Struct& anim, const float delta) {
            // only process animation if the animation is not stoped.
            if (anim.state == AnimationState::PLAYING) {
                anim.frame += anim.framesPerSeccond * delta;

                if (anim.frame > anim.maxFrames) {
                    anim.frame = 0;
                    if (!anim.looped) {
                        stopAnimation(anim);
                    }
                }
            }

            Animation::utils::gotoFrame(anim, int(anim.frame));
        }


        void gotoAndStop(Animation::Struct& anim, int frame) {
            stopAnimation(anim);
            anim.frame = (anim.frame > anim.maxFrames) ? anim.maxFrames : anim.frame;
            anim.frame = frame;
            gotoFrame(anim, frame);
        }

        void setCentered(Animation::Struct& anim, bool pCentered) {
            anim.centered = pCentered;
            if (anim.centered) {
                anim.sprite.setOrigin(anim.frameSize.width / 2, 0.0);
            } else {
                anim.sprite.setOrigin(0.0, 0.0);
            }
        }

    };

}
