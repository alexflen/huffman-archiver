#include "doctest.h"
#include "functions_test.h"
#include <string>
#include <iostream>

TEST_CASE("One letter file") {
    std::string to_encode = "../test/one_letter_file.txt";
    std::string result = "../test/result.txt";
    std::string temp_file = "../test/temp_file.txt";
    TestFunctions::invokeArchiver(to_encode, result, temp_file);
    CHECK(TestFunctions::checkFiles(to_encode, result));
}

TEST_CASE("One character file") {
    std::string to_encode = "../test/one_character_file.txt";
    std::string result = "../test/result.txt";
    std::string temp_file = "../test/temp_file.txt";
    TestFunctions::invokeArchiver(to_encode, result, temp_file);
    CHECK(TestFunctions::checkFiles(to_encode, result));
}

TEST_CASE("Big file, all bytes") {
    std::string to_encode = "../test/big_file.txt";
    std::string result = "../test/result.txt";
    std::string temp_file = "../test/temp_file.txt";
    TestFunctions::invokeArchiver(to_encode, result, temp_file);
    CHECK(TestFunctions::checkFiles(to_encode, result));
}

TEST_CASE("Random 1kb") {
    std::string to_encode = "../test/random1kb.txt";
    std::string result = "../test/result.txt";
    std::string temp_file = "../test/temp_file.txt";
    TestFunctions::invokeArchiver(to_encode, result, temp_file);
    CHECK(TestFunctions::checkFiles(to_encode, result));
}

TEST_CASE("Random 10Bytes") {
    std::string to_encode = "../test/random10b.txt";
    std::string result = "../test/result.txt";
    std::string temp_file = "../test/temp_file.txt";
    TestFunctions::invokeArchiver(to_encode, result, temp_file);
    CHECK(TestFunctions::checkFiles(to_encode, result));
}