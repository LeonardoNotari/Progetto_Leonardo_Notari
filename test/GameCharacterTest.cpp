//
// Created by leonardo on 01/07/20.
//
#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include "../GameCharacter.h"
#include "../Weapon.h"
#include "../KamikazeEnemy.h"
#include "../CommonEnemy.h"
#include "../TileMap.h"


TEST(GameCharacter, EquipWeapon) {
    TileMap map;
    sf::Sprite spriteTest;
    GameCharacter player(100, 0, 0, 0, spriteTest);
    Weapon gun(0, 0, 0, 0, spriteTest, 0, 0, 0, WeaponType::LaserGun);
    player.equipWeapon(&gun);
    ASSERT_EQ(player.getWeapon()->getWeaponPower(), 0);
}

TEST(GameCharacter, Move) {
    TileMap map;
    sf::Sprite spriteTest;
    GameCharacter player(8, 0, 0, 0, spriteTest);
    player.move(0, 1, map);
    player.move(1, 0, map);
    player.move(1, 0, map);
    player.move(1, 0, map);
    player.move(1, 0, map);
    ASSERT_EQ(4, player.getX());
    ASSERT_EQ(1, player.getY());
}

TEST(GameCharacter, ReceivedDamage) {
    sf::Sprite spriteTest;
    bool a = false;
    GameCharacter player(200, 2, 2, 10, spriteTest);
    KamikazeEnemy alien(1, 0, 0, 100, 9, spriteTest);
    alien.attack(player, a);
    ASSERT_EQ(100, player.getHP());
}

TEST(GameCharacter, EnemyCollision) {
    TileMap map;
    Tile *tile;
    int i = 0, j = 0;
    sf::Sprite spriteTest;
    int a;
    int matrix[6][8] = {
            1, 0, 0, 1, 0, 0, 0, 1,
            2, 12, 12, 3, 12, 12, 12, 2,
            2, 12, 12, 12, 12, 12, 12, 2,
            2, 12, 12, 12, 12, 10, 12, 2,
            2, 12, 12, 12, 12, 2, 12, 2,
            8, 9, 9, 9, 9, 8, 9, 8
    };
    while (j < 6) {
        a = matrix[j][i];
        if (a == 12)
            tile = new Tile(true, false, 0, std::move(std::to_string(a)), i * 64, j * 64);
        if (a == 1 || a == 2 || a == 8 || a == 9)
            tile = new Tile(false, false, 0, std::move(std::to_string(a)), i * 64, j * 64);
        if (a == 3 || a == 10)
            tile = new Tile(false, true, 10, std::move(std::to_string(a)), i * 64, j * 64);
        map.tiles.push_back(tile);
        i++;
        if (i == 8) {
            i = 0;
            j++;
        }
    }
    GameCharacter player(100, 170, 200, 10, spriteTest);
    CommonEnemy alien(1, 120, 150, 100, 5, spriteTest);
    for (i = 0; i < 6; i++) {
        player.move(-10, 0, map);
        alien.move(player.getX(), player.getY(), map);
        if (player.getX() > alien.getX() - 30 && player.getX() < alien.getX() + 30 &&
            player.getY() > alien.getY() - 40 && player.getY() < alien.getY() + 40) {
            player.receiveDamage(5);
            alien.move(player.getX(), alien.getY(), map);
            if (player.getX() > alien.getX())
                player.move(3, 0, map);
            if (player.getX() < alien.getX())
                player.move(-3, 0, map);
        }
    }
    ASSERT_EQ(player.getX(), 116);
    ASSERT_EQ(alien.getX(), 80);
    ASSERT_EQ(alien.getY(), 180);
    ASSERT_EQ(player.getHP(), 90);
}


