//
// Created by asem on 15.03.18.
//

#ifndef HUFFMAN_ARCHIVER_HUFFMAN_TREE_NODE_H
#define HUFFMAN_ARCHIVER_HUFFMAN_TREE_NODE_H


#include "../SymbolStream/Symbol.h"
class Node {
public:
    // create non-leaf node
    Node(uint64_t count,
                                     Node *left_,
                                     Node *right_);
    // create leaf node
    Node(Symbol symbol_, uint64_t count_);
    void setSymbol(Symbol s);
    void setLeafFlag(bool isLeaf);
    bool isLeaf();
    const Symbol & getSymbol();
    ~Node();
    // preventing any copying
    Node(const Node &) = delete;
    Node(Node &&) = delete;
    void operator = (Node &) = delete;
    void operator = (Node &&) = delete;
    friend class HuffmanTree;
    friend class Decoder;
private:
    Node *left;
    Node *right;
    Symbol symbol; // not empty only if node is leaf
    uint64_t countOccur;
    bool isLeaf_;
};


#endif //HUFFMAN_ARCHIVER_HUFFMAN_TREE_NODE_H
