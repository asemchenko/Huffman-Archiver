//
// Created by asem on 15.03.18.
//
#include <algorithm>
#include "HuffmanTree.h"

const Symbol TREE_DUMP_DOWN_CODE = Symbol(0, 1);
const Symbol TREE_DUMP_UP_CODE = Symbol(1, 1);

bool HuffmanTree::cmp(const HuffmanTreeNode *a, const HuffmanTreeNode *b) {
    return a->countOccur > b->countOccur;
}

HuffmanTree::HuffmanTree(const std::unordered_map<Symbol, uint64_t, Symbol::Hash> &occurrence) :
        root(nullptr) {
    // todo refactor lines below - create method for building tree
    symbolsCount = occurrence.size();
    if (symbolsCount == 1) {
        // if file contains bytes with only one value
        // we can not build tree
        throw std::logic_error("Sorry, this file can not be compressed");
    }
    // building tree
    auto heap = buildHeap(occurrence);
    int iterCount = static_cast<int>(heap.size()) - 1;
    for (int i = 0; i < iterCount; ++i) {
        HuffmanTreeNode *l = heap.front();
        std::pop_heap(heap.begin(), heap.end(), cmp);
        heap.pop_back();

        HuffmanTreeNode *r = heap.front();
        std::pop_heap(heap.begin(), heap.end(), cmp);

        heap.back() = new HuffmanTreeNode(l->countOccur + r->countOccur, l, r);
        std::push_heap(heap.begin(), heap.end() - 1);
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
    if (root) {
        delete root;
    }
}

void HuffmanTree::addToCodeTable(HuffmanTreeNode *root, Symbol code,
                                 std::unordered_map<Symbol, Symbol, Symbol::Hash> &codeTable) const {
    if (root->isLeaf) {
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

void HuffmanTree::dump(SymbolStreamInterface *destination) {
    std::vector<Symbol> leafs;
    std::vector<Symbol> codes;
    dumpSubtree(root, leafs, codes);
    // writing header entry - codes count
    destination->writeSymbol(Symbol(codes.size(), 64));
    // writing header entry - leafs count
    // writing codes
    for (auto code:codes) {
        destination->writeSymbol(code);
    }
    // writing leafs
    for (auto leaf: leafs) {
        destination->writeSymbol(leaf);
    }
}

void HuffmanTree::dumpSubtree(HuffmanTreeNode *treeRoot, std::vector<Symbol> leafs, std::vector<Symbol> codes) {
    if (treeRoot->isLeaf) {
        leafs.push_back(treeRoot->symbol);
        codes.push_back(TREE_DUMP_UP_CODE);
    } else {
        codes.push_back(TREE_DUMP_DOWN_CODE);
        dumpSubtree(treeRoot->left, leafs, codes);
        dumpSubtree(treeRoot->right, leafs, codes);
    }
}

HuffmanTree::HuffmanTree(SymbolStreamInterface *dumpSource) {
    // todo implement me
}
