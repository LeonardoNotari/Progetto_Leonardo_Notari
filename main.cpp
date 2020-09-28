
#include <list>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include "PowerUp.h"
#include "Resource.h"
#include "GameCharacter.h"
#include "Weapon.h"
#include "bullet.h"
#include "TileMap.h"
#include "Tile.h"
#include "EnemyFactory.h"
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
    return rand() % 8000+64;
}

float generateCasualY() {
    srand(time(nullptr));
    return rand() % 640+64;
}

float generateCasualNumber() {
    srand(time(nullptr));
    return rand() % 10;
}

bullet *generateBullet(const Character &character, int power, bool verse, const sf::Texture &bulletTexture,
                                    int bulletRange) {
    bullet *bullet ;
    sf::Sprite B;
    B.setTexture(bulletTexture);
    bullet = new class bullet(power, verse, character.getX(), character.getY(), B, bulletRange);
    bullet->sprite.setPosition(sf::Vector2f(character.getX(), character.getY()));
    return bullet;
}

void updateGame(const GameEvent &gameEvent, GameCharacter &player,
                bool &verse,const sf::Texture &bulletTexture, const sf::Texture &bulletTexture1,
                std::list<bullet *> &bullets, float playerSpeed,const TileMap& map, std::string& lastMove) {
    switch (gameEvent) {
        case GameEvent::up: {
            lastMove="up";
            player.move(0, -playerSpeed,map);
            break;
        }
        case GameEvent::left: {
            verse = false;
            lastMove="left";
            player.move(-playerSpeed, 0,map);
            break;
        }
        case GameEvent::down: {
            lastMove="down";
            player.move(0, playerSpeed,map);
            break;
        }
        case GameEvent::right: {
            verse = true;
            lastMove="right";
            player.move(playerSpeed, 0,map);
            break;
        }
        case GameEvent::fire: {
            if (player.getWeapon()->getWeaponBullet() > 0) {
                player.getWeapon()->setWeaponBullet();
            }
            if (player.getWeapon()->type == WeaponType::Bazooka)
                bullets.push_back(
                        generateBullet(player, player.getWeapon()->getWeaponPower(), verse, bulletTexture1,
                                             player.getWeapon()->getWeaponRange()));
            else
                bullets.push_back(
                        generateBullet(player, player.getWeapon()->getWeaponPower(), verse, bulletTexture,
                                             player.getWeapon()->getWeaponRange()));
            break;
        }
        case GameEvent::noop: {
            if(lastMove=="up")
                player.move(0, -0.3,map);
            if(lastMove=="left")
                player.move(-0.6, 0,map);
            if(lastMove=="down")
                player.move(0, 0.3,map);
            if(lastMove=="right")
                player.move(0.6, 0,map);
            break;
        }
    }
}

void powerUpControl(PowerUp &item, GameCharacter &player) {//controllo powerup
    if (player.getX() < item.getX() + 30 && player.getX() > item.getX() - 30 && player.getY() < item.getY() + 30 &&
        player.getY() > item.getY() - 30) {
        if (item.getType() == PowerUpType::Life)
            player.receiveDamage(-(item.getEffect()));
        if (item.getType() == PowerUpType::Energy)
            player.setEnergy(item.getEffect());
        item.used = true;
    }
}

bool weaponControl(Weapon &weapon, GameCharacter &player) {
    if (weapon.getWeaponX() - 30 < player.getX() && weapon.getWeaponX() + 30 > player.getX() &&
        weapon.getWeaponY() - 30 < player.getY() && weapon.getWeaponY() + 30 > player.getY()) {
        player.equipWeapon(&weapon);
        return true;
    }
    return false;
}

PowerUp *createPowerUp(PowerUpType type) {
    PowerUp *powerUp = nullptr;
    sf::Sprite sprite;
    int increment;
    if (type == PowerUpType::Energy) {
        sprite = Resource::getInstance()->setSprite(TypeOfSprite::EnergyPU);
        increment = 100;
    }
    if (type == PowerUpType::Life){
        sprite = Resource::getInstance()->setSprite(TypeOfSprite::LifePU);
        increment = 300;
    }
    powerUp = new PowerUp(generateCasualX(), generateCasualY(), increment,sprite, type);
    powerUp->sprite.setPosition(sf::Vector2f(powerUp->getX(), powerUp->getY()));
    return powerUp;
}


