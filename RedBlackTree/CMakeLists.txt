cmake_minimum_required(VERSION 3.10)
project(RedBlackTreeTest)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_redblacktree test_redblacktree.cpp)
target_link_libraries(test_redblacktree GTest::GTest GTest::Main)

add_test(NAME RedBlackTreeTest COMMAND test_redblacktree)