//
// Created by leono on 18/06/2020.
//

#ifndef PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H
#define PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H

#include <iostream>
#include "Weapon.h"

class GameCharacter{
public:
    GameCharacter(int starshipEnergy,int   starshipHP);
    bool   IsPossibleEquipeWeapon(int cost);
    void   EquipeWeapon(int cost);
    int   getGameCharacterX()   const   ;
    int   getGameCharacterY()   const   ;
private:
    int   posX;
    int   posY;
    int   HP;
    int   energy;
    int   freeEnergy;
    std::string   name;
    Weapon*  weapon   {nullptr};
};

#endif //PROGETTO_LEONARDO_NOTARI_GAMECHARACTER_H