#pragma once

#include "../core/resources/resource_holder.hpp"
#include <SFML/Audio.hpp>
namespace Textures{
    enum ID {
        TITLE_BACKGROUND_TILE,
        TABLE,
        HOUSE,
        LIGHT_O_TABLE,
        BACKGROUND,
        MOTH,
        TITLE_MAIN_IMAGE,
        MENU_SIDE_IMAGE,
        CAT_1_ANIMATION,
        LITTLE_MAC,
        BACKGROUND_FIGHT,
        BACKGROUND_DIALOG,
        BACKGROUND_MENU,
        HENCHMAN,
        PANDA,
        AGRETSUKO,
        VFX_YELLOW_HIT,
        TEXTURE_COUNT
    };
}

namespace SoundFX {
    enum ID {
        TYPEWRITER,
        SOUND_COUNT
    };
}

namespace Fonts{
    enum ID {
        PRESS_START,
        FONT_COUNT
    };
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer , SoundFX::ID> SoundHolder;
