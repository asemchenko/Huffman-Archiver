//
// Created by asem on 15.03.18.
//
#include <algorithm>
#include "HuffmanTree.h"

bool HuffmanTree::cmp(const HuffmanTreeNode *a, const HuffmanTreeNode *b) {
    return a->countOccur > b->countOccur;
}

HuffmanTree::HuffmanTree(const std::unordered_map<Symbol, uint64_t, Symbol::Hash> &occurrence) {
    symbolsCount = occurrence.size();
    //building tree
    auto heap = buildHeap(occurrence);
    int iterCount = static_cast<int>(heap.size()) - 1;
    for (int i = 0; i < iterCount; ++i) {
        HuffmanTreeNode *l = heap.front();
        std::pop_heap(heap.begin(), heap.end(), cmp);
        heap.pop_back();

        HuffmanTreeNode *r = heap.front();
        std::pop_heap(heap.begin(), heap.end(), cmp);

        heap.back() = new HuffmanTreeNode(l->countOccur + r->countOccur, l, r);
        std::push_heap(heap.begin(), heap.end()-1);
    }
    root = heap.front();
}

std::vector<HuffmanTreeNode *>
HuffmanTree::buildHeap(std::unordered_map<Symbol, uint64_t, Symbol::Hash> occurrence) {
    // building heap
    std::vector<HuffmanTreeNode *> nodes;
    nodes.reserve(occurrence.size());
    for (auto &i : occurrence) {
        nodes.push_back(new HuffmanTreeNode(i.first, i.second));
    }
    std::make_heap(nodes.begin(), nodes.end(), cmp);
    return nodes;
}

HuffmanTree::~HuffmanTree() {
    delete root;
}

void HuffmanTree::addToCodeTable(HuffmanTreeNode *root, Symbol code,
                            std::unordered_map<Symbol, Symbol, Symbol::Hash> &codeTable) const {
    if(root->isLeaf) {
        codeTable.insert({root->symbol, code});
    } else {
        Symbol leftCode = code;
        leftCode.append(0);
        addToCodeTable(root->left, leftCode, codeTable);
        Symbol rightCode = code;
        rightCode.append(1);
        addToCodeTable(root->right, rightCode, codeTable);
    }
}

std::unordered_map<Symbol, Symbol, Symbol::Hash> HuffmanTree::buildCodeTable() const {
    std::unordered_map<Symbol, Symbol, Symbol::Hash> codeTable;
    codeTable.reserve(symbolsCount);
    Symbol startSymbol(0, 0);
    addToCodeTable(root, startSymbol, codeTable);
    return codeTable;
}