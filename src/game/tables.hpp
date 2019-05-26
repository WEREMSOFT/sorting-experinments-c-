//
// Created by Pablo Weremczuk on 2019-05-13.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "resource_definitions.hpp"
#include "../core/resources/animation.hpp"

#define MAX_ENTITIES 100

enum Entities {
    BACKGROUND,
    HOUSE,
    CAT,
    TABLE,
    TILE,
    ENTITIES_COUNT
};

enum Flags{
    DIRTY = 1,
    ANIMATED = 1 << 1,
    FLIPPED = 1 << 2
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
    std::vector<sf::FloatRect> textureRect;
    std::vector<Animation::Struct> animations;

    Tables():
    flags(MAX_ENTITIES),
    childs(MAX_ENTITIES),
    parent(MAX_ENTITIES),
    transform(MAX_ENTITIES),
    worldTransform(MAX_ENTITIES),
    textureID(MAX_ENTITIES),
    fontsID(MAX_ENTITIES),
    textureRect(MAX_ENTITIES),
    animations(MAX_ENTITIES)
    {}
};