TEST(GameCharacter, TileCollision) {
    TileMap map;
    int i = 0, j = 0;
    Tile *tile;
    sf::Sprite spriteTest;
    int a;
    int matrix[6][8] = {
            1, 0, 0, 1, 0, 0, 0, 1,
            2, 12, 12, 3, 12, 12, 12, 2,
            2, 12, 12, 12, 12, 12, 12, 2,
            2, 12, 12, 12, 12, 10, 12, 2,
            2, 12, 12, 12, 12, 2, 12, 2,
            8, 9, 9, 9, 9, 8, 9, 8
    };
    while (j < 6) {
        a = matrix[j][i];
        if (a == 12)
            tile = new Tile(true, false, 0, std::move(std::to_string(a)), i * 64, j * 64);
        if (a == 1 || a == 2 || a == 8 || a == 9)
            tile = new Tile(false, false, 0, std::move(std::to_string(a)), i * 64, j * 64);
        if (a == 3 || a == 10)
            tile = new Tile(false, true, 10, std::move(std::to_string(a)), i * 64, j * 64);
        map.tiles.push_back(tile);
        i++;
        if (i == 8) {
            i = 0;
            j++;
        }
    }
    GameCharacter player(200, 400, 150, 10, spriteTest);
    player.move(7, 0, map);
    player.move(7, 0, map);
    player.move(7, 0, map);
    player.move(7, 0, map);
    player.move(7, 0, map);
    player.move(7, 0, map);
    player.move(7, 0, map);
    player.move(7, 0, map);
    ASSERT_EQ(player.getX(), 442);
    auto it = map.tiles.begin();
    tile = *it;
    while (player.getX() + 10 < tile->xVertexTopSx || player.getX() + 10 > tile->xVertexTopSx + 64 ||
           player.getY() < tile->yVertexTopSx || player.getY() > tile->yVertexTopSx + 64) {
        tile = *it;
        it++;
    }
    ASSERT_EQ(tile->getIsCrossable(), false);
    ASSERT_EQ(tile->code, "2");
    player.move(0, 15, map);
    player.move(0, 15, map);
    player.move(0, 15, map);
    player.move(0, 15, map);
    player.move(0, 15, map);
    player.move(0, 15, map);
    player.move(0, 15, map);
    player.move(0, 15, map);
    player.move(0, 15, map);
    player.move(0, 15, map);
    player.move(0, 15, map);
    player.move(0, 15, map);
    ASSERT_EQ(player.getY(), 315);
    it = map.tiles.begin();
    tile = *it;
    while (player.getX() < tile->xVertexTopSx || player.getX() > tile->xVertexTopSx + 64 ||
           player.getY() + 10 < tile->yVertexTopSx || player.getY() + 10 > tile->yVertexTopSx + 64) {
        tile = *it;
        it++;
    }
    ASSERT_EQ(tile->getIsCrossable(), false);
    ASSERT_EQ(tile->code, "9");
    player.move(0, -15, map);
    player.move(0, -15, map);
    player.move(0, -15, map);
    player.move(0, -15, map);
    player.move(0, -15, map);
    player.move(-10, 0, map);
    player.move(-10, 0, map);
    player.move(-10, 0, map);
    player.move(-10, 0, map);
    player.move(-10, 0, map);
    player.move(-10, 0, map);
    player.move(-10, 0, map);
    player.move(-10, 0, map);
    player.move(-10, 0, map);
    ASSERT_EQ(player.getY(), 240);
    ASSERT_EQ(player.getX(), 392);
    ASSERT_EQ(player.getHP(), 160);
    it = map.tiles.begin();
    tile = *it;
    while (player.getX() - 10 < tile->xVertexTopSx || player.getX() - 10 > tile->xVertexTopSx + 64 ||
           player.getY() < tile->yVertexTopSx || player.getY() > tile->yVertexTopSx + 64) {
        tile = *it;
        it++;
    }
    ASSERT_EQ(tile->getIsCrossable(), false);
    ASSERT_EQ(tile->getIsDestructible(), true);
    ASSERT_EQ(tile->code, "10");
}