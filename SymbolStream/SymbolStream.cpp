//
// Created by asem on 15.03.18.
//

#include "SymbolStream.h"
#include <cstdint>
#include <stdexcept>

SymbolStream::SymbolStream(const std::string &fileName, ioDirect direction) {
    file.exceptions(std::ios_base::failbit | std::ios_base::badbit | std::ios_base::eofbit);
    open(fileName, direction);
}

SymbolStream::SymbolStream() {
    file.exceptions(std::ios_base::failbit | std::ios_base::badbit);
}

bool SymbolStream::open(const std::string &fileName, SymbolStream::ioDirect direction) {
    if (direction == inStream) {
        file.open(fileName, std::ios_base::in | std::ios_base::binary);
    } else {
        file.open(fileName, std::ios_base::out | std::ios_base::binary);
        bufferBitSize = 0;
        buffer = 0;
    }
    return file.is_open();
}

bool SymbolStream::isOpen() const {
    return file.is_open();
}

bool SymbolStream::good() const {
    return file.good();
}

Symbol SymbolStream::readSymbol() {
    char s;
    // potential problem - casting from uint8_t to char
    file.get(s);
    return Symbol(s);
}

bool SymbolStream::writeSymbol(Symbol s) {
    // buffer addition up to 8 bits
    if (bufferBitSize && s.size() >= (8-bufferBitSize)) {
        buffer |= s.popBits(8-bufferBitSize);
        file.put(buffer);
        bufferBitSize = 0;
        buffer = 0;
    }
    // writing remained symbol bits
    while (s.size() >= 8) {
        file.put(s.popBits(8));
    }
    size_t symbolSize = s.size();
    if (symbolSize) {
        buffer |= s.popBits(symbolSize) << (8-bufferBitSize-symbolSize);
        bufferBitSize += symbolSize;
    }
    return true;
}

void SymbolStream::flush() {
    if (direction == outStream && bufferBitSize) {
        file.put(buffer);
    }
}

SymbolStream::~SymbolStream() {
    close();
}

void SymbolStream::close() {
    flush();
    if (file.is_open()) {
        file.close();
    }
}
