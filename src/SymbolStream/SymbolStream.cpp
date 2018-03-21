//
// Created by asem on 15.03.18.
//

#include "SymbolStream.h"

SymbolStream::SymbolStream(const std::string &fileName, ioDirect streamDirection) {
    open(fileName, streamDirection);
}

SymbolStream::SymbolStream() {
    file = nullptr;
}

void SymbolStream::open(const std::string &fileName, SymbolStream::ioDirect streamDirection) {
    direction = streamDirection;
    if (streamDirection == inStream) {
        file = fopen(fileName.c_str(), "rb");
    } else {
        file = fopen(fileName.c_str(), "wb");
        bufferBitSize = 0;
        buffer = 0;
    }
    if (!file || ferror(file)) {
        throw std::runtime_error("Can not open file " + fileName);
    }
}

bool SymbolStream::good() const {
    return !feof(file) && !static_cast<bool>(ferror(file));
}

Symbol SymbolStream::readSymbol() {
    uint8_t s;
    // potential problem - casting from uint8_t to char
    fread(&s, sizeof(uint8_t), 1, file);
    return Symbol(s);
}

bool SymbolStream::writeSymbol(Symbol s) {
    // buffer addition up to 8 bits
    if (bufferBitSize && s.size() >= (8 - bufferBitSize)) {
        buffer |= s.popBits(8 - bufferBitSize);
        fwrite(&buffer, sizeof(buffer), 1, file);
        bufferBitSize = 0;
        buffer = 0;
    }
    // writing remained symbol bits
    while (s.size() >= 8) {
        uint8_t bits = s.popBits(8);
        fwrite(&bits, sizeof(bits), 1, file);
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
        fflush(file);
    }
}

SymbolStream::~SymbolStream() {
    close();
}

void SymbolStream::close() {
    if (direction == outStream) {
        flush();
    }
    if (file) {
        fclose(file);
        file = nullptr;
    }
}

void SymbolStream::seekg(size_t pos) {
    clearerr(file);
    fseek(file, 0, SEEK_SET);
}
