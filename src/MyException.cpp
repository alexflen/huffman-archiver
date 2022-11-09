#include "MyException.h"
#include <iostream>

namespace MyHuffmanArchiver {
    void MyException::print() const {
        std::cout << _message << std::endl;
    }
}