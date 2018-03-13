//
// Created by asem on 12.03.18.
//

#ifndef HUFFMANS_CODE_HUFFMAN_FILE_PROCESSOR_H
#define HUFFMANS_CODE_HUFFMAN_FILE_PROCESSOR_H

#include <stdint.h>
#include <stdio.h>
// both macro must be changed, not one
// ***********************************
#define Symbol uint16_t
#define SYMBOL_SIZE_BITS 16
// ***********************************


uint64_t *getSymbolsCount(FILE *f);

#endif //HUFFMANS_CODE_HUFFMAN_FILE_PROCESSOR_H
