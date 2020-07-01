add_subdirectory(./lib/googletest-master)
set(gtest_SOURCE_DIR, ./lib/googletest-master/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES RunAllTest.cpp  GameCharacterTest.cpp GameCharacterFixture.cpp)
add_executable(runGameCharacterTest ${TEST_SOURCE_FILES} RunAllTest.cpp  GameCharacterTest.cpp GameCharacterFixture.cpp)
target_link_libraries(runGameCharacterTest gtest gtest_main core)