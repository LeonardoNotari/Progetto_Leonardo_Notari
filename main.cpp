
#include <list>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <utility>
#include "PowerUp.h"
#include "GameCharacter.h"
#include "Weapon.h"
#include "bullet.h"
#include "TileMap.h"
#include "Tile.h"
#include "EnemyFactory.h"
#include "TileFactory.h"
#include "BulletFactory.h"
#include "WeaponFactory.h"

enum class GameEvent {
    left, up, down, right, fire, noop
};


GameEvent getEvent(int &cycles, int cadence) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        return GameEvent::right;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        return GameEvent::left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        return GameEvent::down;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        return GameEvent::up;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        if (cycles >= cadence) {
            cycles = 0;
            return GameEvent::fire;
        } else {
            cycles++;
            return GameEvent::noop;
        }
    }
    return GameEvent::noop;
}

float generateCasualX() {
    srand(time(nullptr));
    return rand() % 8096;
}

float generateCasualY() {
    srand(time(nullptr));
    return rand() % 768;
}

float generateCasualNumber() {
    srand(time(nullptr));
    return rand() % 10;
}


void updateGame(const GameEvent &gameEvent, GameCharacter &player, BulletFactory factory,
                bool &verse,
                const sf::Texture &bulletTexture, const sf::Texture &bulletTexture1, std::list<bullet *> &bullets,
                std::vector<Tile *> tiles, float playerSpeed) {
    switch (gameEvent) {
        case GameEvent::up: {
            if (player.isLegalMove((const std::vector<Tile *> &) tiles, 0, -playerSpeed))
                player.move(0, -playerSpeed);
            break;
        }
        case GameEvent::left: {
            verse = false;
            if (player.isLegalMove((const std::vector<Tile *> &) tiles, -playerSpeed, 0))
                player.move(-playerSpeed, 0);
            break;
        }
        case GameEvent::down: {
            if (player.isLegalMove((const std::vector<Tile *> &) tiles, 0, playerSpeed))
                player.move(0, playerSpeed);
            break;
        }
        case GameEvent::right: {
            verse = true;
            if (player.isLegalMove((const std::vector<Tile *> &) tiles, playerSpeed, 0))
                player.move(playerSpeed, 0);
            break;
        }
        case GameEvent::fire: {
            if (player.getWeapon()->getWeaponBullet() > 0) {
                player.getWeapon()->setWeaponBullet();
            }
            if (player.getWeapon()->type == WeaponType::Bazooka)
                bullets.push_back(
                        factory.createBullet(player, player.getWeapon()->getWeaponPower(), verse, bulletTexture1,
                                             player.getWeapon()->getWeaponRange()));
            else
                bullets.push_back(
                        factory.createBullet(player, player.getWeapon()->getWeaponPower(), verse, bulletTexture,
                                             player.getWeapon()->getWeaponRange()));
            break;
        }
        case GameEvent::noop: {
            break;
        }
    }
}

void itemControl(PowerUp &item, GameCharacter &player) {//controllo powerup
    if (player.getX() < item.getX() + 30 && player.getX() > item.getX() - 30 && player.getY() < item.getY() + 30 &&
        player.getY() > item.getY() - 30) {
        if (item.getType() == PowerUpType::Life)
            player.receiveDamage(-(item.getEffect()));
        if (item.getType() == PowerUpType::Energy)
            player.setEnergy(item.getEffect());
        item.used = true;
    }
}

void weaponControl(Weapon &weapon, GameCharacter &player) {
    if (weapon.getWeaponX() - 30 < player.getX() && weapon.getWeaponX() + 30 > player.getX() &&
        weapon.getWeaponY() - 30 < player.getY() && weapon.getWeaponY() + 30 > player.getY()) {
        player.equipWeapon(&weapon);
    }
}

