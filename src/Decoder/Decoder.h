//
// Created by asem on 27.03.18.
//

#ifndef HUFFMANARCHIVER_DECODER_H
#define HUFFMANARCHIVER_DECODER_H

#include "../HuffmanTree/HuffmanTree.h"
#include "../SymbolStream/SymbolStreamInterface.h"

class Decoder {
public:
    Decoder(SymbolStreamInterface *inStream,
            SymbolStreamInterface *outStream,
            HuffmanTree *codeTree);
    void decode();
private:
    SymbolStreamInterface *inStream_;
    SymbolStreamInterface *outStream_;
    HuffmanTree *codeTree_;
};


#endif //HUFFMANARCHIVER_DECODER_H
