//
// Created by Pablo Weremczuk on 2019-05-07.
//

#include "game_object.hpp"

GameObject::GameObject(const sf::Texture &texture) : Sprite(texture) {

}

void GameObject::draw(sf::RenderTarget &target, sf::RenderStates pStates) {

}

void GameObject::addChild(sf::Texture &texture) {

}


//std::vector<GameObject> children;
//sf::RenderStates states;
//explicit GameObject(const sf::Texture& texture);
//
//virtual void draw(sf::RenderTarget& target, sf::RenderStates pStates){
//    states = pStates;
//}
//
//void addChild(sf::Texture& texture){
//    children.emplace_back(texture);
//}