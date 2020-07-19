//
// Created by leono on 18/06/2020.
//

#include "GameCharacter.h"
#include "Weapon.h"


GameCharacter::GameCharacter(int spaceshipEnergy, int spaceshipHP) : posX(0), posY(0), energy(spaceshipEnergy),
                                                                     freeEnergy(spaceshipEnergy), HP(spaceshipHP) {}

bool GameCharacter::isPossibleEquipWeapon(int cost) {
    if (cost <= freeEnergy) {
        freeEnergy -= cost;
        return true;
    } else
        return false;
}

void GameCharacter::equipWeapon(int cost, Weapon *gun) {
    if (this->isPossibleEquipWeapon(cost))
        this->weapon = gun;
}

Weapon *GameCharacter::getWeapon() const {
    return this->weapon;
}

float GameCharacter::getGameCharacterX() const {
    return this->posX;
}

float GameCharacter::getGameCharacterY() const {
    return this->posY;
}

void GameCharacter::move(float x, float y) {
    posX += x;
    posY += y;
}

void GameCharacter::receiveDamage(int damage) {
    this->HP -= damage;
}

int GameCharacter::getGameCharacterHP() const {
    return this->HP;
}