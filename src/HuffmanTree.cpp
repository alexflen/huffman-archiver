#include "HuffmanTree.h"
#include "MyException.h"
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

namespace MyHuffmanArchiver {
    HuffmanTree::HuffmanTree(std::vector<unsigned char> &bytes) {
        std::vector<int> cntByte(UCHAR_MAX + 1);
        for (auto &byte: bytes) cntByte[byte]++;

        auto compare = [](HuffmanNode *a, HuffmanNode *b) {
            return HuffmanNode::getPriority(a) > HuffmanNode::getPriority(b);
        }; // priority queue sorts in reversed order
        std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, decltype(compare)> heap(compare);

        for (int byte = 0; byte <= UCHAR_MAX; byte++) {
            if (cntByte[byte]) heap.push(new HuffmanNode(cntByte[byte], byte));
        }

        if (heap.size() <= 1) {
            root = new HuffmanNode(!heap.empty() ? heap.top() : nullptr, nullptr);
            if (!heap.empty()) heap.pop();
            return;
        }

        while (heap.size() > 1) {
            HuffmanNode *node1 = heap.top();
            heap.pop();
            HuffmanNode *node2 = heap.top();
            heap.pop();

            heap.push(new HuffmanNode(node1, node2));
        }

        root = heap.top();
        heap.pop();
    }

    HuffmanTree::HuffmanTree(std::vector<std::vector<bool>> &table) {
        root = new HuffmanNode(nullptr, nullptr);
        for (int byte = 0; byte <= UCHAR_MAX; byte++) {
            HuffmanNode *node = root;
            for (int bitNum = 0; bitNum < table[byte].size(); bitNum++) {
                HuffmanNode *son = goDown(node, table[byte][bitNum]);
                if (bitNum + 1 == table[byte].size()) { // last edge, make a new vertex with symb
                    if (son != nullptr) { // two symbols with matching prefix
                        throw MyException("Error: the huffman table is wrong");
                    }

                    son = new HuffmanNode(0, byte); // priority does not matter
                    HuffmanNode::setSon(node, son, table[byte][bitNum]);
                }

                if (son == nullptr) {
                    son = new HuffmanNode(nullptr, nullptr);
                    HuffmanNode::setSon(node, son, table[byte][bitNum]);
                }

                node = son;
            }
        }
    }

    void HuffmanTree::recursiveDestructor(HuffmanNode *node) {
        if (node == nullptr) return;
        recursiveDestructor(HuffmanNode::getZerSon(node));
        recursiveDestructor(HuffmanNode::getOneSon(node));
        delete node;
    }

    HuffmanTree::~HuffmanTree() {
        recursiveDestructor(root);
    }

    void HuffmanTree::fillTable(HuffmanNode *node, std::vector<bool> &way,
                                std::vector<std::vector<bool>> &table) const {
        if (node == nullptr) return;
        if (HuffmanNode::isLeaf(node)) {
            table[HuffmanNode::getSymb(node)] = way;
            return;
        }

        for (bool dir: {0, 1}) {
            way.push_back(dir);
            fillTable(goDown(node, dir), way, table);
            way.pop_back();
        }
    }

    std::vector<std::vector<bool>> HuffmanTree::getTable() const {
        std::vector<std::vector<bool>> result(UCHAR_MAX + 1);
        std::vector<bool> way = {};

        fillTable(root, way, result);

        return result;
    }

    HuffmanNode *HuffmanTree::goDown(HuffmanNode *node, bool dir) {
        if (dir == 0) {
            return HuffmanNode::getZerSon(node);
        } else {
            return HuffmanNode::getOneSon(node);
        }
    }
}