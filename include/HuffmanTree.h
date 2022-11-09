#ifndef HW_02_HUFFMAN_HUFFMANTREE_H
#define HW_02_HUFFMAN_HUFFMANTREE_H

#include "HuffmanNode.h"
#include <vector>

namespace MyHuffmanArchiver {
    class HuffmanTree {
    public:
        explicit HuffmanTree(HuffmanNode *root) : root(root) {}
        explicit HuffmanTree(std::vector<unsigned char> &bytes);
        explicit HuffmanTree(std::vector<std::vector<bool>> &table);

        HuffmanTree(const HuffmanTree &other) = delete;
        HuffmanTree(HuffmanTree &&other) = delete;

        HuffmanTree &operator =(const HuffmanTree &other) = delete;
        HuffmanTree &operator =(HuffmanTree &&other) = delete;

        void recursiveDestructor(HuffmanNode *node);
        ~HuffmanTree();

        std::vector<std::vector<bool>> getTable() const;
        static HuffmanNode *goDown(HuffmanNode *node, bool dir);

        HuffmanNode *root;
    private:
        void fillTable(HuffmanNode *node, std::vector<bool> &way,
           std::vector<std::vector<bool>> &table) const;
    };
}

#endif //HW_02_HUFFMAN_HUFFMANTREE_H
