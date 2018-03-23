//
// Created by asem on 15.03.18.
//
#include <algorithm>
#include "HuffmanTree.h"

const Symbol HuffmanTree::TREE_DUMP_DOWN_CODE = Symbol(0, 1);
const Symbol HuffmanTree::TREE_DUMP_UP_CODE = Symbol(1, 1);

HuffmanTree::HuffmanTree(SymbolStreamInterface *dumpSource) {

}

HuffmanTree::HuffmanTree(const OccurrenceTable &occurrence) :
        root(nullptr) {
    symbolsCount = occurrence.size();
    if (symbolsCount == 1) {
        // if file contains bytes with only one value
        // we can not build tree
        throw std::logic_error("Sorry, this file can not be compressed");
    }
    auto heap = buildHeap(occurrence); // putting symbols occurrence into heap
    buildTree(heap);
}

bool HuffmanTree::cmp(const Node *a, const Node *b) {
    return a->countOccur > b->countOccur;
}

std::vector<Node *>
HuffmanTree::buildHeap(OccurrenceTable occurrence) {
    // building heap
    std::vector<Node *> nodes;
    nodes.reserve(occurrence.size());
    for (auto &i : occurrence) {
        nodes.push_back(new Node(i.first, i.second));
    }
    std::make_heap(nodes.begin(), nodes.end(), cmp);
    return nodes;
}

void HuffmanTree::buildTree(std::vector<Node *> &heap) {
    int iterCount = static_cast<int>(heap.size()) - 1;
    for (int i = 0; i < iterCount; ++i) {
        Node *l = heap.front();
        std::pop_heap(heap.begin(), heap.end(), cmp);
        heap.pop_back();

        Node *r = heap.front();
        std::pop_heap(heap.begin(), heap.end(), cmp);

        heap.back() = new Node(l->countOccur + r->countOccur, l, r);
        std::push_heap(heap.begin(), heap.end(), cmp);
    }
    root = heap.front();
}

void HuffmanTree::addSubtreeCodes(Node *root,
                                  Symbol code,
                                  CodeTable codeTable) const {
    if (root->isLeaf) {
        codeTable.insert({root->symbol, code});
    } else {
        Symbol leftCode = code;
        leftCode.append(0);
        addSubtreeCodes(root->left, leftCode, codeTable);
        Symbol rightCode = code;
        rightCode.append(1);
        addSubtreeCodes(root->right, rightCode, codeTable);
    }
}

CodeTable HuffmanTree::buildCodeTable() const {
    CodeTable codes;
    codes.reserve(symbolsCount);
    Symbol startSymbol(0, 0);
    addSubtreeCodes(root, startSymbol, codes);
    return codes;
}

void HuffmanTree::dump(SymbolStreamInterface *destination) {
    std::vector<Symbol> leafs;
    std::vector<Symbol> codes;
    dumpSubtree(root, leafs, codes);
    // writing header entry - codes count
    destination->writeSymbol(Symbol(codes.size(), 64));
    // writing header entry - leafs count
    destination->writeSymbol(Symbol(leafs.size(), 64));
    // writing codes
    for (auto code:codes) {
        destination->writeSymbol(code);
    }
    // writing leafs
    for (auto leaf: leafs) {
        destination->writeSymbol(leaf);
    }
}

void HuffmanTree::dumpSubtree(Node *treeRoot, std::vector<Symbol> &leafs,
                              std::vector<Symbol> &codes) {
    if (treeRoot->isLeaf) {
        leafs.push_back(treeRoot->symbol);
        codes.push_back(TREE_DUMP_UP_CODE);
    } else {
        codes.push_back(TREE_DUMP_DOWN_CODE);
        dumpSubtree(treeRoot->left, leafs, codes);
        dumpSubtree(treeRoot->right, leafs, codes);
    }
}

HuffmanTree::~HuffmanTree() {
    if (root) {
        delete root;
    }
}
