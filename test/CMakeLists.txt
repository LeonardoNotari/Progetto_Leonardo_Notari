add_subdirectory(./lib/googletest-master)


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


set(gtest_SOURCE_DIR, ./lib/googletest-master/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES RunAllTest.cpp GameCharacterTest.cpp EnemyTest.cpp)
add_executable(runGameCharacterTest ${TEST_SOURCE_FILES} RunAllTest.cpp GameCharacterTest.cpp)
target_link_libraries(runGameCharacterTest gtest gtest_main core sfml-graphics sfml-window sfml-system)