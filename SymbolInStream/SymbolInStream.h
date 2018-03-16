//
// Created by asem on 15.03.18.
//

#ifndef HUFFMAN_ARCHIVER_SYMBOL_STREAM_H
#define HUFFMAN_ARCHIVER_SYMBOL_STREAM_H

#include <fstream>
#include <cstring>
#include "../Symbol/Symbol.h"

class SymbolInStream {
public:
    enum ioDirect { inStream, outStream};
    SymbolInStream(const std::string &fileName, ioDirect direction);

    bool isOpen() const;

    bool good() const;

    Symbol readSymbol();

    bool writeSymbol(Symbol s);

private:

    std::fstream file;
    uint8_t buffer;
    size_t bufferBitSize;
};


#endif //HUFFMAN_ARCHIVER_SYMBOL_STREAM_H