// MOVIMENTO E CONTROLLO POSIZIONE NEMICI
void enemyControl(GameCharacter &player,
                  Enemy *enemy, bool &enemyHasWeapon,const TileMap& map) {//controllo delle posizioni
    float gameCharacterX, gameCharacterY;
    enemyHasWeapon = false;
    gameCharacterX = player.getX();
    gameCharacterY = player.getY();
    if(player.getX() > enemy->getX()-30 && player.getX() < enemy->getX()+30 && player.getY() > enemy->getY()-40 && player.getY() < enemy->getY()+40) {
        player.receiveDamage(10);
        enemy->move(player.getX(),enemy->getY(),map);
        if(player.getX() > enemy->getX() )
            player.move(3, 0, map);
        if(player.getX() < enemy->getX() )
            player.move(-3, 0, map);
    }
    enemy->move(gameCharacterX, gameCharacterY,map);//movimento del nemico
    enemy->attack(player, enemyHasWeapon);
    enemy->sprite.setPosition(sf::Vector2f(enemy->getX(), enemy->getY()));
}


//MOVIMENTO E CONTROLLO POSIZIONE DEI PROIETTILI
void bulletMovement(GameCharacter &player, bullet *bullet, std::list<Enemy *> &enemies, std::vector<Tile *> &tiles) {
    if (bullet->bulletVerse)
        bullet->move(2.3);
    else
        bullet->move(-2.3);
    bullet->sprite.setPosition(sf::Vector2f(bullet->bulletX, bullet->bulletY));
    if (player.getY() >= bullet->bulletY - 3 && player.getY() <= bullet->bulletY + 3 &&
        player.getX() >= bullet->bulletX - 1.9 && player.getX() <= bullet->bulletX + 1.9) {
        player.receiveDamage(bullet->damage);
        bullet->bulletLife=bullet->range;
    }
    for (auto enemy:enemies) {
        if (enemy->getY() >= bullet->bulletY - 65 && enemy->getY() <= bullet->bulletY + 1.5 &&
            enemy->getX() >= bullet->bulletX - 1.9 && enemy->getX() <= bullet->bulletX + 1.9) {
            enemy->receiveDamage(bullet->damage);
            bullet->bulletLife=bullet->range;
        }
    }
    for (auto tile:tiles) {
        if (tile->yVertexTopSx < bullet->bulletY && tile->yVertexTopSx + 64 > bullet->bulletY &&
            tile->xVertexTopSx < bullet->bulletX && tile->xVertexTopSx + 64 > bullet->bulletX) {
            if(tile->getIsDestructible())
                   tile->destroyTile();
            if(!tile->getIsCrossable())
                   bullet->bulletLife=bullet->range;
        }
    }
}


