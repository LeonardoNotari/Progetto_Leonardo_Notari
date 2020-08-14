
#include <list>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "PowerUp.h"
#include "GameCharacter.h"
#include "Weapon.h"
#include "bullet.h"
#include "TileMap.h"
#include "EnemyFactory.h"
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

float generateCasualNumber() {
    srand(time(nullptr));
    return rand() % 800+300;
}


void updateGame(const GameEvent &gameEvent, GameCharacter &player, BulletFactory factory,
                bool &verse,
                const sf::Texture &bulletTexture, std::list<bullet *> &bullets,float playerSpeed) {
    switch (gameEvent) {
        case GameEvent::up: {
            player.move(0, -playerSpeed);
            break;
        }
        case GameEvent::left: {
            verse = false;
            player.move(-playerSpeed, 0);
            break;
        }
        case GameEvent::down: {
            player.move(0, playerSpeed);
            break;
        }
        case GameEvent::right: {
            verse = true;
            player.move(playerSpeed, 0);
            break;
        }
        case GameEvent::fire: {
            if(player.getWeapon()->getWeaponBullet()>0) {
                player.getWeapon()->setWeaponBullet();
            }
            bullets.push_back(
                    factory.createBullet(player,BulletType::Common, player.getWeapon()->getWeaponPower(), verse, bulletTexture,player.getWeapon()->getWeaponRange()));
            break;
        }
        case GameEvent::noop: {
            break;
        }
    }
}
void itemControl(  PowerUp& item, GameCharacter &player) {//controllo powerup
    if (player.getX() < item.getX() + 30 && player.getX() > item.getX() - 30 && player.getY() < item.getY() + 30 && player.getY() > item.getY() - 30){
        if(item.getType()==PowerUpType::Life)
            player.receiveDamage(-(item.getEffect()));
        if(item.getType()==PowerUpType::Energy)
            player.setEnergy(item.getEffect());
        item.used=true;
        }
}

void weaponControl(Weapon& weapon, GameCharacter &player) {
    if (weapon.getWeaponX()-30 < player.getX() && weapon.getWeaponX()+30 > player.getX()   &&   weapon.getWeaponY()-30 < player.getY() && weapon.getWeaponY()+30 > player.getY()) {
        player.equipWeapon( &weapon);
    }
}