PowerUp *createPowerUp(PowerUpType type, const sf::Texture &itemTexture) {
    PowerUp *powerUp = nullptr;
    sf::Sprite P;
    if (type == PowerUpType::Energy) {
        P.setTexture(itemTexture);
        powerUp = new PowerUp(generateCasualX(), generateCasualY(), 100, P, type);
    }
    if (type == PowerUpType::Life) {
        P.setTexture(itemTexture);
        powerUp = new PowerUp(generateCasualX(), generateCasualY(), 300, P, type);
    }
    powerUp->sprite.setPosition(sf::Vector2f(powerUp->getX(), powerUp->getY()));
    return powerUp;
}


// MOVIMENTO E CONTROLLO POSIZIONE NEMICI
void enemyControl(GameCharacter &player,
                  Enemy *enemy, bool &enemyHasWeapon) {//controllo delle posizioni
    float gameCharacterX, gameCharacterY;
    enemyHasWeapon = false;
    gameCharacterX = player.getX();
    gameCharacterY = player.getY();
    enemy->move(gameCharacterX, gameCharacterY);//movimento del nemico
    enemy->attack(player, enemyHasWeapon);
    enemy->sprite.setPosition(sf::Vector2f(enemy->getX(), enemy->getY()));

}


//MOVIMENTO E CONTROLLO POSIZIONE DEI PROIETTILI
void bulletMovement(GameCharacter &player, bullet *bullet, std::list<Enemy *> &enemies, std::vector<Tile *> &tiles) {
    if (bullet->bulletVerse)
        bullet->move(2);
    else
        bullet->move(-2);
    bullet->sprite.setPosition(sf::Vector2f(bullet->bulletX, bullet->bulletY));
    if (player.getX() >= bullet->bulletY - 0.5 && player.getY() <= bullet->bulletY + 0.5 &&
        player.getX() >= bullet->bulletX - 0.5 && player.getX() <= bullet->bulletX + 0.5)
        player.receiveDamage(bullet->damage);
    for (auto enemy:enemies) {
        if (enemy->getY() >= bullet->bulletY - 65 && enemy->getY() <= bullet->bulletY + 1.5 &&
            enemy->getX() >= bullet->bulletX - 1.5 && enemy->getX() <= bullet->bulletX + 1.5) {
            enemy->receiveDamage(bullet->damage);
        }
    }
    for (auto tile:tiles) {
        if (tile->yVertexTopSx < bullet->bulletY && tile->yVertexTopSx + 64 > bullet->bulletY &&
            tile->xVertexTopSx < bullet->bulletX && tile->xVertexTopSx + 64 > bullet->bulletX) {
            tile->destroyTile();
        }
    }
}


