#include <iostream>
#include "GameCharacter.h"
#include "Weapon.h"
#include "KamikazeEnemy.h"



enum class GameEvent {
    quit, left, up, down, right, fire, noop
};


GameEvent getEvent() {
    char c;
    while (std::cin.get(c)) {
        std::cin.ignore(0, '\n');
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
    return GameEvent::noop;
}

bool updateGame(const GameEvent &gameEvent, GameCharacter &player, Weapon &gun) {
    switch (gameEvent) {
        case GameEvent::quit:
            return true;

        case GameEvent::up: {
            player.move(0, 1);
            break;
        }
        case GameEvent::left: {
            player.move(-1, 0);
            break;
        }
        case GameEvent::down: {
            player.move(0, -1);
            break;
        }
        case GameEvent::right: {
            player.move(1, 0);
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

void GameControl(GameCharacter& player,Weapon& gun,Enemy& alien){//controllo delle posizioni
    int gameCharacterX,gameCharacterY;
    int weaponX,weaponY,weaponCost;
    gameCharacterX = player.getGameCharacterX();
    gameCharacterY = player.getGameCharacterY();
    weaponY = gun.getWeaponY();
    weaponX = gun.getWeaponX();
    weaponCost=gun.getWeaponCost();
    alien.Move(gameCharacterX, gameCharacterY);//movimento del nemico
    player.ReceiveDamage(alien.Attack(gameCharacterX, gameCharacterY));//attacco nemico
    if (weaponX == gameCharacterX && weaponY == gameCharacterY) {//equipaggiamento arma se nella stessa posizione del GameCharacter
        player.EquipWeapon(weaponCost, &gun);
    }
}


int main() {

    int spaceshipEnergy = 0, spaceshipHP = 0;//variabili gamecharacter

    int weaponY = 0,weaponX=0, weaponCost = 0, weaponPower = 0, basicWeaponPower = 0;//variabili weapon

    int enemyX = 0, enemyY = 0, enemyPower=4;//variabili enemy

    GameCharacter player(spaceshipEnergy, spaceshipHP);//istanza personaggio
    Weapon baseGun(basicWeaponPower);//istanza arma di base
    player.EquipWeapon(1, &baseGun);

    Weapon gun(weaponPower, weaponCost, weaponX, weaponY);//istanza di un' arma non base

    KamikazeEnemy alien(enemyX, enemyY, enemyPower);//istanza enemy di tipo kamikaze

    while (true) {
        GameEvent gameEvent = getEvent();
        bool quit = updateGame(gameEvent, player, gun);//mossa giocatore
        GameControl(player,gun,alien);
        if (quit)
            return 0;
    }
}
