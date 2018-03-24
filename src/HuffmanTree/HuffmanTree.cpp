//
// Created by asem on 15.03.18.
//
#include <algorithm>
#include "HuffmanTree.h"

const Symbol HuffmanTree::TREE_DUMP_DOWN_CODE = Symbol(0, 1);
const Symbol HuffmanTree::TREE_DUMP_UP_CODE = Symbol(1, 1);

HuffmanTree::HuffmanTree(SymbolStreamInterface *dumpSource) {
    uint64_t codesCount = dumpSource->readSymbol(64).getCode();
    uint64_t leafsCount = dumpSource->readSymbol(64).getCode();
    if (!dumpSource->good()) {
        throw std::runtime_error("Error during reading header from stream");
    }
    // TODO implement dumping/recovering tree with leaf size greater than 8
    // reading leafs list
    std::vector<Symbol> leafs;
    leafs.reserve(leafsCount);
    for (uint64_t i = 0; i < leafsCount; ++i) {
        leafs.push_back(dumpSource->readSymbol(8));
    }
    // reading codes list
    std::vector<Symbol> codes;
    codes.reserve(codesCount);
    for (uint64_t j = 0; j < codesCount; ++j) {
        codes.push_back(dumpSource->readSymbol(1));
    }
    if (!dumpSource->good()) {
        throw std::runtime_error("Error during reading header from stream");
    }
    // recovering tree from dump

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
    if (root->isLeaf_) {
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
    // writing leafs
    for (auto leaf: leafs) {
        destination->writeSymbol(leaf);
    }
    // writing codes
    for (auto code:codes) {
        destination->writeSymbol(code);
    }
}

void HuffmanTree::dumpSubtree(Node *treeRoot, std::vector<Symbol> &leafs,
                              std::vector<Symbol> &codes) {
    if (treeRoot->isLeaf_) {
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

void HuffmanTree::recover(Node *root,
                          const std::vector<Symbol> &codes,
                          int &currentCodeIndex,
                          const std::vector<Symbol> &leafs,
                          int &currentLeafIndex) {
    // TODO check that this method works correctly
    if (currentCodeIndex >= codes.size()) {
        throw std::logic_error("Dump was damaged");
    }
    if (codes[currentCodeIndex] == TREE_DUMP_DOWN_CODE) {
        root->left = new Node(0, nullptr, nullptr);
        ++currentCodeIndex;
        recover(root->left, codes, currentCodeIndex, leafs, currentLeafIndex);
        root->right = new Node(0, nullptr, nullptr);
        recover(root->right, codes, currentCodeIndex, leafs, currentLeafIndex);
    } else {
        if (currentLeafIndex >= leafs.size()) {
            throw std::logic_error("Dump was damaged");
        }
        root->setLeafFlag(true);
        root->setSymbol(leafs[currentLeafIndex]);
        ++currentLeafIndex;
        ++currentCodeIndex;
    }
}
