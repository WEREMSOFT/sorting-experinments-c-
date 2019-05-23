//
// Created by Pablo Weremczuk on 2019-05-13.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "resource_definitions.hpp"
#define MAX_ENTITIES 50000
#define HALF_MAX 500

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
    DIRTY = 1,
};


struct Tables {
    int flags[MAX_ENTITIES] = {0};
    int childCount[MAX_ENTITIES] = {0};
    int childs[MAX_ENTITIES][4] = {0};
    int parent[MAX_ENTITIES] = {0};
    sf::Transform transform[MAX_ENTITIES];
    sf::Transform worldTransform[MAX_ENTITIES];
    Textures::ID textureID[MAX_ENTITIES] = {static_cast<Textures::ID>(0)};
    Fonts::ID fontsID[MAX_ENTITIES] = {static_cast<Fonts::ID>(0)};
};


