//
// Created by leonardo on 01/07/20.
//
#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include "../GameCharacter.h"
#include "../Weapon.h"
#include "../KamikazeEnemy.h"


TEST(GameCharacter, EquipWeapon) {
    sf::Texture playerTexture;
    sf::Sprite spriteTest;
    spriteTest.setTexture(playerTexture);
    GameCharacter player(100, 0, 0, 0, spriteTest);
    Weapon gun(9, 0, 0, 0, spriteTest, 0, 0, 0);
    player.equipWeapon(gun.getWeaponCost(), &gun);
    ASSERT_EQ(player.getWeapon()->getWeaponPower(), 9);
}

TEST(GameCharacter, Move) {
    sf::Texture playerTexture;
    sf::Sprite spriteTest;
    spriteTest.setTexture(playerTexture);
    GameCharacter player(8, 0, 0, 0, spriteTest);
    player.move(0, 1);
    player.move(1, 0);
    player.move(1, 0);
    player.move(1, 0);
    player.move(1, 0);
    ASSERT_EQ(4, player.getX());
    ASSERT_EQ(1, player.getY());
}

TEST(GameCharacter, ReceivedDamage) {
    sf::Texture playerTexture;
    sf::Sprite spriteTest;
    bool a = false;
    spriteTest.setTexture(playerTexture);
    GameCharacter player(200, 2, 2, 10, spriteTest);
    KamikazeEnemy alien(1, 0, 0, 100, 9, spriteTest);
    alien.attack(player, a);
    ASSERT_EQ(100, player.getHP());
}

