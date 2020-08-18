//
// Created by leono on 18/06/2020.
//

#include "GameCharacter.h"
#include <utility>
#include "Weapon.h"


GameCharacter::GameCharacter(int gameCharacterHP,float gameCharacterX,float gameCharacterY, int spaceshipEnergy, sf::Sprite playerSprite) : Character(gameCharacterHP,gameCharacterX,gameCharacterY,std::move(playerSprite)),energy(spaceshipEnergy) {}

bool GameCharacter::isPossibleEquipWeapon(int cost) const {
    if (cost <= this->energy) {
        return true;
    } else
        return false;
}

void GameCharacter::equipWeapon(Weapon *gun) {
    if (this->isPossibleEquipWeapon(gun->getWeaponCost())) {
        this->weapon = gun;
        gun->equip=true;
    }
}

Weapon *GameCharacter::getWeapon() const {
    return this->weapon;
}

int GameCharacter::getEnergy() const {
    return this->energy;
}

float GameCharacter::getXMax() const {
    return this->xMax;
}

float GameCharacter::getXMin() const {
    return this->xMin;
}

void GameCharacter::move(float x, float y) {
    posX += x;
    posY += y;
}

void GameCharacter::setEnergy(int increment){
    this->energy+=increment;
}

void GameCharacter::setHP(int increment){
    this->HP+=increment;
}