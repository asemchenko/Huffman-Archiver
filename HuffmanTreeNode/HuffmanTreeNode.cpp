//
// Created by asem on 15.03.18.
//

#include "HuffmanTreeNode.h"

HuffmanTreeNode::HuffmanTreeNode(uint64_t count, HuffmanTreeNode *left_, HuffmanTreeNode *right_) {
    countOccur = count;
    left = left_;
    right = right_;
    // this constructor creates internal tree node, so
    isLeaf = false;
}

HuffmanTreeNode::HuffmanTreeNode(Symbol symbol_, uint64_t count_) {
    symbol = symbol_;
    countOccur = count_;
    // this constructor creates leaf, so
    isLeaf = true;
    left = nullptr;
    right = nullptr;
}

HuffmanTreeNode::~HuffmanTreeNode() {
    delete left;
    delete right;
}
