//
// Created by asem on 15.03.18.
//

#include <unordered_map>
#include <vector>
#include "API.h"
#include "HuffmanTree/HuffmanTree.h"
using std::unordered_map;

static unordered_map<Symbol, uint64_t, Symbol::Hash> symbolsOccurrence(SymbolStream &stream) {
    unordered_map<Symbol , uint64_t, Symbol::Hash> symbolsCount;
    symbolsCount.reserve(256);
    Symbol s = stream.readByte();
    while (stream.good()) {
        symbolsCount[s] += 1;
        s = stream.readByte();
    }
    return symbolsCount;
}


bool compressFile(const std::string &inFilename, const std::string &outFilename) {
    SymbolStream in(inFilename, SymbolStream::inStream);
    //  counting symbols occurrence
    auto occurrence = symbolsOccurrence(in);
    HuffmanTree tree(occurrence);
    auto codeTable = tree.buildCodeTable();
#ifdef DEBUG
    for (const auto &i : occurrence) {
        printf("Symbol %u: %lu\n", static_cast<unsigned>(i.first.getCode()), i.second);
    }
    //int height = tree.postorder(tree.getRoot(), 0);
    //std::cout << "Tree height: " << height-1 << std::endl;
    for (auto &i : codeTable) {
        std::cout << "Symbol " << i.first.getCode() << " has code " << i.second.binaryRepresentation() << std::endl;
    }
#endif
    in.seekg(0); // rewind stream at the begin
    Symbol s = in.readByte();
    SymbolStream out(outFilename, SymbolStream::outStream);
    tree.dump(&out);
    while (in.good()) {
        out.writeSymbol(codeTable[s]);
        s = in.readByte();
    }
    return true;
}
