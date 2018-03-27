#include <iostream>
#include "API.h"

#include "SymbolStream/SymbolStream.h"

void printErrorUsage() {
    std::cerr << "Usage: <option> <inputFilename> <outputFilename>" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printErrorUsage();
        return 1;
    }
    try {
        if (std::string(argv[1]) == "-c") { // if compress option selected
            compressFile(argv[2], argv[3]);
        } else if (std::string(argv[1]) == "-d") { // if decompress option selected
            decompressFile(argv[2], argv[3]);
        } else {
            printErrorUsage();
            return 1;
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        // :)
        std::cerr << "Unexpected error occurred. Terminating ..." << std::endl;
        return 1;
    }
    return 0;
}