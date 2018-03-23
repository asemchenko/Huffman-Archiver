//
// Created by asem on 15.03.18.
//

#ifndef HUFFMAN_ARCHIVER_HUFFMAN_TREE_H
#define HUFFMAN_ARCHIVER_HUFFMAN_TREE_H

#include <vector>
#include <unordered_map>
#include "Node.h"
#include "../SymbolStream/SymbolStreamInterface.h"
#include <iostream>
#include <iomanip>

using CodeTable = std::unordered_map<Symbol, Symbol, Symbol::Hash>;
using OccurrenceTable = std::unordered_map<Symbol, uint64_t, Symbol::Hash>;

class HuffmanTree {
public:
    // create tree using symbol occurrence
    explicit HuffmanTree(const OccurrenceTable &occurrence);

    // import tree from file
    explicit HuffmanTree(SymbolStreamInterface *dumpSource);

    // calculate code for each symbol in tree and
    // get code table
    CodeTable buildCodeTable() const;

#ifdef DEBUG

    // prints tree into console
    int postorder(Node *p, int indent) {
        if (p) {
            int r = 0, l = 0;
            if (p->right) {
                r = postorder(p->right, indent + 6);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right) std::cout << " /\n" << std::setw(indent) << ' ';
            std::cout << (p->isLeaf ? p->symbol.getCode() : p->countOccur) << "\n ";
            if (p->left) {
                std::cout << std::setw(indent) << ' ' << " \\\n";
                l = postorder(p->left, indent + 6);
            }
            return std::max(l + 1, r + 1);
        }
        return 0;
    }

#endif

    // export tree into file
    void dump(SymbolStreamInterface *destination);

    ~HuffmanTree();

    // internal constants
    static const Symbol TREE_DUMP_DOWN_CODE;
    static const Symbol TREE_DUMP_UP_CODE;
private:
    static bool cmp(const Node *a, const Node *b);

    // recursively build code table
    void addSubtreeCodes(Node *root, Symbol s, CodeTable codeTable) const;

    // used to build tree from symbol occurrence table
    std::vector<Node *> buildHeap(OccurrenceTable occurrence);

    // recursively dump subtree
    void dumpSubtree(Node *treeRoot,
                     std::vector<Symbol> &leafs,
                     std::vector<Symbol> &codes);

    Node *root;
    size_t symbolsCount;
};


#endif //HUFFMAN_ARCHIVER_HUFFMAN_TREE_H
