
#include <list>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
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


GameEvent getEvent(int &cicles, int cadence) {

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
        if (cicles == cadence) {
            cicles = 0;
            return GameEvent::fire;
        } else {
            cicles++;
            return GameEvent::noop;
        }
    }
    return GameEvent::noop;
}

float generateCasualNumber() {
    srand(time(nullptr));
    return rand() % 800;
}


void updateGame(const GameEvent &gameEvent, int power, GameCharacter &player, Weapon *gun, BulletFactory factory,
                bool &verse,
                const sf::Texture &bulletTexture, std::list<bullet *> &bullets) {
    switch (gameEvent) {
        case GameEvent::up: {
            player.move(0, -0.1);
            break;
        }
        case GameEvent::left: {
            verse = false;
            player.move(-0.1, 0);
            break;
        }
        case GameEvent::down: {
            player.move(0, 0.1);
            break;
        }
        case GameEvent::right: {
            verse = true;
            player.move(0.1, 0);
            break;
        }
        case GameEvent::fire: {
            bullets.push_back(
                    factory.createBullet(BulletType::Common, power, verse, bulletTexture, player.getGameCharacterX(),
                                         player.getGameCharacterY(), player.getWeapon()->getWeaponRange()));
            break;
        }
        case GameEvent::noop: {
            break;
        }
    }
}

// FIXME CONTROLLO POSIZIONE ARMI
void weaponControl(Weapon weapon, GameCharacter player) {
    if (weapon.getWeaponX() == player.getGameCharacterX() && weapon.getWeaponY() == player.getGameCharacterY())
        player.equipWeapon(weapon.getWeaponCost(), &weapon);
}


// MOVIMENTO E CONTROLLO POSIZIONE NEMICI
void enemyControl(GameCharacter &player,
                  Enemy *enemy, bool &enemyHasWeapon) {//controllo delle posizioni
    float gameCharacterX, gameCharacterY;
    enemyHasWeapon = false;
    gameCharacterX = player.getGameCharacterX();
    gameCharacterY = player.getGameCharacterY();
    enemy->move(gameCharacterX, gameCharacterY);//movimento del nemico
    enemy->attack(player, enemyHasWeapon);
    enemy->sprite.setPosition(sf::Vector2f(enemy->getEnemyX(), enemy->getEnemyY()));

}


//MOVIMENTO E CONTROLLO POSIZIONE DEI PROIETTILI
void bulletMovement(GameCharacter &player, bullet *bullet, std::list<Enemy *> &enemies) {
    if (bullet->bulletVerse)
        bullet->move(1);
    else
        bullet->move(-1);
    bullet->sprite.setPosition(sf::Vector2f(bullet->bulletX, bullet->bulletY));
    if (player.getGameCharacterX() >= bullet->bulletY - 0.5 && player.getGameCharacterY() <= bullet->bulletY + 0.5 &&
        player.getGameCharacterX() >= bullet->bulletX - 0.5 && player.getGameCharacterX() <= bullet->bulletX + 0.5)
        player.receiveDamage(bullet->damage);
    for (auto enemy:enemies) {
        if (enemy->getEnemyY() >= bullet->bulletY - 0.5 && enemy->getEnemyY() <= bullet->bulletY + 0.5 &&
            enemy->getEnemyX() >= bullet->bulletX - 0.5 && enemy->getEnemyX() <= bullet->bulletX + 0.5) {
            enemy->receiveDamage(bullet->damage);
        }
    }
}


