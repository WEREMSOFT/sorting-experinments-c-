//
// Created by Pablo Weremczuk on 2019-06-23.
//

#pragma once

struct GameObject: sf::Drawable, sf::NonCopyable {
    uint state = 0;
    sf::Sprite sprite;
    uint childCounter = 0;
    GameObject* children[10] = {0};

    GameObject(const sf::Texture& texture){
        sprite.setTexture(texture);
    }

    GameObject(){
    }

    void setPosition(float x, float y){
        sprite.setPosition(x, y);
    }

    virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
        renderTarget.draw(sprite, renderStates);
        for(int i = 0; i < childCounter; i++){
            renderTarget.draw(*children[i], renderStates.transform * sprite.getTransform());
        }
    }

    void addChild(GameObject* gameObject){
        children[childCounter++] = gameObject;
    }

    virtual void update(float dt) {
        for(int i = 0; i < childCounter; i++){
            children[i]->update(dt);
        }
    }

    const sf::Vector2f& getposition() { return sprite.getPosition(); };
    const void setposition(sf::Vector2f position) { sprite.setPosition(position); };


};
