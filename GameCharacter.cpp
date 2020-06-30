//
// Created by leono on 18/06/2020.
//

#include <iostream>
#include "GameCharacter.h"
#include "Weapon.h"

GameCharacter::GameCharacter(int starshipEnergy,int   starshipHP) :  posX(0),  posY(0),  energy(starshipEnergy),  HP(starshipHP)  {}


bool GameCharacter::IsPossibleEquipeWeapon(int cost){
    return cost <= energy;
};