//
// Created by leonardo on 09/07/20.
//

#include <gtest/gtest.h>
#include "../GameCharacter.h"
#include "../KamikazeEnemy.h"
#include "../CommonEnemy.h"

TEST(Enemy, Move) {
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
    GameCharacter player(0, 200, 200, 0, spriteTest);
    KamikazeEnemy alien(0, 5, 5, 0, 0.5, spriteTest);
    CommonEnemy alien1(0, 205, 205, 0, 0.5, spriteTest);
    alien.move(player.getX(), player.getY(), map);
    alien.move(player.getX(), player.getY(), map);
    alien.move(player.getX(), player.getY(), map);
    alien1.move(player.getX(), player.getY(), map);
    alien1.move(player.getX(), player.getY(), map);
    alien1.move(player.getX(), player.getY(), map);
    ASSERT_EQ(alien.getX(), 3.5);
    ASSERT_EQ(alien.getY(), 6.5);
    ASSERT_EQ(alien1.getX(), 206.5);
    ASSERT_EQ(alien1.getY(), 203.5);
}

TEST(KamikazeEnemy, Attack) {
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
    bool flag = false;
    GameCharacter player(0, 100, 100, 0, spriteTest);
    KamikazeEnemy alien(10, 135, 135, 0, 1, spriteTest);
    alien.move(player.getX(), player.getY(), map);
    alien.move(player.getX(), player.getY(), map);
    alien.move(player.getX(), player.getY(), map);
    alien.move(player.getX(), player.getY(), map);
    alien.attack(player, flag);
    ASSERT_EQ(alien.getHP(), 10);
    alien.move(player.getX(), player.getY(), map);
    alien.attack(player, flag);
    ASSERT_EQ(alien.getHP(), 10);
    alien.move(player.getX(), player.getY(), map);
    alien.attack(player, flag);
    ASSERT_EQ(alien.getHP(), 0);
}
