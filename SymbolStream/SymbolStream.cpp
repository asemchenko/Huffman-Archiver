//
// Created by asem on 15.03.18.
//

#include "SymbolStream.h"


SymbolStream::SymbolStream(const std::string &fileName, ioDirect streamDirection) {
    open(fileName, streamDirection);
}

SymbolStream::SymbolStream() = default;

bool SymbolStream::open(const std::string &fileName, SymbolStream::ioDirect streamDirection) {
    direction = streamDirection;
    if (streamDirection == inStream) {
        file.open(fileName, std::ios_base::in | std::ios_base::binary);
    } else {
        file.open(fileName, std::ios_base::out | std::ios_base::binary);
        bufferBitSize = 0;
        buffer = 0;
    }
    if (!file.is_open()) {
        throw std::runtime_error("Can not open file " + fileName);
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
    return Symbol(static_cast<uint8_t>(s));
}

bool SymbolStream::writeSymbol(Symbol s) {
    // buffer addition up to 8 bits
    if (bufferBitSize && s.size() >= (8 - bufferBitSize)) {
        buffer |= s.popBits(8 - bufferBitSize);
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
        buffer |= s.popBits(symbolSize) << (8 - bufferBitSize - symbolSize);
        bufferBitSize += symbolSize;
    }
    return true;
}

void SymbolStream::flush() {
    if (direction == inStream) {
        throw std::logic_error("Attempt flushing input stream");
    }
    else if (bufferBitSize) {
        file.put(buffer);
    }
}

SymbolStream::~SymbolStream() {
    close();
}

void SymbolStream::close() {
    if (direction == outStream) {
        flush();
    }
    if (file.is_open()) {
        file.close();
    }
}

void SymbolStream::seekg(size_t pos) {
    file.clear();
    file.seekg(pos);
}
