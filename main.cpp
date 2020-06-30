#include <iostream>
#include "GameCharacter.h"

int main() {
    int basicWeaponPower=0,  starshipEnergy=0,   starshipHP=0;
    GameCharacter player(starshipEnergy,   starshipHP);
    Weapon gun(basicWeaponPower);
    player.IsPossibleEquipeWeapon(gun.cost);
    return 0;
}