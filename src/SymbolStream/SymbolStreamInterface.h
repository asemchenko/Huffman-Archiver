//
// Created by asem on 20.03.18.
//

#ifndef HUFFMAN_ARCHIVER_SYMBOL_STREAM_INTERFACE_H
#define HUFFMAN_ARCHIVER_SYMBOL_STREAM_INTERFACE_H

#include "Symbol.h"
class SymbolStreamInterface {
public:
    enum ioDirect {
        inStream, outStream
    };

    virtual void open(const std::string &fileName, ioDirect streamDirection) = 0;

    virtual bool good() const = 0;

    virtual Symbol readSymbol() = 0;

    virtual bool writeSymbol(Symbol s) = 0;

    virtual void seekg(size_t pos) = 0;

    virtual void flush() = 0;

    virtual void close() = 0;

    virtual ~SymbolStreamInterface() = default;
};
#endif //HUFFMAN_ARCHIVER_SYMBOL_STREAM_INTERFACE_H
