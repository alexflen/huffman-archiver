#include "HuffmanNode.h"
#include "MyException.h"

namespace MyHuffmanArchiver {
    int HuffmanNode::getPriority(HuffmanNode *node) {
        if (node == nullptr) return 0;
        return node->_priority;
    }

    unsigned char HuffmanNode::getSymb(HuffmanNode *node) {
        if (node == nullptr) return 0;
        return node->_symb;
    }

    HuffmanNode *HuffmanNode::getZerSon(HuffmanNode *node) {
        if (node == nullptr) return nullptr;
        return node->_zerSon;
    }

    HuffmanNode *HuffmanNode::getOneSon(HuffmanNode *node) {
        if (node == nullptr) return nullptr;
        return node->_oneSon;
    }

    bool HuffmanNode::isLeaf(HuffmanNode *node) {
        return HuffmanNode::getOneSon(node) == nullptr && HuffmanNode::getZerSon(node) == nullptr;
    }

    void HuffmanNode::setSon(HuffmanNode *node, HuffmanNode *son, bool dir) {
        if (node == nullptr) return;
        if (dir == 0) {
            node->_zerSon = son;
        } else {
            node->_oneSon = son;
        }
    }
}