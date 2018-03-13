#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "huffmanFileProcessor.h"



int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: huffman <filename>\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "rb");
    if(f == NULL) {
        fprintf(stderr, "Error in opening file %s: %s\n", argv[1], strerror(errno));
        return 1;
    }
    uint64_t *count = getSymbolsCount(f);
    uint64_t sum = 0;
    for (int i = 0; i < (1U << 8*sizeof(Symbol)); ++i) {
        if (count[i]) {
            printf("Symbol 0x%x appeared %lu\n", i, count[i]);
            sum += count[i];
        }
    }
    printf("Total: %lu\n", sum);
    free(count);
    return 0;
}