#ifndef HW_02_HUFFMAN_MYEXCEPTION_H
#define HW_02_HUFFMAN_MYEXCEPTION_H

#include <string>
#include <utility>

namespace MyHuffmanArchiver {
    class MyException {
    public:
        MyException(std::string message) : _message(std::move(message)) {}
        void print() const;

    private:
        std::string _message;
    };
}

#endif //HW_02_HUFFMAN_MYEXCEPTION_H