int main() {
    //SET GAME VALUES
    int spaceshipEnergy = 100, spaceshipHP = 1000;
    float playerSpeed = 1.5;
    float playerX = 512, playerY = 384;
    int basicWeaponPower = 50, basicWeaponCadence = 130, basicWeaponRange = 200;
    bool verse = true;
    bool enemyBulletVerse, enemyHasWeapon;
    int enemyBulletRange = 250, enemyBulletCount = 0, cadenceEnemyBullet = 80;
    int fireCount = 0;
    float countWeaponPowerUp=0;
    int spawnEnemy = 200;
    float maxNumberOfEnemy = 2;
    bool drawExplosion = false;
    int lifeOfExplosion = 0;
    int numberOfCycles = 0;
    int casualNumber,durateGoal=0;
    int actualScore;
    std::string lastMove;
    std::string goalReach;
    // carica l'immagine dello sfondo della pagina iniziale
    sf::Texture background;
    if (!background.loadFromFile("image/page1.png"))
    {
        return -1;
    }
    sf::Sprite begin;
    begin.setTexture(background);
    // carica l'immagine del gameover
    sf::Texture gameovert;
    if (!gameovert.loadFromFile("image/page3.png"))
    {
        return -1;
    }
    sf::Sprite gameover;
    gameover.setTexture(gameovert);
    char stato='0';
    //*********************************************************************************************************+
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Volcan Battle");
    // define the level with an array of tile indices
    // create the tilemap from the level definition
    TileMap map;
    if (!map.readMatrix("image/image00.png", "matrice.txt"))
        return -1;

    // *********charter1
    GameCharacter player(spaceshipHP, playerX, playerY, spaceshipEnergy, Resource::getInstance()->setSprite(TypeOfSprite::Player) );//istanza personaggio
    Weapon baseGun(basicWeaponPower, basicWeaponCadence, basicWeaponRange);//istanza arma di base
    player.equipWeapon(&baseGun);
    player.sprite.setPosition(sf::Vector2f(player.getX(), player.getY()));
    //************* VISTE LIMITE
    sf::View view1(sf::Vector2f(player.getXMax() - 512, 384), sf::Vector2f(1024, 764));
    sf::View view2(sf::Vector2f(player.getXMin() + 512, 384), sf::Vector2f(1024, 764));
    sf::Texture explosionTexture;
    explosionTexture.loadFromFile("image/explosion.png");
    sf::Sprite explosion(explosionTexture);
    //************ enemy list
    std::list<Enemy *> enemies;
    std::list<Weapon *> weapons;
    std::list<PowerUp *> powerUps;
    //************** sprite proiettili
    sf::Texture BulletCommon;
    BulletCommon.loadFromFile("image/projectile00.png");
    sf::Texture BulletBazooka;
    BulletBazooka.loadFromFile("image/shot7.png");
    sf::Texture BulletLaser;
    BulletLaser.loadFromFile("image/projectile00.png");
    std::list<bullet *> bullets;
    EnemyFactory factoryE;
    WeaponFactory factoryW;
    //FIXME PROVA SCRITTE
    std::string hpPlayer;
    std::string playerScore;
    std::string HigScore;
    std::string EPlayer;
    std::string PPlayer;
    std::string BPlayer;
    sf::Text Hp;
    sf::Text Hs;
    sf::Text Goal;
    sf::Text Score;
    sf::Font font;
    if(!font.loadFromFile("image/Roboto-Black.ttf"))
        return -1;
    Hp.setFont(font);
    Hp.setCharacterSize(16);
    Hs.setFont(font);
    Hs.setCharacterSize(40);
    Hs.setPosition(560,250);
    Goal.setFont(font);
    Goal.setCharacterSize(50);
    Score.setFont(font);
    Score.setCharacterSize(40);
    Score.setPosition(560,140);
    //************* GAMELOOP
    while (window.isOpen())
    {
        if (stato=='0')
            window.draw(begin);
        if (stato=='2') {
            std::ifstream inputFile ("record.txt", std::ifstream::in);
            std::getline (inputFile, HigScore,',');
            //trasformo punteggio in un intero
            std::stringstream ss;
            int pRecord;
            ss << HigScore;
            ss >> pRecord;
            Hs.setString(HigScore);
            if(actualScore>pRecord){
                std::ofstream outputfile("record.txt",std::ofstream::out);
                outputfile<<playerScore;
            }
            Score.setString(playerScore);
            window.draw(gameover);
            window.draw(Score);
            window.draw(Hs);
        }
        if (stato=='1') {
            if (!map.loadMap(sf::Vector2u(64, 64), 128, 12))
                return -1;
            //VISTA MAPPA
            sf::View view0(sf::Vector2f(player.getX(), 384), sf::Vector2f(1024, 764));

            //*********************** CREAZIONE NEMICI CON UN NUMERO MASSIMO OGNI 10000 CICLI
            if (enemies.size() < maxNumberOfEnemy) {
                if (numberOfCycles >= spawnEnemy) {
                    if (static_cast<int>(generateCasualNumber()) % 2 == 0) {
                        enemies.push_back(factoryE.createEnemy(EnemyType::Kamikaze,generateCasualX(),
                                                               generateCasualY(), ((generateCasualNumber() / 100) +
                                                                                   (maxNumberOfEnemy / 100)),
                                                               static_cast<int>(generateCasualNumber()) %
                                                               static_cast<int>(maxNumberOfEnemy) + 1));
                    } else
                        enemies.push_back(factoryE.createEnemy(EnemyType::Common, generateCasualX(),
                                                               generateCasualY(),
                                                               ((generateCasualNumber() / 50) +
                                                                (maxNumberOfEnemy / 100)),
                                                               static_cast<int>(generateCasualNumber()) %
                                                               static_cast<int>(maxNumberOfEnemy) + 1));
                    numberOfCycles = 0;
                    player.subscribe(enemies.back());
                }
            }
            numberOfCycles++;

            //***************** MOVIMENTO GAMECHARACTER E CONSEGUENTE MOVIMENTO DEI NEMICI

            GameEvent gameEvent = getEvent(fireCount, player.getWeapon()->getWeaponCadence());
            updateGame(gameEvent, player, verse, BulletCommon, BulletBazooka,
                       bullets,playerSpeed,map,lastMove);//mossa giocatore
            player.sprite.setPosition(sf::Vector2f(player.getX(), player.getY()));
            auto it=map.tiles.begin();
            Tile*  tile;
            tile=*it;
            while (player.getX()+20 < tile->xVertexTopSx || (player.getX()+20) > tile->xVertexTopSx + 64 ||
                   (player.getY()+30) < tile->yVertexTopSx || (player.getY()+30) > tile->yVertexTopSx + 64){
                tile = *it;
                it++;
            }
            player.receiveDamage(tile->getDamage());
            for (auto enemy:enemies) {
                enemyControl(player, enemy, enemyHasWeapon, map);
                if (enemyHasWeapon && enemy->cadenceOfBullet >= cadenceEnemyBullet) {
                        enemyBulletVerse = enemy->getX() < player.getX();
                        bullets.push_back(
                                generateBullet(*enemy, enemy->getEnemyDamage(), enemyBulletVerse,
                                                      BulletCommon, enemyBulletRange));
                        enemy->cadenceOfBullet = 0;
                }
                enemy->cadenceOfBullet++;
            }
            //************** MOVIMENTO PROIETTILI
            for (auto bullet:bullets) {
                bulletMovement(player, bullet, enemies, map.tiles);
            }
            //**************** CREAZIONE ARMI E POWERUP
            if (countWeaponPowerUp>=maxNumberOfEnemy) {
                casualNumber = static_cast<int>(generateCasualNumber());
                if (casualNumber % 5 == 0)
                    weapons.push_back(
                            factoryW.createWeapon(WeaponType::Bazooka, generateCasualX(), generateCasualY(), static_cast<int>(generateCasualNumber()) %
                                                                  static_cast<int>(maxNumberOfEnemy) + 1));
                if (casualNumber % 5 == 1)
                    weapons.push_back(
                            factoryW.createWeapon(WeaponType::MachineGun, generateCasualX(), generateCasualY(), static_cast<int>(generateCasualNumber()) %
                                                                     static_cast<int>(maxNumberOfEnemy) + 1));
                if (casualNumber % 5 == 2)
                    weapons.push_back(
                            factoryW.createWeapon(WeaponType::LaserGun, generateCasualX(), generateCasualY(), static_cast<int>(generateCasualNumber()) %
                                                                   static_cast<int>(maxNumberOfEnemy) + 1));
                if (casualNumber % 5 == 3)
                    powerUps.push_back(createPowerUp(PowerUpType::Life));
                if (casualNumber % 5 == 4)
                    powerUps.push_back(createPowerUp(PowerUpType::Energy));
                if(casualNumber%5==4 || casualNumber%5==3)
                    player.subscribe(powerUps.back());
                else
                    player.subscribe(weapons.back());
                countWeaponPowerUp=0;
                maxNumberOfEnemy++;
            }
            //************CONTROLLO E ELIMINAZIONE POWERUP
            for (auto powerUp:powerUps) {
                powerUpControl(*powerUp, player);
            }
            if (!powerUps.empty()) {
                PowerUp *powerUp;
                auto itPU = powerUps.begin();
                while (itPU != powerUps.end() ) {
                    powerUp = *itPU;
                    itPU++;
                    if (powerUp->used) {
                        player.unsubscribe(powerUp);
                        powerUps.remove(powerUp);
                    }
                }
            }
            // ************CONTROLLO E ELIMINAZIONE ARMI
            Weapon* weaponToRemove;
            for (auto weapon:weapons) {
                if(weaponControl(*weapon, player))
                   weaponToRemove=weapon;
            }
            weapons.remove(weaponToRemove);
            if (player.getWeapon()->getWeaponBullet() == 0) {
                player.unsubscribe(player.getWeapon());
                weapons.remove(player.getWeapon());
                player.equipWeapon(&baseGun);
            }
            //**************  CANCELLA NEMICI
            if (!enemies.empty()) {
                Enemy *enemy;
                auto itEnemy = enemies.begin();
                while (itEnemy != enemies.end()) {
                    enemy = *itEnemy;
                    itEnemy++;
                    if (enemy->getHP() <= 0) {
                        explosion.setPosition(sf::Vector2f(enemy->getX() - 400, enemy->getY() - 300));
                        player.setScore(50*(1+enemy->getHP()%100));
                        player.unsubscribe(enemy);
                        enemies.remove(enemy);
                        drawExplosion = true;
                        countWeaponPowerUp++;
                        player.setEnemyDefeated();
                        if(player.getEnemyDefeated()==20) {
                            player.notify("EnemyGoal1");
                        }
                        if(player.getEnemyDefeated()==50) {
                            player.notify("EnemyGoal2");
                        }
                        if(player.getEnemyDefeated()==200) {
                            player.notify("EnemyGoal3");
                        }
                    }
                }
            }

            //************* ELIMINAZIONE PROIETTILI
            if (!bullets.empty()) {
                bullet * bullet;
                auto itBullet = bullets.begin();
                while (itBullet != bullets.end()) {
                    bullet = *itBullet;
                    itBullet++;
                    if (bullet->bulletLife == bullet->range) {
                        bullets.remove(bullet);
                    }
                }
            }
            //**************FIXME POSIZIONE SCRITTE
            hpPlayer = std::to_string(player.getHP());
            EPlayer = std::to_string(player.getEnergy());
            PPlayer = std::to_string(player.getWeapon()->getWeaponPower());
            BPlayer = std::to_string(player.getWeapon()->getWeaponBullet());
            Goal.setString(player.getGoal());
            Hp.setString("HP:" + hpPlayer + "  Energy:" + EPlayer + "  Power:" + PPlayer + "  Bullet:" + BPlayer);
            Hp.setPosition(player.getX() + 180, 50);
            Goal.setPosition(player.getX() -100 , 200);
            //************* DISEGNA SPRITE E MAPPA
            window.clear();
            if (player.getX() >= player.getXMin() + 512 || player.getX() <= player.getXMax() - 512)
                window.setView(view0);
            if (player.getX() < player.getXMin() + 512)
                window.setView(view2);
            if (player.getX() > player.getXMax() - 512)
                window.setView(view1);
            window.draw(map);
            window.draw(player.sprite);
            window.draw(Hp);
            if(Goal.getString()!=" ") {
                if(durateGoal>700) {
                    durateGoal = 0;
                    player.setGoal();
                }
                window.draw(Goal);
                durateGoal++;
            }
            for (auto enemy:enemies)
                window.draw(enemy->sprite);
            for (auto bullet:bullets)
                window.draw(bullet->sprite);
            for (auto weapon:weapons) {
                if (!weapon->equip)
                    window.draw(weapon->sprite);
            }
            for (auto powerUp:powerUps)
                window.draw(powerUp->sprite);
            if (drawExplosion) {
                lifeOfExplosion++;
                window.draw(explosion);
                if (lifeOfExplosion >= 500) {
                    drawExplosion = false;
                    lifeOfExplosion = 0;
                }
            }
        }
        window.display();
        window.clear();
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space) {
                    window.setView(view2);
                    stato = '1';
                }
            }
            if (player.getHP()<=0) {
                playerScore = std::to_string(player.getScore());
                actualScore=player.getScore();
                player.reset(spaceshipEnergy,spaceshipHP,playerX,playerY);
                player.equipWeapon(&baseGun);
                maxNumberOfEnemy=1;
                weapons.clear();
                enemies.clear();
                window.setView(view2);
                stato = '2';
            }
        }
    }
}