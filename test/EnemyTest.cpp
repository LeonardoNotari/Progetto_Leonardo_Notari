//
// Created by leonardo on 09/07/20.
//

#include <gtest/gtest.h>
#include "../GameCharacter.h"
#include "../KamikazeEnemy.h"
#include "../CommonEnemy.h"

TEST(Enemy, Move) {
    TileMap map;
    sf::Texture playerTexture;
    sf::Sprite spriteTest;
    spriteTest.setTexture(playerTexture);
    GameCharacter player(0, 0, 0, 0, spriteTest);
    KamikazeEnemy alien(0, 5, 5, 0, 0.5, spriteTest);
    CommonEnemy alien1(0, 5, 5, 0, 0.5, spriteTest);
    alien.move(player.getX(), player.getY(), map);
    alien.move(player.getX(), player.getY(), map);
    alien.move(player.getX(), player.getY(), map);
    alien1.move(player.getX(), player.getY(), map);
    alien1.move(player.getX(), player.getY(), map);
    alien1.move(player.getX(), player.getY(), map);
    ASSERT_EQ(alien.getX(), 3.5);
    ASSERT_EQ(alien.getY(), 3.5);
    ASSERT_EQ(alien1.getX(), 6.5);
    ASSERT_EQ(alien1.getY(), 3.5);
    player.move(200, 200, map);
    alien.move(player.getX(), player.getY(), map);
    alien.move(player.getX(), player.getY(), map);
    alien.move(player.getX(), player.getY(), map);
    alien1.move(player.getX(), player.getY(), map);
    alien1.move(player.getX(), player.getY(), map);
    alien1.move(player.getX(), player.getY(), map);
    ASSERT_EQ(alien.getX(), 5);
    ASSERT_EQ(alien.getY(), 5);
    ASSERT_EQ(alien1.getX(), 5);
    ASSERT_EQ(alien1.getY(), 5);
}

TEST(KamikazeEnemy, Attack) {
    TileMap map;
    bool a = false;
    sf::Texture playerTexture;
    sf::Sprite spriteTest;
    spriteTest.setTexture(playerTexture);
    GameCharacter player(0, 0, 0, 0, spriteTest);
    KamikazeEnemy alien(10, 35, 35, 0, 1, spriteTest);
    alien.move(player.getX(), player.getY(), map);
    alien.move(player.getX(), player.getY(), map);
    alien.move(player.getX(), player.getY(), map);
    alien.move(player.getX(), player.getY(), map);
    alien.attack(player, a);
    ASSERT_EQ(alien.getHP(), 10);
    alien.move(player.getX(), player.getY(), map);
    alien.attack(player, a);
    ASSERT_EQ(alien.getHP(), 10);
    alien.move(player.getX(), player.getY(), map);
    alien.attack(player, a);
    ASSERT_EQ(alien.getHP(), 0);
}
