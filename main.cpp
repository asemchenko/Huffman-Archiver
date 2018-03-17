#include <iostream>
#include "API.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: <inputFilename> <outputFilename>" << std::endl;
        return 1;
    }
    try {
        compressFile(argv[1], argv[2]);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}