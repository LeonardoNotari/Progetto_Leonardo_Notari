#include <iostream>
#include "GameCharacter.h"

Weapon builtWeapon();

enum class GameEvent {
    quit, left, up, down, right, fire, noop
};


GameEvent getEvent() {
    char c;
    while (std::cin.get(c)) {
        std::cin.ignore(100, '\n');
        switch (c) {
            case 'Q':
                return GameEvent::quit;
            case 'w':
                return GameEvent::up;
            case 'a':
                return GameEvent::left;
            case 's':
                return GameEvent::down;
            case 'd':
                return GameEvent::right;
            case 'f':
                return GameEvent::fire;
            default:
                return GameEvent::noop;
        }
    }
}

bool updateGame(const GameEvent &gameEvent, GameCharacter &player,   Weapon &gun) {
    switch (gameEvent) {
        case GameEvent::quit:
            return true;

        case GameEvent::up: {
            player.move(0,1);
            break;
        }
        case GameEvent::left: {
            player.move(-1,0);
            break;
        }
        case GameEvent::down: {
            player.move(0,-1);
            break;
        }
        case GameEvent::right: {
            player.move(1,0);
            break;
        }
        case GameEvent::fire: {
            gun.Use();
            break;
        }
        case GameEvent::noop: {
            break;
        }
    }
    return false;
}


int main() {
    int basicWeaponPower=0,  starshipEnergy=0,   starshipHP=0;
    int gameCharacterX,  gameCharacterY,  weaponX=0,  weaponY=0,   weaponCost=0,   weaponPower=0;
    GameCharacter player(starshipEnergy,   starshipHP);//istanza personaggio
    Weapon baseGun(basicWeaponPower);//istanza arma di base
    player.EquipeWeapon(1,&baseGun);


    Weapon gun(weaponPower,weaponCost,weaponX,weaponY);//istanza di un' arma non base
    weaponY=gun.getWeaponY();
    weaponX=gun.getWeaponX();


    while (true) {
        GameEvent gameEvent = getEvent();
        bool quit = updateGame(  gameEvent,   player,   gun  );
        gameCharacterX=player.getGameCharacterX();
        gameCharacterY=player.getGameCharacterY();
        if(   weaponX == gameCharacterX  &&  weaponY == gameCharacterY   ){
            player.EquipeWeapon(weaponCost,&gun);
        }
        if (quit)
            return 0;
    }
}


Weapon builtWeapon(){
    int weaponX=0,  weaponY=0,   weaponCost=1,   weaponPower=0;
    Weapon gun(weaponPower,weaponCost,weaponX,weaponY);//istanza di un' arma non base
    return gun;
}