//
// Created by asem on 12.03.18.
//
#include "huffmanFileProcessor.h"
#include <stdlib.h>

// function readSymbol tries to read one symbol from file f, and store
// it in variable specified by symbol. If success returns 0.
// If error occurs returns count remained bytes and symbol
// will be aligned by zero bytes
size_t readSymbol(FILE *f, Symbol *symbol) {
#if SYMBOL_SIZE_BITS == 8 // optimizations if Symbol is a byte
    return 1 - fread(symbol, sizeof(Symbol), 1, f);
#else // interpreting symbol as binary number with big-endian byte order
    Symbol s = 0;
    uint8_t bytes[sizeof(Symbol)] = {0};
    size_t read = fread(&bytes, sizeof(uint8_t), sizeof(Symbol), f);
    for (size_t i = 0; i < sizeof(Symbol); ++i) {
        s <<= 8;
        s |= bytes[i];
    }
    *symbol = s;
    return sizeof(Symbol) - read;
#endif
}

// function getSymbolsCount returns an array A where stored count occurrences of
// symbols in file f. Array should be indexed by symbols numeric values.
// E.g. count symbols S will be placed at A[S]. Returned memory MUST BE FREED!
uint64_t *getSymbolsCount(FILE *f) {
    // 1U << 8*sizeof(Symbol) == 2 in pow count bits in Symbol representation
    // alternative, it's a count unique values which can be symbol
    uint64_t *count = (uint64_t *) calloc(1U << 8*sizeof(Symbol), sizeof(uint64_t));
    if (count == NULL) {
        fprintf(stderr, "Error: Can not allocate memory\n");
        return NULL;
    }
    Symbol s;
    while (readSymbol(f, &s) != sizeof(Symbol)) {
        ++count[s];
    }
    return count;
}