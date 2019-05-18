//
// Created by Pablo Weremczuk on 2019-05-13.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "resource_definitions.hpp"
#define MAX_ENTITIES 100

enum Entities {
    BACKGROUND,
    HOUSE,
    CAT,
    TILE,
    TILE1,
    TILE2,
    TILE3,
    TILE4,
    TILE5,
    TILE6,
    ENTITIES_COUNT
};

enum Flags{
    NONE = 0,
    DIRTY = 1,
    HAS_CHILDS = 1 << 2,
};


struct Tables {
    unsigned int flags[MAX_ENTITIES] = {0};
    Entities parent[MAX_ENTITIES] = {static_cast<Entities>(0)};
    sf::Transform transform[MAX_ENTITIES];
    sf::Transform worldTransform[MAX_ENTITIES];
    Textures::ID textureID[MAX_ENTITIES] = {static_cast<Textures::ID>(0)};
    Fonts::ID fontsID[MAX_ENTITIES] = {static_cast<Fonts::ID>(0)};
};