int main() {
    //SET GAME VALUES
    int spaceshipEnergy = 100, spaceshipHP = 1000;
    float playerSpeed = 1.1;
    float playerX = 512, playerY = 384;
    int basicWeaponPower = 50, basicWeaponCadence = 150, basicWeaponRange = 200;
    bool verse = true;
    bool enemyBulletVerse, enemyHasWeapon;
    int enemyBulletRange = 250, enemyBulletCount = 0, cadenceEnemyBullet = 100;
    int fireCount = 0;
    int spawnEnemy = 200;
    float maxNumberOfEnemy = 1;
    bool drawExplosion = false;
    int lifeOfExplosion = 0;
    float enemyDefeated = 0;
    int numberOfCycles = 0;
    int casualNumber;
    std::vector<Tile *> tiles;
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Volcan Battle");
    // define the level with an array of tile indices


    // create the tilemap from the level definition
    TileMap map;
    if (!map.readMatrix("image/image00.png", "matrice.txt", tiles))
        return -1;
    // *********background
    /*
    sf::Texture sfondo;
    if (!sfondo.loadFromFile("image/Background.png"))
        return -1;
    sf::Sprite sf;
    sf.setTexture(sfondo);
    sf.setTextureRect(sf::IntRect(0, 0, 1024, 512));
    ************* end background
     */


    // *********charter1
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("image/Ship00.png"))return -1;
    sf::Sprite ch1;
    ch1.setTexture(playerTexture);
    GameCharacter player(spaceshipHP, playerX, playerY, spaceshipEnergy, ch1);//istanza personaggio
    Weapon baseGun(basicWeaponPower, basicWeaponCadence, basicWeaponRange);//istanza arma di base
    player.equipWeapon(&baseGun);
    player.sprite.setPosition(sf::Vector2f(player.getX(), player.getY()));
    //************* VISTE LIMITE
    sf::View view1(sf::Vector2f(player.getXMax() - 512, 384), sf::Vector2f(1024, 764));
    sf::View view2(sf::Vector2f(player.getXMin() + 512, 384), sf::Vector2f(1024, 764));
    //************* sprite Weapon
    sf::Texture machineGunTexture;
    machineGunTexture.loadFromFile("image/gun.png");
    sf::Texture laserGunTexture;
    laserGunTexture.loadFromFile("image/gun1.png");
    sf::Texture bazookaTexture;
    bazookaTexture.loadFromFile("image/gun2.png");
    std::list<Weapon *> weapons;
    //************* sprite item

    sf::Texture lifeTexture;
    lifeTexture.loadFromFile("image/life1.png");
    sf::Texture energyTexture;
    energyTexture.loadFromFile("image/statuetta.png");
    std::list<PowerUp *> items;

    sf::Texture explosionTexture;
    explosionTexture.loadFromFile("image/explosion.png");
    sf::Sprite explosion(explosionTexture);

    //************ sprite enemy
    sf::Texture enemyTexture;
    sf::Texture enemyTexture1;
    enemyTexture.loadFromFile("image/alien2.png");
    enemyTexture1.loadFromFile("image/Ship10.png");
    std::list<Enemy *> enemies;

    //************** sprite proiettili
    sf::Texture BulletCommon;
    BulletCommon.loadFromFile("image/projectile00.png");
    sf::Texture BulletBazooka;
    BulletBazooka.loadFromFile("image/shot7.png");
    sf::Texture BulletLaser;
    BulletLaser.loadFromFile("image/projectile00.png");
    std::list<bullet *> bullets;
    EnemyFactory factoryE;
    BulletFactory factoryB;
    WeaponFactory factoryW;
    //************* GAMELOOP
    while (window.isOpen()) {
        if (!map.loadMap(sf::Vector2u(64, 64), 128, 12, tiles))
            return -1;
        //VISTA MAPPA
        sf::View view0(sf::Vector2f(player.getX(), 384), sf::Vector2f(1024, 764));

        //*********************** CREAZIONE NEMICI CON UN NUMERO MASSIMO OGNI 10000 CICLI
        if (enemies.size() < maxNumberOfEnemy) {
            if (numberOfCycles >= spawnEnemy) {
                if (static_cast<int>(generateCasualNumber()) % 2 == 0) {
                    enemies.push_back(factoryE.createEnemy(EnemyType::Kamikaze, enemyTexture, generateCasualX(),
                                                           generateCasualY(), ((generateCasualNumber() / 100) +
                                                                               (maxNumberOfEnemy / 100))));
                } else
                    enemies.push_back(factoryE.createEnemy(EnemyType::Common, enemyTexture1, generateCasualX(),
                                                           generateCasualY(),
                                                           ((generateCasualNumber() / 50) + (maxNumberOfEnemy / 100))));
                numberOfCycles = 0;
            }
        }
        numberOfCycles++;

        //***************** MOVIMENTO GAMECHARACTER E CONSEGUENTE MOVIMENTO DEI NEMICI
        enemyBulletCount++;
        GameEvent gameEvent = getEvent(fireCount, player.getWeapon()->getWeaponCadence());
        updateGame(gameEvent, player, factoryB, verse, BulletCommon, BulletBazooka,
                   bullets, tiles, playerSpeed);//mossa giocatore
        player.sprite.setPosition(sf::Vector2f(player.getX(), player.getY()));
        for (auto enemy:enemies) {
            enemyControl(player, enemy, enemyHasWeapon);
            if (enemyHasWeapon && enemyBulletCount >= cadenceEnemyBullet) {
                enemyBulletVerse = enemy->getX() < player.getX();
                bullets.push_back(
                        factoryB.createBullet(*enemy, enemy->getEnemyDamage(), enemyBulletVerse,
                                              BulletCommon, enemyBulletRange));
                enemyBulletCount = 0;
            }
        }
        //************** MOVIMENTO PROIETTILI
        for (auto bullet:bullets) {
            bulletMovement(player, bullet, enemies, tiles);
        }
        //**************** CREAZIONE ARMI E POWERUP
        if (enemyDefeated >= 1 + maxNumberOfEnemy) {
            casualNumber = static_cast<int>(generateCasualNumber());
            if (casualNumber % 5 == 0)
                weapons.push_back(
                        factoryW.createWeapon(WeaponType::Bazooka, generateCasualX(), generateCasualY(),
                                              bazookaTexture));
            if (casualNumber % 5 == 1)
                weapons.push_back(
                        factoryW.createWeapon(WeaponType::MachineGun, generateCasualX(), generateCasualY(),
                                              machineGunTexture));
            if (casualNumber % 5 == 2)
                weapons.push_back(
                        factoryW.createWeapon(WeaponType::LaserGun, generateCasualX(), generateCasualY(),
                                              laserGunTexture));
            if (casualNumber % 5 == 3)
                items.push_back(createPowerUp(PowerUpType::Life, lifeTexture));
            if (casualNumber % 5 == 4)
                items.push_back(createPowerUp(PowerUpType::Energy, energyTexture));
            enemyDefeated = 0;
            maxNumberOfEnemy++;
        }
        //************CONTROLLO E ELIMINAZIONE POWERUP
        for (auto item:items) {
            itemControl(*item, player);
        }
        if (!items.empty()) {
            PowerUp *powerUp;
            auto it = items.begin();
            while (it != items.end()) {
                powerUp = *it;
                it++;
                if (powerUp->used) {
                    items.remove(powerUp);
                }
            }
        }
        // ************CONTROLLO E ELIMINAZIONE ARMI
        for (auto weapon:weapons) {
            weaponControl(*weapon, player);
        }
        if (player.getWeapon()->getWeaponBullet() == 0) {
            weapons.remove(player.getWeapon());
            player.equipWeapon(&baseGun);
        }
        //**************  CANCELLA NEMICI
        if (!enemies.empty()) {
            Enemy *enemy;
            auto it = enemies.begin();
            while (it != enemies.end()) {
                enemy = *it;
                it++;
                if (enemy->getHP() <= 0) {
                    explosion.setPosition(sf::Vector2f(enemy->getX() - 400, enemy->getY() - 300));
                    enemies.remove(enemy);
                    drawExplosion = true;
                    enemyDefeated++;
                }
            }
        }
        //************* ELIMINAZIONE PROIETTILI
        if (!bullets.empty()) {
            bullet * bullet;
            auto it = bullets.begin();
            while (it != bullets.end()) {
                bullet = *it;
                it++;
                if (bullet->bulletLife == bullet->range) {
                    bullets.remove(bullet);
                }
            }
        }
        //************* DISEGNA SPRITE E MAPPA
        window.clear();
        // window.draw(sf);//FIXME
        if (player.getX() >= player.getXMin() + 512 || player.getX() <= player.getXMax() - 512)
            window.setView(view0);
        if (player.getX() < player.getXMin() + 512)
            window.setView(view2);
        if (player.getX() > player.getXMax() - 512)
            window.setView(view1);
        window.draw(map);
        /*
        window.draw(life);
        window.draw(power);
        window.draw(energy);
        */

        window.draw(player.sprite);
        for (auto enemy:enemies)
            window.draw(enemy->sprite);
        for (auto bullet:bullets)
            window.draw(bullet->sprite);
        for (auto weapon:weapons) {
            if (!weapon->equip)
                window.draw(weapon->sprite);
        }
        for (auto item:items)
            window.draw(item->sprite);
        if (drawExplosion) {
            lifeOfExplosion++;
            window.draw(explosion);
            if (lifeOfExplosion >= 500) {
                drawExplosion = false;
                lifeOfExplosion = 0;
            }
        }
        window.display();
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (player.getHP() <= 0) {
            window.close();
        }

    }
}