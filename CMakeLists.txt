cmake_minimum_required(VERSION 3.15)
project(Progetto_Leonardo_Notari)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(test)
set(SOURCE_FILE main.cpp GameCharacter.h GameCharacter.cpp Weapon.h Weapon.cpp Enemy.cpp Enemy.h KamikazeEnemy.cpp KamikazeEnemy.h)

find_package(wxWidgets REQUIRED net gl core base)
include(${wxWidgets_USE_FILE})

add_executable(Progetto_Leonardo_Notari main.cpp GameCharacter.cpp GameCharacter.h Weapon.cpp Weapon.h Enemy.cpp Enemy.h)
add_library(core ${SOURCE_FILE})
target_link_libraries(Progetto_Leonardo_Notari core)


target_link_libraries(Progetto_Leonardo_Notari ${wxWidgets_LIBRARIES})
