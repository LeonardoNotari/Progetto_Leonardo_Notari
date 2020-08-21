//
// Created by leono on 18/06/2020.
//

#include "GameCharacter.h"
#include <utility>
#include "Weapon.h"


GameCharacter::GameCharacter(int gameCharacterHP, float gameCharacterX, float gameCharacterY, int spaceshipEnergy,
                             sf::Sprite playerSprite) : Character(gameCharacterHP, gameCharacterX, gameCharacterY,
                                                                  std::move(playerSprite)), energy(spaceshipEnergy) {}

GameCharacter::~GameCharacter() {//FIXME
    delete this->weapon;
}

bool GameCharacter::isPossibleEquipWeapon(int cost) const {
    if (cost <= this->energy) {
        return true;
    } else
        return false;
}

void GameCharacter::equipWeapon(Weapon *gun) {
    if (this->isPossibleEquipWeapon(gun->getWeaponCost())) {
        this->weapon = gun;
        gun->equip = true;
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
    if (this->posX + x > xMin && this->posX + x < xMax - 60)
        posX += x;
    if (this->posY + y > xMin - 15 && this->posY + y < yMax - 45)
        posY += y;
}

void GameCharacter::setEnergy(int increment) {
    this->energy += increment;
}

bool GameCharacter::isLegalMove(std::vector<Tile *> tiles, float x, float y) {
    auto it = tiles.begin();
    Tile *tile;
    tile = *it;
    while (this->posX + x < tile->xVertexTopSx || this->posX + x > tile->xVertexTopSx + 64 ||
           this->posY + y < tile->yVertexTopSx || this->posY + y > tile->yVertexTopSx + 64) {
        it++;
        tile = *it;
    }
    receiveDamage(tile->getDamage());
    return tile->getIsCrossable();
}
