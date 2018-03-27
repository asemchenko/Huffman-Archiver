//
// Created by asem on 15.03.18.
//

#include "Node.h"

Node::Node(uint64_t count, Node *left_, Node *right_) {
    countOccur = count;
    left = left_;
    right = right_;
    // this constructor creates internal tree node, so
    isLeaf_ = false;
}

Node::Node(Symbol symbol_, uint64_t count_) {
    symbol = symbol_;
    countOccur = count_;
    // this constructor creates leaf, so
    isLeaf_ = true;
    left = nullptr;
    right = nullptr;
}

Node::~Node() {
    delete left;
    delete right;
}

void Node::setSymbol(Symbol s) {
    symbol = s;
}

void Node::setLeafFlag(bool isLeaf) {
    isLeaf_ = isLeaf;
}


bool Node::isLeaf() {
    return isLeaf_;
}

const Symbol & Node::getSymbol() {
    return symbol;
}
