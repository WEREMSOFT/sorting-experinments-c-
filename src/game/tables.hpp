//
// Created by Pablo Weremczuk on 2019-05-13.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "resource_definitions.hpp"
#include "../core/resources/animation.hpp"

#define MAX_ENTITIES 50

enum Screens {
    MAIN_MENU,
    TOWN,
    DIALOG,
    SCREEN_COUNT,
};

enum Flags{
    DIRTY = 1,
    ANIMATED = 1 << 1,
    FLIPPED = 1 << 2,
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
 2. You have ONE entity_type of GameObject.
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


