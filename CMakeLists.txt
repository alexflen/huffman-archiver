cmake_minimum_required(VERSION 3.16.3)
project(hw-02_huffman)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(mutual STATIC src/HuffmanNode.cpp
        src/HuffmanTree.cpp
        include/HuffmanNode.h
        include/HuffmanTree.h src/MyException.cpp include/MyException.h src/HuffmanArchiver.cpp include/HuffmanArchiver.h)


add_executable(hw-02_huffman src/main.cpp)
target_link_libraries(hw-02_huffman mutual)

add_executable(testing
        test/test.cpp
        test/functions_test.cpp
        include/doctest.h
        include/functions_test.h
        test/lib-test.cpp)
target_link_libraries(testing mutual)