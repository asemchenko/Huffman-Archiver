#include <iostream>
#include "API.h"

#include "SymbolStream/SymbolStream.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: <inputFilename> <outputFilename>" << std::endl;
        return 1;
    }
    SymbolStreamInterface *stream;
    try {
        //compressFile(argv[1], argv[2]);
        stream = new SymbolStream(argv[1], SymbolStreamInterface::inStream);
        size_t i = 1;
        Symbol s = stream->readSymbol(i);
        while (stream->good()) {
            std::cout << s.binaryRepresentation();
            ++i;
            s = stream->readSymbol(i);
        }
        std::cout << s.binaryRepresentation() << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    delete stream;
    return 0;
}