//
// Created by asem on 15.03.18.
//

#include "Node.h"

Node::Node(uint64_t count, Node *left_, Node *right_) {
    countOccur = count;
    left = left_;
    right = right_;
    // this constructor creates internal tree node, so
    isLeaf = false;
}

Node::Node(Symbol symbol_, uint64_t count_) {
    symbol = symbol_;
    countOccur = count_;
    // this constructor creates leaf, so
    isLeaf = true;
    left = nullptr;
    right = nullptr;
}

Node::~Node() {
    delete left;
    delete right;
}
