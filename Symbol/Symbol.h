//
// Created by asem on 15.03.18.
//

#ifndef HUFFMAN_ARCHIVER_SYMBOL_H
#define HUFFMAN_ARCHIVER_SYMBOL_H

#include <cstdlib>
#include <cstdint>

#include <bitset>

class Symbol {
public:
    explicit Symbol(uint8_t v);

    explicit Symbol(uint64_t v, size_t bitSize_);

    Symbol() = default;

    uint64_t getCode() const;

    bool operator==(const Symbol &s) const noexcept ;

    void append(bool bit);

    size_t size() const;

    uint8_t popBits(size_t count);

    std::string binaryRepresentation() const;

    struct Hash {
        std::size_t operator()(const Symbol &s) const noexcept;
    };

private:
    uint64_t value;
    size_t bitSize;
};

#endif //HUFFMAN_ARCHIVER_SYMBOL_H
