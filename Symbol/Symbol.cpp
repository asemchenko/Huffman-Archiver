//
// Created by asem on 17.03.18.
//

#include "Symbol.h"

Symbol::Symbol(uint8_t v) : value(v), bitSize(8) {}

Symbol::Symbol(uint64_t v, size_t bitSize_) : value(v), bitSize(bitSize_) {}

uint64_t Symbol::getCode() const {
    return value;
}

bool Symbol::operator==(const Symbol &s) const noexcept {
    return value == s.value;
}

void Symbol::append(bool bit) {
    ++bitSize;
    value <<= 1;
    value |= (bit ? 1 : 0);
}

size_t Symbol::size() const {
    return bitSize;
}

uint8_t Symbol::popBits(size_t count) {
    // count must be less or equal 8
    // Symbol.size() must be greater or equal count
    bitSize -= count;
    return static_cast<uint8_t >(value >> count);
}

std::string Symbol::binaryRepresentation() const {
    return std::bitset<64>(value).to_string().substr(64 - bitSize, bitSize);
}

std::size_t Symbol::Hash::operator()(const Symbol &s) const noexcept {
        return s.value;
}