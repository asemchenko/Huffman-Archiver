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
    }
    bufferBitSize = 0;
    buffer = 0;
    if (!file || ferror(file)) {
        throw std::runtime_error("Can not open file " + fileName);
    }
}

bool SymbolStream::good() const {
    bool eof = static_cast<bool>(feof(file));
    bool err = static_cast<bool>(ferror(file));
    return !eof && !err;
}

Symbol SymbolStream::readByte() {
    return readSymbol(8);
}

bool SymbolStream::writeSymbol(Symbol s) {
    // buffer addition up to 8 bits
    if (bufferBitSize && s.size() >= (8 - bufferBitSize)) {
        buffer |= s.popFrontBits(8 - bufferBitSize);
        fwrite(&buffer, sizeof(buffer), 1, file);
        bufferBitSize = 0;
        buffer = 0;
    }
    // writing remained symbol bits
    while (s.size() >= 8) {
        uint8_t bits = s.popFrontBits(8);
        fwrite(&bits, sizeof(bits), 1, file);
    }
    size_t symbolSize = s.size();
    if (symbolSize) {
        buffer |= s.popFrontBits(symbolSize) << (8 - bufferBitSize - symbolSize);
        bufferBitSize += symbolSize;
    }
    return true;
}

void SymbolStream::flush() {
    if (direction == inStream) {
        throw std::logic_error("Attempt flushing input stream");
    }
    else {
        fflush(file);
    }
}

SymbolStream::~SymbolStream() {
    close();
}

void SymbolStream::close() {
    if (direction == outStream && file) {
        if (bufferBitSize) {
            fwrite(&buffer, sizeof(buffer), 1, file);
        }
    }
    if (file) {
        fclose(file);
        file = nullptr;
    }
}

void SymbolStream::seekg(size_t pos) {
    clearerr(file);
    fseek(file, pos, SEEK_SET);
    if (!good()) {
        throw std::runtime_error("Error during setting file seek");
    }
}

Symbol SymbolStream::readSymbol(size_t bitsCount) {
    uint64_t readedSymbol = 0;
    size_t readedSymbolSize = 0;
    if (bufferBitSize) { // firstly reads data from buffer
        size_t countBitsFromBuffer = std::min(bitsCount, bufferBitSize);
        readedSymbol = buffer >> 8 - countBitsFromBuffer;
        buffer <<= countBitsFromBuffer;
        bufferBitSize -= countBitsFromBuffer;
        bitsCount -= countBitsFromBuffer;
        readedSymbolSize += countBitsFromBuffer;
    }
    if (!bitsCount) {
        return Symbol(readedSymbol, readedSymbolSize);
    }
    fread(&buffer, sizeof(buffer), 1, file); // reading byte to buffer
    while (bitsCount/8 && good()) {
        readedSymbol <<= 8;
        readedSymbol |= buffer;
        readedSymbolSize += 8;
        bitsCount -= 8;
        fread(&buffer, sizeof(buffer), 1, file); // reading byte to buffer
    }
    if (good()) {
        bufferBitSize = 8;
    } else {
        bufferBitSize = 0;
        return Symbol(readedSymbol, readedSymbolSize);
    }
    if (bitsCount) {
        readedSymbol <<= bitsCount;
        readedSymbol |= buffer >> 8-bitsCount;
        readedSymbolSize += bitsCount;
        buffer <<= bitsCount;
        bufferBitSize -= bitsCount;
    }
    return Symbol(readedSymbol, readedSymbolSize);
}
