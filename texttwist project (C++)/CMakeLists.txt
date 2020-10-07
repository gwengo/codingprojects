cmake_minimum_required(VERSION 3.13)
project(project10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wextra -pedantic -pedantic-errors")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES Trie.h Trie.cpp TrieNode.cpp TrieNode.h TextTwist.cpp TextTwist.h TextTwistDriver.cpp)


add_executable(project10 ${SOURCE_FILES})