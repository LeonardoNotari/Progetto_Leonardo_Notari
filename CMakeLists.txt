cmake_minimum_required(VERSION 3.15)
project(Progetto_Leonardo_Notari)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(test)
set(SOURCE_FILE GameCharacter.cpp GameCharacter.h Weapon.cpp Weapon.h)

add_executable(Progetto_Leonardo_Notari main.cpp GameCharacter.cpp GameCharacter.h Weapon.cpp Weapon.h)
add_library(core  ${SOURCE_FILE})
target_link_libraries(Progetto_Leonardo_Notari core)