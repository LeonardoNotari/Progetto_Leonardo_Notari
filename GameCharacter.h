//
// Created by leono on 18/06/2020.
//

#ifndef PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
#define PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H

#include <iostream>
#include "Weapon.h"

class GameCharacter {
public:

    GameCharacter(int spaceshipEnergy, int spaceshipHP);

    bool isPossibleEquipWeapon(int cost);

    void equipWeapon(int cost, Weapon *weapon);

    Weapon *getWeapon() const;

    int getGameCharacterX() const;

    int getGameCharacterY() const;

    void move(int x, int y);

    void receiveDamage(int damage);

    int getGameCharacterHP() const;

protected:
    Weapon *weapon{nullptr};
    int posX;
    int posY;
    int HP;
    int energy;
    int freeEnergy;
    std::string name;
};

#endif //PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
