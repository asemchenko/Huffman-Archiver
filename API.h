//
// Created by asem on 15.03.18.
//

#ifndef HUFFMAN_ARCHIVER_API_H
#define HUFFMAN_ARCHIVER_API_H

#include <string>
#include <iostream>
#include "SymbolStream/SymbolStream.h"

bool compressFile(const std::string &inFilename, const std::string &outFilename);

#endif //HUFFMAN_ARCHIVER_API_H
