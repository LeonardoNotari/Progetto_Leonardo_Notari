#include <iostream>
#include "GameCharacter.h"

int main() {
    int basicWeaponPower=0,  starshipEnergy=0,   starshipHP=0;
    int gameCharacterX,  gameCharacterY,  weaponX,  weaponY,   weaponCost;
    GameCharacter player(starshipEnergy,   starshipHP);
    Weapon gun(basicWeaponPower);
    weaponX=gun.getWeaponX();
    weaponY=gun.getWeaponY();
    weaponCost=gun.getWeaponCost();
    gameCharacterX=player.getGameCharacterX();
    gameCharacterY=player.getGameCharacterY();
    if(   weaponX == gameCharacterX  &&  weaponY == gameCharacterY   ){
        player.EquipeWeapon(weaponCost);
    }
    return 0;
}