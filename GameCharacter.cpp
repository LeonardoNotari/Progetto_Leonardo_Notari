//
// Created by leono on 18/06/2020.
//

#include "GameCharacter.h"
#include <utility>
#include "Weapon.h"


GameCharacter::GameCharacter(int gameCharacterHP, float gameCharacterX, float gameCharacterY, int spaceshipEnergy,
                             sf::Sprite playerSprite) : Character(gameCharacterHP, gameCharacterX, gameCharacterY,
                                                                  std::move(playerSprite)), energy(spaceshipEnergy), score(0), travel(0), weaponEquipped(0) {}

bool GameCharacter::isPossibleEquipWeapon(int cost) const {
    if (cost <= this->energy) {
        return true;
    } else
        return false;
}

void GameCharacter::equipWeapon(Weapon *gun) {
    if (this->isPossibleEquipWeapon(gun->getWeaponCost())) {
        this->weaponEquipped=this->weaponEquipped+1;
        this->weapon = gun;
        gun->equip = true;
    }
    if(weaponEquipped==5){
        this->notify("EquipGoal1");
    }
    if(weaponEquipped==20){
        this->notify("EquipGoal2");
    }
    if(weaponEquipped==80){
        this->notify("EquipGoal3");
    }
}

Weapon *GameCharacter::getWeapon() const {
    return this->weapon;
}

int GameCharacter::getEnergy() const {
    return this->energy;
}

int GameCharacter::getScore() const {
    return this->score;
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
        this->travel+=1;
    }
    if(travel==100000)
        this->notify("TravelGoal1");
    if(travel==500000)
        this->notify("TravelGoal2");
    if(travel==1000000)
        this->notify("TravelGoal3");
    this->receiveDamage(damage);
}

void GameCharacter::setEnergy(int increment) {
    this->energy += increment;
}

void GameCharacter::setGoal() {
    this->goal=" ";
}

void GameCharacter::setScore(int increment) {
    this->score+=increment;
}

std::string GameCharacter::getGoal() {
    return this->goal;
}

void GameCharacter::reset(int playerEnergy,int hp,float x,float y){
    this->energy=playerEnergy;
    this->observers.clear();
    this->HP=1000;
    this->posX=x;
    this->posY=y;
    this->enemyDefeated=0;
    this->score=0;
    this->travel=0;
    this->weaponEquipped=0;
    this->weapon= nullptr;
}

void GameCharacter::subscribe(Observer* o) {
    observers.push_back(o);
}

void GameCharacter::unsubscribe(Observer* o) {
    observers.remove(o);
}

void GameCharacter::notify(const std::string& goalReach) {
    this->goal=goalReach;
    if(goalReach=="EnemyGoal1" || goalReach=="TravelGoal1" || goalReach=="EquipGoal1"){
        this->score=this->score+500;
    }
    if(goalReach=="EnemyGoal2" || goalReach=="TravelGoal2" || goalReach=="EquipGoal2"){
        this->score=this->score+500;
    }
    if(goalReach=="EnemyGoal3" || goalReach=="TravelGoal3" || goalReach=="EquipGoal3"){
        this->score=this->score+500;
    }
    for(auto & observer : this->observers){
        observer->update(goalReach);
    }
}

void GameCharacter::setEnemyDefeated() {
    this->enemyDefeated+=1;
}

float GameCharacter::getEnemyDefeated() const {
    return this->enemyDefeated;
}
