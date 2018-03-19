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
    Symbol s = stream.readSymbol();
    while (stream.good()) {
        symbolsCount[s] += 1;
        s = stream.readSymbol();
    }
    return symbolsCount;
}


bool compressFile(const std::string &inFilename, const std::string &outFilename) {
    SymbolStream in(inFilename, SymbolStream::inStream);
    //  counting symbols occurrence
    auto occurrence = symbolsOccurrence(in);
/*    for (const auto &i : occurrence) {
    printf("Symbol %u: %lu\n", static_cast<unsigned>(i.first.getCode()), i.second);
    }*/
    HuffmanTree tree(occurrence);
/*    int height = tree.postorder(tree.getRoot(), 0);
    std::cout << "Tree height: " << height-1 << std::endl;*/
    auto codeTable = tree.buildCodeTable();
/*    for (auto &i : codeTable) {
        std::cout << "Symbol " << i.first.getCode() << " has code " << i.second.binaryRepresentation() << std::endl;
    }*/
    in.seekg(0); // rewind stream at the begin
    Symbol s = in.readSymbol();
    SymbolStream out(outFilename, SymbolStream::outStream);
    while (in.good()) {
        out.writeSymbol(codeTable[s]);
        s = in.readSymbol();
    }
    return true;
}
