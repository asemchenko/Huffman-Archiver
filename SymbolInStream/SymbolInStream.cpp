//
// Created by asem on 15.03.18.
//

#include "SymbolInStream.h"
#include <cstdint>

SymbolInStream::SymbolInStream(const std::string &fileName) :
        file(fileName, std::ios_base::in | std::ios_base::binary) {}

bool SymbolInStream::isOpen() const {
    return file.is_open();
}

bool SymbolInStream::good() const {
    return file.good();
}

Symbol SymbolInStream::readSymbol() {
    char s;
    // potential problem - casting from uint8_t to char
    file.get(s);
    return Symbol(s);
}