//
// Created by asem on 15.03.18.
//

#ifndef HUFFMAN_ARCHIVER_SYMBOL_STREAM_H
#define HUFFMAN_ARCHIVER_SYMBOL_STREAM_H

#include <fstream>
#include <cstring>
#include <sstream>
#include "SymbolStreamInterface.h"

class SymbolStream: public SymbolStreamInterface {
public:
    SymbolStream(const std::string &fileName, ioDirect streamDirection);

    SymbolStream();

    void open(const std::string &fileName, ioDirect streamDirection) final ;

    bool good() const final ;

    Symbol readByte() final;

    Symbol readSymbol(size_t bitsCount) final;

    bool writeSymbol(Symbol s) final;

    void seekg(size_t pos) final;
    
    void flush() final;
    
    void close() final;
    
    ~SymbolStream() final;

    SymbolStream(SymbolStream &) = delete;
    SymbolStream(SymbolStream &&) = delete;
    void operator = (SymbolStream &) = delete;
    void operator = (SymbolStream &&) = delete;
private:
    ioDirect direction;
    FILE *file;
    uint8_t buffer;
    size_t bufferBitSize;
};


#endif //HUFFMAN_ARCHIVER_SYMBOL_STREAM_H