int main() {
    //SET GAME VALUES
    int spaceshipEnergy = 0, spaceshipHP = 50000;
    int basicWeaponPower = 50, basicWeaponCadence = 300, basicWeaponRange = 500;
    bool verse = true;
    bool enemyBulletVerse, enemyHasWeapon;
    int enemyBulletRange = 500, enemyBulletCount = 0, cadenceEnemyBullet = 200;
    int fireCount = 0;
    int playerDamage;
    int spawnEnemy = 10000;
    int maxNumberOfEnemy = 4;
    bool drawExplosion = false;
    int lifeOfExplosion = 0;
    int enemyDefeated = 0;
    int numberOfCicles = 0;


    // create the window
    sf::RenderWindow window(sf::VideoMode(2000, 512), "Volcano Battle");
    // create background
    // define the level with an array of tile indices
    const int level[] =
            {


                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 2, 4,
                    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 3, 4,
            };
    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("image/tilesetlast.png", sf::Vector2u(32, 32), level, 32, 3))
        return -1;
    // *********TESTI A DESTRA DELL'AREA DI GIOCO
    sf::Text life;
    sf::Text power;
    sf::Font font;
    if (!font.loadFromFile("Roboto-Black.ttf")) {
        // error...
    }
    life.setFont(font);
    power.setFont(font);
    life.setString("Lives:");
    life.setPosition(1027, 10);
    power.setString("Power:");
    power.setPosition(1027, 40);
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
    GameCharacter player(spaceshipEnergy, spaceshipHP, ch1);//istanza personaggio
    Weapon baseGun(basicWeaponPower, basicWeaponCadence, basicWeaponRange);//istanza arma di base
    player.equipWeapon(baseGun.getWeaponCost(), &baseGun);
    player.sprite.setPosition(sf::Vector2f(player.getGameCharacterX(), player.getGameCharacterY()));
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
    //FIXME DEFINIRE MEGLIO E AGGIUNGERE CONTROLLO
    sf::Texture lifeTexture;
    lifeTexture.loadFromFile("image/life1.png");
    sf::Sprite lifeIncrease(lifeTexture);
    lifeIncrease.setPosition(sf::Vector2f(500, 200));

    sf::Texture energyTexture;
    energyTexture.loadFromFile("image/marker_statue3.png");
    sf::Sprite energyIncrease(energyTexture);
    energyIncrease.setPosition(sf::Vector2f(550, 200));


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
    std::list<sf::Sprite> bulletSprites;
    std::list<bullet *> bullets;
    EnemyFactory factoryE;
    BulletFactory factoryB;
    WeaponFactory factoryW;
    //************* GAMELOOP
    while (window.isOpen()) {
        playerDamage = player.getWeapon()->getWeaponPower();
        //*********************** CREAZIONE NEMICI CON UN NUMERO MASSIMO OGNI 10000 CICLI
        if (enemies.size() < maxNumberOfEnemy) {
            if (numberOfCicles == spawnEnemy) {
                if (static_cast<int>(generateCasualNumber()) % 2 == 0) {
                    enemies.push_back(factoryE.createEnemy(EnemyType::Kamikaze, enemyTexture, generateCasualNumber(),
                                                           generateCasualNumber(), generateCasualNumber() / 10000));
                } else
                    enemies.push_back(factoryE.createEnemy(EnemyType::Common, enemyTexture1, generateCasualNumber(),
                                                           generateCasualNumber(), generateCasualNumber() / 10000));
                numberOfCicles = 0;
            }
        }
        numberOfCicles++;
        //***************** CREAZIONE ARMI
        if (enemyDefeated == 4) {
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
            enemyDefeated = 0;
        }
        //***************** MOVIMENTO GAMECHARACTER E CONSEGUENTE MOVIMENTO DEI NEMICI
        enemyBulletCount++;
        GameEvent gameEvent = getEvent(fireCount, player.getWeapon()->getWeaponCadence());
        updateGame(gameEvent, playerDamage, player, player.getWeapon(), factoryB, verse, Bullet1,
                   bullets);//mossa giocatore
        player.sprite.setPosition(sf::Vector2f(player.getGameCharacterX(), player.getGameCharacterY()));
        for (auto enemy:enemies) {
            enemyControl(player, enemy, enemyHasWeapon);
            if (enemyHasWeapon && enemyBulletCount >= cadenceEnemyBullet) {
                enemyBulletVerse = enemy->getEnemyX() < player.getGameCharacterX();
                bullets.push_back(
                        factoryB.createBullet(BulletType::Common, enemy->getEnemyDamage(), enemyBulletVerse,
                                              Bullet1,
                                              enemy->getEnemyX(),
                                              enemy->getEnemyY(), enemyBulletRange));
                enemyBulletCount = 0;
            }
        }
        //************** MOVIMENTO PROIETTILI
        for (auto bullet:bullets) {
            bulletMovement(player, bullet, enemies);
        }
        //**************  CANCELLA NEMICI
        if (!enemies.empty()) {
            Enemy *enemy;
            auto it = enemies.begin();
            while (it != enemies.end()) {
                enemy = *it;
                it++;
                if (enemy->getEnemyHP() <= 0) {
                    explosion.setPosition(sf::Vector2f(enemy->getEnemyX() - 400, enemy->getEnemyY() - 300));
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
        window.clear(sf::Color(83, 87, 79));
        window.draw(sf);
        window.draw(map);
        window.draw(life);
        window.draw(power);
        for (auto enemy:enemies)
            window.draw(enemy->sprite);
        for (auto bullet:bullets)
            window.draw(bullet->sprite);
        for (auto weapon:weapons)
            window.draw(weapon->sprite);
        window.draw(player.sprite);
        /* FIXME item
        window.draw(lifeIncrease);
        window.draw(energyIncrease);
         */
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
        if (player.getGameCharacterHP() <= 0)//CHIUDE FINESTRA SE LA VITA DEL GIOCATORE <=0
            window.close();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}