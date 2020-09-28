//
// Created by leonardo on 17/08/20.
//

#include "Resource.h"

Resource *Resource::instance = nullptr;

Resource *Resource::getInstance() {
    if (instance == nullptr) {
        instance = new Resource();
    }
    return instance;
}

Resource::Resource() {
    sf::Texture texture;
    std::string s;
    texture.loadFromFile("image/Ship00.png");
    textures.insert(std::make_pair(TypeOfSprite::Player, texture));
    texture.loadFromFile("image/gun.png");
    textures.insert(std::make_pair(TypeOfSprite::MGun, texture));
    texture.loadFromFile("image/gun1.png");
    textures.insert(std::make_pair(TypeOfSprite::LGun, texture));
    texture.loadFromFile("image/gun2.png");
    textures.insert(std::make_pair(TypeOfSprite::BGun, texture));
    texture.loadFromFile("image/life1.png");
    textures.insert(std::make_pair(TypeOfSprite::LifePU, texture));
    texture.loadFromFile("image/statuetta.png");
    textures.insert(std::make_pair(TypeOfSprite::EnergyPU, texture));
    texture.loadFromFile("image/alien2.png");
    textures.insert(std::make_pair(TypeOfSprite::KEnemy, texture));
    texture.loadFromFile("image/Ship10.png");
    textures.insert(std::make_pair(TypeOfSprite::CEnemy, texture));
    texture.loadFromFile("image/projectile00.png");
    textures.insert(std::make_pair(TypeOfSprite::CommonBulletSprite, texture));
    texture.loadFromFile("image/shot7.png");
    textures.insert(std::make_pair(TypeOfSprite::BazookaBulletSprite, texture));
    texture.loadFromFile("image/projectile2.png");
    textures.insert(std::make_pair(TypeOfSprite::LaserBulletSprite, texture));
}

sf::Sprite Resource::setSprite(TypeOfSprite spriteType) {
    sf::Sprite sprite;
    auto texture= textures.find(spriteType);
    sprite.setTexture(texture->second);
    return sprite;
}
