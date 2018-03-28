//
// Created by asem on 27.03.18.
//

#include "Decoder.h"

Decoder::Decoder(SymbolStreamInterface *inStream,
                 SymbolStreamInterface *outStream,
                 HuffmanTree *codeTree) {
    inStream_ = inStream;
    outStream_ = outStream;
    codeTree_ = codeTree;
}

void Decoder::decode() {
    uint64_t symbolsCount = inStream_->readSymbol(64).getCode();
    Symbol s = inStream_->readSymbol(1);
    Node *curNode = codeTree_->root;
    while (inStream_->good() && symbolsCount) {
        if (curNode->isLeaf()) {
            outStream_->writeSymbol(curNode->getSymbol());
            --symbolsCount;
            curNode = codeTree_->root;
        }
        curNode = (s.getCode()==1?curNode->right:curNode->left);
        s = inStream_->readSymbol(1);
    }
    if (curNode->isLeaf() && symbolsCount) {
        outStream_->writeSymbol(curNode->getSymbol());
    }
}


