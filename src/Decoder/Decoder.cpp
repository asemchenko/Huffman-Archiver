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
    Symbol s = inStream_->readSymbol(1);
    Node *curNode = codeTree_->root;
    while (inStream_->good()) {
        if (curNode->isLeaf()) {
            outStream_->writeSymbol(curNode->getSymbol());
            curNode = codeTree_->root;
        } else {
            curNode = (s.getCode()==1?curNode->right:curNode->left);
        }
        s = inStream_->readSymbol(1);
    }
    if (curNode->isLeaf()) {
        outStream_->writeSymbol(curNode->getSymbol());
    }
}


