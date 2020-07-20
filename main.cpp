
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


GameEvent getEvent(int &a) {
    int fireCadence = a;

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
        if (fireCadence == 200) {
            a = 0;
            return GameEvent::fire;
        } else {
            a++;
            return GameEvent::noop;
        }
    }
    return GameEvent::noop;
}

float generateCasualNumber() {
    srand(time(nullptr));
    return rand() % 800;
}


void updateGame(const GameEvent &gameEvent, GameCharacter &player, Weapon *gun, BulletFactory factory, bool &verse,
                const sf::Texture &bulletTexture, std::list<sf::Sprite> &sprites, std::list<bullet *> &bullets) {
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
            bullets.push_back(factory.createBullet(BulletType::Common, verse, bulletTexture, player.getGameCharacterX(),
                                                   player.getGameCharacterY(), sprites));
            break;
        }
        case GameEvent::noop: {
            break;
        }
    }
}


void enemyControl(GameCharacter &player, std::list<Weapon *> &weapons,
                  Enemy *enemy, sf::Sprite &sprite) {//controllo delle posizioni
    float gameCharacterX, gameCharacterY;
    gameCharacterX = player.getGameCharacterX();
    gameCharacterY = player.getGameCharacterY();
    enemy->move(gameCharacterX, gameCharacterY);//movimento del nemico
    sprite.setPosition(sf::Vector2f(enemy->getEnemyX(), enemy->getEnemyY()));

}


void
bulletMovement(GameCharacter &player, bullet *bullet, sf::Sprite &sprite, bool &lifeOver, std::list<Enemy *> &enemies) {
    if (bullet->bulletVerse)
        bullet->move(1);
    else
        bullet->move(-1);
    sprite.setPosition(sf::Vector2f(bullet->bulletX, bullet->bulletY));
    /*if (player.getGameCharacterY() == bullet->bulletX && player.getGameCharacterX() == bullet->bulletY)
        player.receiveDamage(bullet->damage);
    auto it=enemies.begin();
    for (auto enemy:enemies) {
        if (enemy->getEnemyY() >= bullet->bulletY-0.05 && enemy->getEnemyY() <= bullet->bulletY+0.5 && enemy->getEnemyX() >= bullet->bulletX-0.5 && enemy->getEnemyX() <= bullet->bulletX+0.05 ) {
            // enemy->receiveDamage(bullet->damage);
            *it=enemy;
        }
    }
    enemies.erase(it);
     */
    if (bullet->bulletLife == 500)
        lifeOver = true;
}

int main() {
    int spaceshipEnergy = 0, spaceshipHP = 10;
    int basicWeaponPower = 0;
    bool verse = true;
    bool bulletLifeOver;
    int fireCadence = 0;

    // create the window
    sf::RenderWindow window(sf::VideoMode(1024, 512), "Volcano Battle");
    // create background
    // define the level with an array of tile indices
    const int level[] =
            {

                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    3, 3, 3, 3, 3, 8, 3, 3, 3, 8, 3, 3, 3, 3, 3, 3, 3, 8, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 8,

            };

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("image/tiles.png", sf::Vector2u(32, 32), level, 32, 3))
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
    GameCharacter player(spaceshipEnergy, spaceshipHP);//istanza personaggio
    Weapon baseGun(basicWeaponPower);//istanza arma di base
    player.equipWeapon(1, &baseGun);
    sf::Texture charter1;
    if (!charter1.loadFromFile("image/starshipdark.png"))
        return -1;
    sf::Sprite ch1;
    ch1.setTexture(charter1);
    ch1.setPosition(sf::Vector2f(player.getGameCharacterX(), player.getGameCharacterY()));
    //************* end charter1

    //************* sprite Weapon
    sf::Texture weaponSprite;
    weaponSprite.loadFromFile("image/alien2.png");
    std::list<sf::Sprite> weaponSprites;
    std::list<Weapon *> weapons;

    //************ sprite enemy
    sf::Texture enemyTexture;
    sf::Texture enemyTexture1;
    enemyTexture.loadFromFile("image/alien2.png");
    enemyTexture1.loadFromFile("image/Ship10.png");
    std::list<sf::Sprite> enemySprites;
    std::list<Enemy *> enemies;

    //************** sprite proiettili
    sf::Texture Bullet1;
    Bullet1.loadFromFile("image/projectile.png");
    std::list<sf::Sprite> bulletSprites;
    std::list<bullet *> bullets;

    int i = 0;
    EnemyFactory factoryE;
    BulletFactory factoryB;

    //************* GameLoop
    while (window.isOpen()) {
        bulletLifeOver = false;
        if (i == 10000) {
            if (static_cast<int>(generateCasualNumber()) % 2 == 0) {
                enemies.push_back(factoryE.createEnemy(EnemyType::Kamikaze, enemyTexture, generateCasualNumber(),
                                                       generateCasualNumber(), generateCasualNumber() / 10000,
                                                       enemySprites));
                i = 0;
            } else {
                i = 0;
                enemies.push_back(factoryE.createEnemy(EnemyType::Common, enemyTexture1, generateCasualNumber(),
                                                       generateCasualNumber(), generateCasualNumber() / 10000,
                                                       enemySprites));
            }
        }
        i++;
        GameEvent gameEvent = getEvent(fireCadence);
        updateGame(gameEvent, player, player.getWeapon(), factoryB, verse, Bullet1, bulletSprites,
                   bullets);//mossa giocatore
        ch1.setPosition(sf::Vector2f(player.getGameCharacterX(), player.getGameCharacterY()));
        if (!enemies.empty()) {
            for (auto enemy:enemies) {
                auto it = enemySprites.begin();
                it = std::next(it, enemy->spriteCode - 1);
                enemyControl(player, weapons, enemy, *it);//sprite alla posizione spritecode
            }
        }

        if (!bullets.empty()) {
            for (auto bullet:bullets) {
                bulletLifeOver = false;
                auto it = bulletSprites.begin();
                it = std::next(it, bullet->spriteCode - 1);
                bulletMovement(player, bullet, *it, bulletLifeOver, enemies);
            }
        }
        if (!bullets.empty()) {
            if (bulletLifeOver) {
                bullets.clear();
                bulletSprites.clear();
            }
        }

        window.clear(sf::Color(83, 87, 79));
        window.draw(sf);
        window.draw(map);
        if (!enemySprites.empty()) {
            for (auto &sprite:enemySprites)
                window.draw(sprite);
        }
        if (!bulletSprites.empty()) {
            for (auto &sprite:bulletSprites)
                window.draw(sprite);
        }
        window.draw(ch1);
        window.display();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}