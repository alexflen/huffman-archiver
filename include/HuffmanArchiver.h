#ifndef HW_02_HUFFMAN_HUFFMANARCHIVER_H
#define HW_02_HUFFMAN_HUFFMANARCHIVER_H

#include "HuffmanTree.h"
#include <iostream>
#include <climits>

namespace MyHuffmanArchiver {
    class HuffmanArchiver {
    public:
        HuffmanArchiver() = default;
        ~HuffmanArchiver();

        HuffmanArchiver(const HuffmanArchiver &other) = delete;
        HuffmanArchiver(HuffmanArchiver &&other) = delete;

        HuffmanArchiver &operator =(const HuffmanArchiver &other) = delete;
        HuffmanArchiver &operator =(HuffmanArchiver &&other) = delete;

        void encodeBuild(std::ifstream &file);
        void decodeBuild(std::ifstream &file);
        void encodeWrite(std::ofstream &file);
        void decodeWrite(std::ofstream &file);

        int additionalSize = 0;
        int dataSize = 0;
        int compressedSize = 0;
    private:
        HuffmanTree *_tree = nullptr;
        std::vector<std::vector<bool>> _table;
        std::vector<unsigned char> _bytes;
        std::vector<unsigned char> _transBytes;

        static const int BUFSIZE = 4096;
        char _buffer[BUFSIZE];
        int _last = CHAR_BIT;

        void readBytes(std::ifstream &file);
        void writeBytes(std::ofstream &file);

        void appendBit(bool bit);
        void appendByte(unsigned char byte);
        bool getBit(int &pointer);
        unsigned char getByte(int &pointer);
        unsigned int getInt(int &pointer);
    };
}

#endif //HW_02_HUFFMAN_HUFFMANARCHIVER_H
