//
// Created by leono on 18/06/2020.
//

#include "GameCharacter.h"
#include "Weapon.h"

GameCharacter::GameCharacter(int starshipEnergy,int   starshipHP) :  posX(0),  posY(0),  energy(starshipEnergy),   freeEnergy(starshipEnergy),  HP(starshipHP)  {}


bool   GameCharacter::IsPossibleEquipWeapon(int cost){
    if(   cost   <=   freeEnergy  ){
        freeEnergy -=cost;
        return true;
    } else
        return false;
}

void   GameCharacter::EquipWeapon(int cost,Weapon* gun){
    if(   this->IsPossibleEquipWeapon( cost ) )
        this->weapon = gun;
}

int   GameCharacter::getGameCharacterX()   const   {
    return   this->posX;
}

int   GameCharacter::getGameCharacterY()   const   {
    return   this->posY;
}

void   GameCharacter::move(int   x,int   y){
    posX += x;
    posY += y;
}


