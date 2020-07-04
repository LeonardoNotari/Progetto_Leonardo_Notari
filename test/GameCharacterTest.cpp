//
// Created by leonardo on 01/07/20.
//
#include <gtest/gtest.h>
#include "../GameCharacter.h"
#include "../Weapon.h"

TEST(GameCharacter, IsPossibleEquipWeapon){
    GameCharacter player(5,10);
    ASSERT_TRUE( player.IsPossibleEquipWeapon(5));
}
TEST(GameCharacter, EquipWeapon){
    GameCharacter player(8,10);
    Weapon gun(10,5,0,0);
    player.EquipWeapon(6,&gun);
    ASSERT_EQ(10, player.weapon->power);
}


