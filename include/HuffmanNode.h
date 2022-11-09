#ifndef HW_02_HUFFMAN_HUFFMANNODE_H
#define HW_02_HUFFMAN_HUFFMANNODE_H

namespace MyHuffmanArchiver {
    class HuffmanNode {
    public:
        HuffmanNode(int priority, unsigned char symb) : _priority(priority), _symb(symb),
            _zerSon(nullptr), _oneSon(nullptr) {}

        HuffmanNode(HuffmanNode *zerSon, HuffmanNode *oneSon) : _zerSon(zerSon), _oneSon(oneSon),
            _priority(getPriority(zerSon) + getPriority(oneSon)),
            _symb(0) {}

        ~HuffmanNode() = default;

        static int getPriority(HuffmanNode *node);
        static unsigned char getSymb(HuffmanNode *node);
        static HuffmanNode *getZerSon(HuffmanNode *node);
        static HuffmanNode *getOneSon(HuffmanNode *node);
        static bool isLeaf(HuffmanNode *node);
        static void setSon(HuffmanNode *node, HuffmanNode *son, bool dir);

    private:
        int _priority;
        unsigned char _symb;
        HuffmanNode *_zerSon, *_oneSon;
    };
}

#endif //HW_02_HUFFMAN_HUFFMANNODE_H