PowerUp * createPowerUp(PowerUpType type,const sf::Texture & itemTexture){
    PowerUp *powerUp = nullptr;
    sf::Sprite P;
    if (type == PowerUpType::Energy) {
        P.setTexture(itemTexture);
        powerUp = new PowerUp(generateCasualNumber(),generateCasualNumber(),100,P,type);
    }
    if (type == PowerUpType::Life) {
        P.setTexture(itemTexture);
        powerUp = new PowerUp(generateCasualNumber(),generateCasualNumber(),100,P,type);
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
void bulletMovement(GameCharacter &player, bullet *bullet, std::list<Enemy *> &enemies) {
    if (bullet->bulletVerse)
        bullet->move(1);
    else
        bullet->move(-1);
    bullet->sprite.setPosition(sf::Vector2f(bullet->bulletX, bullet->bulletY));
    if (player.getX() >= bullet->bulletY - 0.5 && player.getY() <= bullet->bulletY + 0.5 &&
        player.getX() >= bullet->bulletX - 0.5 && player.getX() <= bullet->bulletX + 0.5)
        player.receiveDamage(bullet->damage);
    for (auto enemy:enemies) {
        if (enemy->getY() >= bullet->bulletY - 0.5 && enemy->getY() <= bullet->bulletY + 0.5 &&
            enemy->getX() >= bullet->bulletX - 0.5 && enemy->getX() <= bullet->bulletX + 0.5) {
            enemy->receiveDamage(bullet->damage);
        }
    }
}


int main() {
    //SET GAME VALUES
    int spaceshipEnergy = 100, spaceshipHP = 50000;
    float playerSpeed=0.3;
    float playerX=0,playerY=0;
    int basicWeaponPower = 50, basicWeaponCadence = 300, basicWeaponRange = 500;
    bool verse = true;
    bool enemyBulletVerse, enemyHasWeapon;
    int enemyBulletRange = 500, enemyBulletCount = 0, cadenceEnemyBullet = 150;
    int fireCount = 0;
    int spawnEnemy = 1000;
    float maxNumberOfEnemy = 1;
    bool drawExplosion = false;
    int lifeOfExplosion = 0;
    float enemyDefeated = 0;
    int numberOfCycles = 0;


    sf::RenderWindow window(sf::VideoMode(1024, 768), "Volcan Battle");

    // define the level with an array of tile indices


    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("image/image.png",sf::Vector2u(64, 64), "matrice.txt", 16, 12))
        return -1;

    // *********background
    sf::Texture sfondo;
    if (!sfondo.loadFromFile("image/Background.png"))
        return -1;
    sf::Sprite sf;
    sf.setTexture(sfondo);
    sf.setTextureRect(sf::IntRect(0, 0, 1024, 512));
    //************* end background


    // *********charter1
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("image/Ship0.png"))return -1;
    sf::Sprite ch1;
    ch1.setTexture(playerTexture);
    GameCharacter player(spaceshipHP,playerX,playerY,spaceshipEnergy, ch1);//istanza personaggio
    Weapon baseGun(basicWeaponPower, basicWeaponCadence,basicWeaponRange);//istanza arma di base
    player.equipWeapon( &baseGun);
    player.sprite.setPosition(sf::Vector2f(player.getX(), player.getY()));
    //************* end charter1

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
    energyTexture.loadFromFile("image/marker_statue3.png");
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
    sf::Texture Bullet1;
    Bullet1.loadFromFile("image/projectile.png");
    std::list<bullet *> bullets;



    EnemyFactory factoryE;
    BulletFactory factoryB;
    WeaponFactory factoryW;
    //************* GAMELOOP
    while (window.isOpen()) {
        //*********************** CREAZIONE NEMICI CON UN NUMERO MASSIMO OGNI 10000 CICLI
        if (enemies.size() < maxNumberOfEnemy) {
            if (numberOfCycles >= spawnEnemy) {
                if (static_cast<int>(generateCasualNumber()) % 2 == 0) {
                    enemies.push_back(factoryE.createEnemy(EnemyType::Kamikaze, enemyTexture, generateCasualNumber(),
                                                           generateCasualNumber(),
                                                           (generateCasualNumber() / 40000) * maxNumberOfEnemy));
                } else
                    enemies.push_back(factoryE.createEnemy(EnemyType::Common, enemyTexture1, generateCasualNumber(),
                                                           generateCasualNumber(),
                                                           (generateCasualNumber() / 40000) * maxNumberOfEnemy));
                numberOfCycles = 0;
            }
        }
        numberOfCycles++;

        //***************** MOVIMENTO GAMECHARACTER E CONSEGUENTE MOVIMENTO DEI NEMICI
        enemyBulletCount++;
        GameEvent gameEvent = getEvent(fireCount, player.getWeapon()->getWeaponCadence());
        updateGame(gameEvent, player, factoryB, verse, Bullet1,
                   bullets, playerSpeed);//mossa giocatore
        player.sprite.setPosition(sf::Vector2f(player.getX(), player.getY()));
        for (auto enemy:enemies) {
            enemyControl(player, enemy, enemyHasWeapon);
            if (enemyHasWeapon && enemyBulletCount >= cadenceEnemyBullet) {
                enemyBulletVerse = enemy->getX() < player.getX();
                bullets.push_back(
                        factoryB.createBullet(*enemy, BulletType::Common, enemy->getEnemyDamage(), enemyBulletVerse,
                                              Bullet1, enemyBulletRange));
                enemyBulletCount = 0;
            }
        }
        //************** MOVIMENTO PROIETTILI
        for (auto bullet:bullets) {
            bulletMovement(player, bullet, enemies);
        }
        //**************** CREAZIONE ARMI E POWERUP
        if (enemyDefeated >= 2 + maxNumberOfEnemy) {
            if (static_cast<int>(generateCasualNumber()) % 3 == 0)
                weapons.push_back(
                        factoryW.createWeapon(WeaponType::Bazooka, generateCasualNumber(), generateCasualNumber(),
                                              bazookaTexture));
            if (static_cast<int>(generateCasualNumber()) % 3 == 1)
                weapons.push_back(
                        factoryW.createWeapon(WeaponType::MachineGun, generateCasualNumber(), generateCasualNumber(),
                                              machineGunTexture));
            if (static_cast<int>(generateCasualNumber()) % 3 == 2)
                weapons.push_back(
                        factoryW.createWeapon(WeaponType::LaserGun, generateCasualNumber(), generateCasualNumber(),
                                              laserGunTexture));
            if (static_cast<int>(generateCasualNumber()) % 2 == 0)
                items.push_back(createPowerUp(PowerUpType::Life, lifeTexture));
            else
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
        // ************CONTROLLO E ELEIMINAZIONE ARMI
        for (auto weapon:weapons) {
            weaponControl(*weapon, player);
        }
        if (player.getWeapon()->getWeaponBullet() == 0){
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
       // window.draw(sf);
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
            if(!weapon->equip)
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

    }
}