#include "HuffmanArchiver.h"
#include "MyException.h"
#include <fstream>
#include <iterator>
#include <vector>
#include <climits>

namespace MyHuffmanArchiver {
    HuffmanArchiver::~HuffmanArchiver() {
        delete _tree;
    }

    void HuffmanArchiver::readBytes(std::ifstream &file) {
        try {
            file.read(_buffer, BUFSIZE);
        } catch (std::ifstream::failure &exception) {
            throw MyException("Error while reading the file");
        }

        while (file.gcount()) {
            for (int byte = 0; byte < file.gcount(); byte++) {
                _bytes.push_back(_buffer[byte]);
            }

            file.read(_buffer, BUFSIZE);
        }
    }

    void HuffmanArchiver::writeBytes(std::ofstream &file) {
        // fill to whole byte
        while (_last != CHAR_BIT) {
            appendBit(0);
        }

        for (int leftBound = 0; leftBound < _transBytes.size(); leftBound += BUFSIZE) {
            int toWrite = 0;
            for (int i = leftBound; i < std::min(leftBound + BUFSIZE, (int) _transBytes.size()); i++) {
                _buffer[i - leftBound] = _transBytes[i];
                toWrite++;
            }

            try {
                file.write(_buffer, toWrite);
            } catch (std::ofstream::failure &exception) {
                throw MyException("Error while writing to the file");
            }
        }
    }

    void HuffmanArchiver::appendBit(bool bit) {
        if (_last == CHAR_BIT) {
            _transBytes.push_back(0);
            _last = 0;
        }

        _transBytes.back() = (_transBytes.back() << 1) + bit;
        _last++;
    }

    void HuffmanArchiver::appendByte(unsigned char byte) {
        for (int i = CHAR_BIT - 1; i >= 0; i--) {
            appendBit((byte >> i) & 1);
        }
    }

    bool HuffmanArchiver::getBit(int &pointer) {
        if (pointer >= _bytes.size()) {
            throw MyException("Error: file has a wrong format");
        }

        bool result = (_bytes[pointer] >> _last) & 1;
        _last--;
        if (_last == -1) {
            _last += CHAR_BIT;
            pointer++;
        }

        return result;
    }

    unsigned char HuffmanArchiver::getByte(int &pointer) {
        unsigned char result = 0;
        for (int bit = 0; bit < CHAR_BIT; bit++) {
            result = (result << 1) + getBit(pointer);
        }

        return result;
    }

    unsigned int HuffmanArchiver::getInt(int &pointer) {
        unsigned int result = 0;
        for (int bit = 0; bit < sizeof(int) * CHAR_BIT; bit++) {
            result = (result << 1) + getBit(pointer);
        }

        return result;
    }

    void HuffmanArchiver::encodeBuild(std::ifstream &file) {
        readBytes(file);

        dataSize = _bytes.size();

        _tree = new HuffmanTree(_bytes);
        _table = _tree->getTable();
        _transBytes = {};

        // length 1B code --- 256 * 1B + codeLength
        // fileSize in bits 4B 2**32 / (8 * 1024 * 1024) = 2**9 = 512 mb max
        // file ---

        //table
        _last = CHAR_BIT;
        for (int byte = 0; byte <= UCHAR_MAX; byte++) {
            appendByte(_table[byte].size());
            for (auto bit: _table[byte]) {
                appendBit(bit);
            }
        }

        unsigned int fileSize = 0;
        for (auto &byte: _bytes) {
            fileSize += _table[byte].size();
        }

        for (int bitInt = sizeof(int) * CHAR_BIT - 1; bitInt >= 0; bitInt--) {
            appendBit((fileSize >> bitInt) & 1);
        }

        additionalSize = _transBytes.size(); // ceil

        //bytes
        for (auto &byte: _bytes) {
            for (auto bit: _table[byte]) {
                appendBit(bit);
            }
        }

        compressedSize = (int) _transBytes.size() - additionalSize;
    }

    void HuffmanArchiver::decodeBuild(std::ifstream &file) {
        readBytes(file);
        // length 1B code --- 256 * 1B + codeLength
        // fileSize in bits 4B 2**32 / (8 * 1024 * 1024) = 2**9 = 512 mb max
        // file ---

        _last = CHAR_BIT - 1;
        int pointer = 0;
        _table.resize(UCHAR_MAX + 1);
        //fetch table

        for (int byte = 0; byte <= UCHAR_MAX; byte++) {
            unsigned char length = getByte(pointer);
            for (int it = 0; it < length; it++) {
                _table[byte].push_back(getBit(pointer));
            }
        }

        //fetch size
        unsigned int fileSize = getInt(pointer);
        additionalSize = pointer + (_last != CHAR_BIT - 1); // ceil
        compressedSize = (int) _bytes.size() - additionalSize; // floor

        _tree = new HuffmanTree(_table);
        HuffmanNode *node = _tree->root;
        for (int bitNum = 0; bitNum < fileSize; bitNum++) {
            bool bit = getBit(pointer);
            node = HuffmanTree::goDown(node, bit);
            if (node == nullptr) {
                throw MyException("Error: file has a wrong format");
            }

            if (HuffmanNode::isLeaf(node)) {
                _transBytes.push_back(HuffmanNode::getSymb(node));
                node = _tree->root;
            }
        }

        dataSize = _transBytes.size();
    }

    void HuffmanArchiver::encodeWrite(std::ofstream &file) {
        writeBytes(file);
    }

    void HuffmanArchiver::decodeWrite(std::ofstream &file) {
        _last = CHAR_BIT; // no shift, whole bytes
        writeBytes(file);
    }
}