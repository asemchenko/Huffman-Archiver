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
    explicit SymbolInStream(const std::string &fileName);

    bool isOpen() const;

    bool good() const;

    Symbol readSymbol();

private:
    std::ifstream file;
};


#endif //HUFFMAN_ARCHIVER_SYMBOL_STREAM_H
