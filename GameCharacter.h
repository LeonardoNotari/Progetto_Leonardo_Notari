//
// Created by leono on 18/06/2020.
//

#ifndef PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
#define PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H

#include <iostream>
#include "Weapon.h"

class GameCharacter{
public:
    Weapon*  weapon   {nullptr};
    GameCharacter(int spaceshipEnergy,int   spaceshipHP);
    bool   IsPossibleEquipWeapon(int   cost);
    void   EquipWeapon(int   cost,Weapon*   weapon);
    int   getGameCharacterX()   const   ;
    int   getGameCharacterY()   const   ;
    void   move(int   x,int   y);
protected:
    int   posX;
    int   posY;
    int   HP;
    int   energy;
    int   freeEnergy;
    std::string   name;
};

#endif //PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
