//
// Created by asem on 15.03.18.
//

#include <unordered_map>
#include <vector>
#include "API.h"
#include "HuffmanTree/HuffmanTree.h"
#include "Decoder/Decoder.h"
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
    printf("============ Symbols frequency ======================\n");
    for (const auto &i : occurrence) {
        printf("Symbol %u: %lu\n", static_cast<unsigned>(i.first.getCode()), i.second);
    }
    //int height = tree.postorder(tree.getRoot(), 0);
    //std::cout << "Tree height: " << height-1 << std::endl;
    printf("============ Symbols codes ======================\n");
    for (auto &i : codeTable) {
        std::cout << "Symbol 0x" << std::hex << i.first.getCode() << " has code " << i.second.binaryRepresentation() << std::endl;
    }
#endif
    in.seekg(0); // rewind stream at the begin
    SymbolStream out(outFilename, SymbolStream::outStream);
    tree.dump(&out);
    auto countSymbolsInOutFile = static_cast<uint64_t>(in.fileSize());
    out.writeSymbol(Symbol(countSymbolsInOutFile, 64));
#ifdef DEBUG
    printf("FILE SIZE: %ld\n", countSymbolsInOutFile);
#endif
    Symbol s = in.readByte();
    while (in.good()) {
        out.writeSymbol(codeTable[s]);
        s = in.readByte();
    }
    // TODO catch exceptions and return false if error occurred
    return true;
}

bool decompressFile(const std::string &inFilename,
                    const std::string &outFilename) {
    SymbolStreamInterface *inStream = new SymbolStream(inFilename, SymbolStreamInterface::inStream);
    SymbolStreamInterface *outStream = new SymbolStream(outFilename, SymbolStreamInterface::outStream);
    HuffmanTree codeTree(inStream);
    Decoder decoder(inStream, outStream, &codeTree);
    decoder.decode();
    return true;
}