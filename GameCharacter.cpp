//
// Created by leono on 18/06/2020.
//

#include "GameCharacter.h"
#include <utility>
#include "Weapon.h"


GameCharacter::GameCharacter(int gameCharacterHP, float gameCharacterX, float gameCharacterY, int spaceshipEnergy,
                             sf::Sprite playerSprite) : Character(gameCharacterHP, gameCharacterX, gameCharacterY,
                                                                  std::move(playerSprite)), energy(spaceshipEnergy),
                                                        score(0), travel(0), weaponEquipped(0), enemyDefeated(0) {}

bool GameCharacter::isPossibleEquipWeapon(int cost) const {
    if (cost <= energy) {
        return true;
    } else
        return false;
}

bool GameCharacter::equipWeapon(Weapon *gun) {
    if (isPossibleEquipWeapon(gun->getWeaponCost())) {
        weaponEquipped += 1;
        if (weaponEquipped == 5)
            notify("EquipGoal1");
        if (weaponEquipped == 20)
            notify("EquipGoal2");
        if (weaponEquipped == 80)
            notify("EquipGoal3");
        weapon = gun;
        gun->equip = true;
        return true;
    }
    else return false;
}

Weapon *GameCharacter::getWeapon() const {
    return weapon;
}

int GameCharacter::getEnergy() const {
    return energy;
}

int GameCharacter::getScore() const {
    return score;
}

float GameCharacter::getXMax() const {
    return xMax;
}

float GameCharacter::getXMin() const {
    return xMin;
}

void GameCharacter::move(float x, float y, const TileMap &map) {
    int damage = 0;
    if (map.isLegalMove(posX, posY, x, y, damage)) {
        if (posX + x > xMin && posX + x < xMax - 60)
            posX += x;
        if (posY + y > xMin - 15 && posY + y < yMax - 45)
            posY += y;
        travel += 1;
    }
    if (travel == 100000)
        notify("TravelGoal1");
    if (travel == 500000)
        notify("TravelGoal2");
    if (travel == 1000000)
        notify("TravelGoal3");
    receiveDamage(damage);
}

void GameCharacter::setEnergy(int increment) {
    energy += increment;
}

void GameCharacter::setGoal() {
    goal = " ";
}

void GameCharacter::setScore(int increment) {
    score += increment;
}

std::string GameCharacter::getGoal() {
    return goal;
}

void GameCharacter::reset(int playerEnergy,int hp, float x, float y) {
    energy = playerEnergy;
    observers.clear();
    HP = hp;
    posX = x;
    posY = y;
    enemyDefeated = 0;
    score = 0;
    travel = 0;
    weaponEquipped = 0;
    weapon = nullptr;
}

void GameCharacter::subscribe(Observer *o) {
    observers.push_back(o);
}

void GameCharacter::unsubscribe(Observer *o) {
    observers.remove(o);
}

void GameCharacter::notify(const std::string &goalReach) {
    goal = goalReach;
    if (goalReach == "EnemyGoal1" || goalReach == "TravelGoal1" || goalReach == "EquipGoal1")
        score += 50;
    if (goalReach == "EnemyGoal2" || goalReach == "TravelGoal2" || goalReach == "EquipGoal2")
        score += 500;
    if (goalReach == "EnemyGoal3" || goalReach == "TravelGoal3" || goalReach == "EquipGoal3")
        score += 1000;
    for (auto &observer : observers)
        observer->update(goalReach);
}

void GameCharacter::setEnemyDefeated() {
    enemyDefeated += 1;
}

float GameCharacter::getEnemyDefeated() const {
    return enemyDefeated;
}
