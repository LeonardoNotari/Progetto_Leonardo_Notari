#include <iostream>
#include <vector>
#include <cstdlib>
#include "GameCharacter.h"
#include "Weapon.h"
#include "KamikazeEnemy.h"
#include "CommonEnemy.h"
#include <ctime>


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

int generateCasualNumber() {
    srand(time(nullptr));
    return rand() % 2;
}

std::vector<Enemy *> createEnemy() {//genera nemici
    int numEnemy = 5;
    std::vector<Enemy *> result;
    result.reserve(numEnemy);
    for (int i = 0; i < numEnemy; i++) {
        Enemy *enemy;
        // if (generateCasualNumber() == 1)
        enemy = new KamikazeEnemy(0, 0, 0);
        /* else
             enemy = new CommonEnemy(0, 0, 0);
             */
        result.push_back(enemy);
    }
    return result;
}

std::vector<Weapon *> createWeapon() {//genera armi
    int numWeapon = 5;
    std::vector<Weapon *> result;
    result.reserve(numWeapon);
    for (int i = 0; i < numWeapon; i++) {
        Weapon *weapon;
        weapon = new Weapon(0, 0, 0, 0);
        result.push_back(weapon);
    }
    return result;
}

bool updateGame(const GameEvent &gameEvent, GameCharacter &player, Weapon *gun) {
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
            gun->Use();
            break;
        }
        case GameEvent::noop: {
            break;
        }
    }
    return false;
}

void gameControl(GameCharacter &player, std::vector<Weapon *> &weapons,
                 std::vector<Enemy *> &enemies) {//controllo delle posizioni
    int gameCharacterX, gameCharacterY;
    int weaponX, weaponY, weaponCost;
    gameCharacterX = player.getGameCharacterX();
    gameCharacterY = player.getGameCharacterY();
    for (auto enemy:enemies) {
        enemy->move(gameCharacterX, gameCharacterY);//movimento del nemico
        player.receiveDamage(enemy->attack(gameCharacterX, gameCharacterY));//attacco nemico
    }
    for (auto weapon:weapons) {
        weaponY = weapon->getWeaponY();
        weaponX = weapon->getWeaponX();
        weaponCost = weapon->getWeaponCost();
        if (weaponX == gameCharacterX &&
            weaponY == gameCharacterY) {//equipaggiamento arma se nella stessa posizione del GameCharacter
            player.equipWeapon(weaponCost, weapon);
        }
    }
}


int main() {

    int spaceshipEnergy = 0, spaceshipHP = 0;
    int basicWeaponPower = 0;
    GameCharacter player(spaceshipEnergy, spaceshipHP);//istanza personaggio
    Weapon baseGun(basicWeaponPower);//istanza arma di base
    player.equipWeapon(1, &baseGun);
    std::vector<Weapon *> weapons = createWeapon();
    std::vector<Enemy *> enemies = createEnemy();
    while (true) {
        GameEvent gameEvent = getEvent();
        bool quit = updateGame(gameEvent, player, player.getWeapon());//mossa giocatore
        gameControl(player, weapons, enemies);
        if (quit)
            return 0;
    }
}
