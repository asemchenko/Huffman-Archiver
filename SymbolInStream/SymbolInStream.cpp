//
// Created by asem on 15.03.18.
//

#include "SymbolInStream.h"
#include <cstdint>

SymbolInStream::SymbolInStream(const std::string &fileName, ioDirect direction){
    if (direction == inStream) {
        file = std::fstream(fileName, std::ios_base::in | std::ios_base::binary);
    } else {
        file = std::fstream(fileName, std::ios_base::out | std::ios_base::binary);
        bufferBitSize = 0;
    }
}

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

bool SymbolInStream::writeSymbol(Symbol s) {
    // buffer addition up to 8 bits
    if (bufferBitSize) {
        buffer |= s.popBits(8-bufferBitSize);
        file.put(buffer);
        bufferBitSize = 0;
    }
    // writing remained symbol bits
    while (s.size() >= 8) {
        file.put(s.popBits(8));
    }
    size_t symbolSize = s.size();
    if (symbolSize) {
        buffer = s.popBits(s.size()) << (8-symbolSize);
        bufferBitSize = symbolSize;
    }
    return true;
}
