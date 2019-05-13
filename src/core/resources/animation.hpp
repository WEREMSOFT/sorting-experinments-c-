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
        sf::Texture* texture;
        int maxFrames = 0;
        float frame = 0.f;
        float framesPerSeccond = 30.f;
        sf::Rect<int> frameSize;
        bool looped = true;
        bool centered = false;

        Struct() {
//            std::cout << "building animation " << std::endl;
//            if (centered) {
//                sprite.setOrigin(frameSize.width / 2, 0.0);
//            } else {
//                sprite.setOrigin(0.0, 0.0);
//            }
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

        void gotoFrame(Animation::Struct& anim, int frame, GameObject::Struct& go) {
            go.textureRect.left = anim.frameSize.left + anim.frameSize.width * (int)anim.frame;
            go.textureRect.top = anim.frameSize.top;
            go.textureRect.width = anim.frameSize.width;
            go.textureRect.height = anim.frameSize.height;
        }

        void processAnimationFrame(Animation::Struct& anim, const float delta, GameObject::Struct& go) {
            if (anim.state == AnimationState::PLAYING) {
                anim.frame += anim.framesPerSeccond * delta;

                if (anim.frame > anim.maxFrames) {
                    anim.frame = 0;
                    if (!anim.looped) {
                        stopAnimation(anim);
                    }
                }
            }

            Animation::utils::gotoFrame(anim, int(anim.frame), go);
        }


        void gotoAndStop(Animation::Struct& anim, int frame, GameObject::Struct& go) {
            stopAnimation(anim);
            anim.frame = (anim.frame > anim.maxFrames) ? anim.maxFrames : anim.frame;
            anim.frame = frame;
            gotoFrame(anim, frame, go);
        }

        void setCentered(Animation::Struct& anim, bool pCentered, sf::Sprite& sprite) {
            anim.centered = pCentered;
            if (anim.centered) {
                sprite.setOrigin(anim.frameSize.width / 2, 0.0);
            } else {
                sprite.setOrigin(0.0, 0.0);
            }
        }

    };

}
