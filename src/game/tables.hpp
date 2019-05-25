//
// Created by Pablo Weremczuk on 2019-05-13.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "resource_definitions.hpp"
#define MAX_ENTITIES 100000
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

typedef std::vector<int> IntVect;
typedef std::vector<sf::Transform> SFTransformVect;
typedef std::vector<Textures::ID> TexturesIDVect;
typedef std::vector<Fonts::ID> FontsIDVect;

struct Tables {
    IntVect flags;
    std::vector<std::vector<int>> childs;
    IntVect parent;
    SFTransformVect transform;
    SFTransformVect worldTransform;
    TexturesIDVect textureID;
    FontsIDVect fontsID;

    Tables():
    flags(MAX_ENTITIES),
    childs(MAX_ENTITIES),
    parent(MAX_ENTITIES),
    transform(MAX_ENTITIES),
    worldTransform(MAX_ENTITIES),
    textureID(MAX_ENTITIES),
    fontsID(MAX_ENTITIES){}
};


