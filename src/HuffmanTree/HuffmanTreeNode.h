//
// Created by asem on 15.03.18.
//

#ifndef HUFFMAN_ARCHIVER_HUFFMAN_TREENODE_H
#define HUFFMAN_ARCHIVER_HUFFMAN_TREENODE_H


#include "../SymbolStream/Symbol.h"
class HuffmanTreeNode {
public:
    // constructor creates non-leaf
    HuffmanTreeNode(uint64_t count,
                                     HuffmanTreeNode *left_,
                                     HuffmanTreeNode *right_);
    // constructor creates leaf
    HuffmanTreeNode(Symbol symbol_, uint64_t count_);
    ~HuffmanTreeNode();
    // preventing any copying
    HuffmanTreeNode(const HuffmanTreeNode &) = delete;
    HuffmanTreeNode(HuffmanTreeNode &&) = delete;
    void operator = (HuffmanTreeNode &) = delete;
    void operator = (HuffmanTreeNode &&) = delete;
    friend class HuffmanTree;
private:
    HuffmanTreeNode *left;
    HuffmanTreeNode *right;
    Symbol symbol;
    uint64_t countOccur;
    bool isLeaf;
};


#endif //HUFFMAN_ARCHIVER_HUFFMAN_TREENODE_H
