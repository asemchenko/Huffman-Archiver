//
// Created by asem on 15.03.18.
//

#ifndef HUFFMAN_ARCHIVER_SYMBOL_STREAM_H
#define HUFFMAN_ARCHIVER_SYMBOL_STREAM_H

#include <fstream>
#include <cstring>
#include <sstream>
#include "../Symbol/Symbol.h"

class SymbolStream {
public:
    enum ioDirect {
        inStream, outStream
    };

    SymbolStream(const std::string &fileName, ioDirect streamDirection);

    SymbolStream();

    bool open(const std::string &fileName, ioDirect streamDirection);

    bool isOpen() const;

    bool good() const;

    Symbol readSymbol();

    bool writeSymbol(Symbol s);

    void seekg(size_t pos);
    
    void flush();
    
    void close();
    
    ~SymbolStream();

private:
    ioDirect direction;
    std::fstream file;
    uint8_t buffer;
    size_t bufferBitSize;
};


#endif //HUFFMAN_ARCHIVER_SYMBOL_STREAM_H
