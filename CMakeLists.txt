cmake_minimum_required(VERSION 3.16)
project(Progetto_Leonardo_Notari_)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(test)
set(SFML_INCLUDE_DIR "/home/SFML/SFML-2.5.1/include/SFML")
set(SFML_LIBRARY_DIR "/home/SFML/SFML-2.5.1/lib")
set(SFML_DIR "/home/SFML/SFML-2.5.1/lib/cmake/SFML")
set(CMAKE_VERBOSE_MAKEFILE ON)
link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)
if (SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARY_DIR}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")


endif ()


set(SOURCE_FILE main.cpp TileMap.h GameCharacter.h GameCharacter.cpp Weapon.h Weapon.cpp Enemy.cpp Enemy.h KamikazeEnemy.cpp KamikazeEnemy.h CommonEnemy.cpp CommonEnemy.h bullet.cpp bullet.h EnemyFactory.cpp EnemyFactory.h BulletFactory.cpp BulletFactory.h WeaponFactory.cpp WeaponFactory.h Character.cpp Character.h PowerUp.cpp PowerUp.h TileMap.cpp Resource.cpp Resource.h Tile.cpp Tile.h TileFactory.cpp TileFactory.h Observer.cpp Observer.h Subject.cpp Subject.h)

add_executable(Progetto_Leonardo_Notari_ main.cpp TileMap.h GameCharacter.cpp GameCharacter.h Weapon.cpp Weapon.h Enemy.cpp Enemy.h)
add_library(core ${SOURCE_FILE})
target_link_libraries(Progetto_Leonardo_Notari_ core sfml-graphics sfml-window sfml-system)



