//
// Created by leonardo on 17/08/20.
//

#include "Resource.h"

void setTexture(){
    sf::Texture playerTexture;
    playerTexture.loadFromFile("image/Ship00.png");
    sf::Sprite characterSprite;
    characterSprite.setTexture(playerTexture);
    //************* sprite Weapon
    sf::Texture machineGunTexture;
    machineGunTexture.loadFromFile("image/gun.png");
    sf::Texture laserGunTexture;
    laserGunTexture.loadFromFile("image/gun1.png");
    sf::Texture bazookaTexture;
    bazookaTexture.loadFromFile("image/gun2.png");
    //************* sprite item
    sf::Texture lifeTexture;
    lifeTexture.loadFromFile("image/life1.png");
    sf::Texture energyTexture;
    energyTexture.loadFromFile("image/statuetta.png");
    sf::Texture explosionTexture;
    explosionTexture.loadFromFile("image/explosion.png");
    sf::Sprite explosion(explosionTexture);
    //************ sprite enemy
    sf::Texture enemyTexture;
    sf::Texture enemyTexture1;
    enemyTexture.loadFromFile("image/alien2.png");
    enemyTexture1.loadFromFile("image/Ship10.png");
    //************** sprite proiettili
    sf::Texture BulletCommon;
    BulletCommon.loadFromFile("image/projectile00.png");
    sf::Texture BulletBazooka;
    BulletBazooka.loadFromFile("image/shot7.png");
    sf::Texture BulletLaser;
    BulletLaser.loadFromFile("image/projectile00.png");
}