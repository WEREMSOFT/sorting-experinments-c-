//
// Created by Pablo Weremczuk on 2019-05-13.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "resource_definitions.hpp"
#include "../core/resources/animation.hpp"

#define MAX_ENTITIES_SOA 1
#define MAX_ENTITIES 100


enum Entities {
    BACKGROUND,
    HOUSE,
    TABLE,
    CAT,
    ENTITIES_COUNT
};

enum Flags{
    DIRTY = 1,
    ANIMATED = 1 << 1,
    FLIPPED = 1 << 2,
    VISIBLE = 1 << 3
};

typedef std::vector<int> IntVect;
typedef std::vector<sf::Transform> SFTransformVect;
typedef std::vector<Textures::ID> TexturesIDVect;
typedef std::vector<Fonts::ID> FontsIDVect;

/*
 DOD rules:
 ==========
 1.a. IF YOU UNDERSTAND THE DATA, YOU UNDERSTAND THE PROBLEM.
 1. Everything is public.
 2. You have ONE type of GameObject.
 3. You have ONE array of objects. Called "tables"
 4. Class methods are FORBIDDEN. Constructors are ok.
 5. Templates are forbidden(std::vector is ok)
 6. The GameObjects in the array are transformed by functions with the signature:
    void functionName(std::vector<Tables>& tables, int begin, int end, ...)
 7. If's inside function myst be avoided, SORT THE ARRAY and iterate the part of it you are interested
    As an example, if you want to draw only the visible objects, don't do

    for(int i = begin; i < end; i++){
        if(tables[i].visible) draw(tables[i]);
    }


    first SORT the tables by visible attribute, and then iterate all the visible gameObjects.

    std::sort(tables, (GameObject* a, GameObject* b)-> int { return a->visible - b->visible; }); // note, you can also sort by z-index

    then, since all the visible objects are at the end, get the first visible object index, and iterate from there

    int firstVisibleIndex = findFirstVisible(tables);

    for(int i = firstVisibleIndex; i < tables.size(); i++){
        draw(tables[i]);
    }

    Sort and iterate, don't "if"


 */


struct GameObject {
    int type = 0;
    uint flags = 0;
    int zIndex = 0;
    int worldZIndex = 0;
    int parent = 0;
    Fonts::ID fontsID;
    std::vector<int> children;
    sf::Transform transform;
    sf::Transform worldTransform;
    Textures::ID textureID;
    sf::FloatRect textureRect;
    Animation::Struct animations;
};

typedef std::vector<GameObject> Tables;
