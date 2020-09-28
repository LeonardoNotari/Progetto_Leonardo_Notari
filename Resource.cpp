//
// Created by leonardo on 17/08/20.
//

#include "Resource.h"

Resource* Resource::instance=nullptr;

Resource* Resource::getInstance() {
    if(instance == nullptr){
        instance = new Resource();
    }
    return instance;
}

Resource::Resource() {
    sf::Texture texture;
    texture.loadFromFile("image/Ship00.png");
    textures.push_back(texture);
    texture.loadFromFile("image/gun.png");
    textures.push_back(texture);
    texture.loadFromFile("image/gun1.png");
    textures.push_back(texture);
    texture.loadFromFile("image/gun2.png");
    textures.push_back(texture);
    texture.loadFromFile("image/life1.png");
    textures.push_back(texture);
    texture.loadFromFile("image/statuetta.png");
    textures.push_back(texture);
    texture.loadFromFile("image/alien2.png");
    textures.push_back(texture);
    texture.loadFromFile("image/Ship10.png");
    textures.push_back(texture);
}

sf::Sprite Resource::setSprite(TypeOfSprite spriteType){
    if(spriteType==TypeOfSprite::Player){
        sprite.setTexture(textures.at(0));
    }
    if(spriteType==TypeOfSprite::MGun){
        sprite.setTexture(textures.at(1));
    }
    if(spriteType==TypeOfSprite::LGun){
        sprite.setTexture(textures.at(2));
    }
    if(spriteType==TypeOfSprite::BGun){
        sprite.setTexture(textures.at(3));
    }
    if(spriteType==TypeOfSprite::LifePU){
        sprite.setTexture(textures.at(4));
    }
    if(spriteType==TypeOfSprite::EnergyPU){
        sprite.setTexture(textures.at(5));
    }
    if(spriteType==TypeOfSprite::KEnemy){
        sprite.setTexture(textures.at(6));
    }
    if(spriteType==TypeOfSprite::CEnemy){
        sprite.setTexture(textures.at(7));
    }
    return sprite;
}
