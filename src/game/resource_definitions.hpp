#pragma once

#include "../core/resources/resource_holder.hpp"

namespace Textures{
    enum ID {
        TITLE_BACKGROUND_TILE,
        TABLE,
        HOUSE,
        LIGHT_O_TABLE,
        BACKGROUND,
        MOTH,
        TITLE_MAIN_IMAGE,
        CAT_1_ANIMATION,
        LITTLE_MAC,
        BACKGROUND_FIGHT,
        HENCHMAN,
        TEXTURE_COUNT
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
