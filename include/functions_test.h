#ifndef HW_02_HUFFMAN_FUNCTIONS_TEST_H
#define HW_02_HUFFMAN_FUNCTIONS_TEST_H

#include <string>

namespace TestFunctions {
    void invokeArchiver(const std::string& to_archive, const std::string& result, const std::string& temp);
    bool checkFiles(const std::string& model_file, const std::string& file);
}

#endif //HW_02_HUFFMAN_FUNCTIONS_TEST_H
