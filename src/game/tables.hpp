//
// Created by Pablo Weremczuk on 2019-05-13.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "resource_definitions.hpp"
#define MAX_ENTITIES 100

struct Position{
    float position_x[MAX_ENTITIES] = {0};
    float position_y[MAX_ENTITIES] = {0};
};

struct Transform{
    float scale_x[MAX_ENTITIES] = {0};
    float scale_y[MAX_ENTITIES] = {0};
    float rotation[MAX_ENTITIES] = {0};
};



struct Tables {
    Position position;
    Transform transform;
    Textures::ID textureID[MAX_ENTITIES] = {static_cast<Textures::ID>(0)};
    Fonts::ID fontsID[MAX_ENTITIES] = {static_cast<Fonts::ID>(0)};
};


struct Entity {
    unsigned int entityId = 0;
    Entity(){
        static unsigned int lastId;
        entityId = ++lastId;
    }
};

