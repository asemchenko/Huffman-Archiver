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
    explicit Symbol(uint8_t v) : value(v), bitSize(8) {}

    explicit Symbol(uint64_t v, size_t bitSize_) : value(v), bitSize(bitSize_) {}

    Symbol() {}

    inline uint64_t getCode() const {
        return value;
    }

    bool operator==(const Symbol &s) const noexcept {
        return value == s.value;
    }

    void append(bool bit) {
        ++bitSize;
        value <<= 1;
        value |= (bit ? 1 : 0);
    }
    std::string binaryRepresentation() const {
        return std::bitset<64>(value).to_string().substr(64-bitSize, bitSize);
    }
    struct Hash {
        std::size_t operator()(const Symbol &s) const noexcept {
            return s.value;
        }
    };

private:
    uint64_t value;
    size_t bitSize;
};

#endif //HUFFMAN_ARCHIVER_SYMBOL_H
