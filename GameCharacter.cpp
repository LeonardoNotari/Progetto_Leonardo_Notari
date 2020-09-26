//
// Created by leono on 18/06/2020.
//

#include "GameCharacter.h"
#include <utility>
#include "Weapon.h"


GameCharacter::GameCharacter(int gameCharacterHP, float gameCharacterX, float gameCharacterY, int spaceshipEnergy,
                             sf::Sprite playerSprite) : Character(gameCharacterHP, gameCharacterX, gameCharacterY,
                                                                  std::move(playerSprite)), energy(spaceshipEnergy) {}

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

void GameCharacter::move(float x, float y,const TileMap& map) {
    int damage=0;
    if(map.isLegalMove(this->posX,this->posY,x,y,damage)) {
        if (this->posX + x > xMin && this->posX + x < xMax - 60)
            posX += x;
        if (this->posY + y > xMin - 15 && this->posY + y < yMax - 45)
            posY += y;
    }
    this->receiveDamage(damage);
}

void GameCharacter::setEnergy(int increment) {
    this->energy += increment;
}

void GameCharacter::reset(int playerEnergy,int hp,float x,float y){
    this->energy=playerEnergy;
    this->HP=1000;
    this->posX=x;
    this->posY=y;
    this->enemyDefeated=0;
    this->weapon= nullptr;
}

void GameCharacter::subscribe(Observer* o) {
    observers.push_back(o);
}

void GameCharacter::unsubscribe(Observer* o) {
    observers.remove(o);
}

void GameCharacter::notify() {
    for(auto & observer : this->observers){
        observer->update();
    }
}

void GameCharacter::setEnemyDefeated() {
    this->enemyDefeated++;
}

float GameCharacter::getEnemyDefeated() const {
    return this->enemyDefeated;
}
