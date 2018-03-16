//
// Created by asem on 15.03.18.
//

#ifndef HUFFMAN_ARCHIVER_HUFFMAN_TREE_H
#define HUFFMAN_ARCHIVER_HUFFMAN_TREE_H

#include <vector>
#include <unordered_map>
#include "../HuffmanTreeNode/HuffmanTreeNode.h"

#include <iostream>
#include <iomanip>
class HuffmanTree {
public:
    explicit HuffmanTree(const std::unordered_map<Symbol, uint64_t, Symbol::Hash> &occurrence);
    std::unordered_map<Symbol, Symbol, Symbol::Hash> buildCodeTable() const;
    ~HuffmanTree();
    int postorder(HuffmanTreeNode* p, int indent) {
        if(p) {
            int r = 0, l = 0;
            if(p->right) {
                r = postorder(p->right, indent+6);
            }
/*            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
            std::cout<< (p->isLeaf?p->symbol.getCode():p->countOccur) << "\n ";
*/
            if(p->left) {
//                std::cout << std::setw(indent) << ' ' <<" \\\n";
                l = postorder(p->left, indent+6);
            }
            return std::max(l+1, r+1);
        }
        return 0;
    }
    inline HuffmanTreeNode *getRoot() {
        return root;
    }
private:
    static bool cmp(const HuffmanTreeNode *a, const HuffmanTreeNode *b);
    void addToCodeTable(HuffmanTreeNode* root, Symbol s,
                       std::unordered_map<Symbol, Symbol, Symbol::Hash> &codeTable) const;
    std::vector<HuffmanTreeNode*>
    buildHeap(std::unordered_map<Symbol, uint64_t, Symbol::Hash> occurrence);
    HuffmanTreeNode *root;
    size_t symbolsCount;
};


#endif //HUFFMAN_ARCHIVER_HUFFMAN_TREE_H
