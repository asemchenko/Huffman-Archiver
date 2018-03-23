//
// Created by asem on 16.03.18.
//
#include <gtest/gtest.h>
#include "../SymbolStream.h"


TEST(InStreamTest, openingUnexistingFile) {
    SymbolStream s;
    ASSERT_THROW(s.open("noSuchFile", SymbolStream::inStream), std::runtime_error);
}

TEST(InStreamTest, readingBits) {
    SymbolStream s("uniqBytes.bin", SymbolStream::inStream);
    for (int i = 0; i < 256; ++i) {
        ASSERT_EQ(s.readByte().getCode(), i);
    }
}

TEST(OutStreamTest, writingBits) {
    SymbolStream out("bits", SymbolStream::outStream);
    // writing byte 0xff to stream
    for (int i = 0; i < 8; ++i) {
        out.writeSymbol(Symbol(0xffffffff, 1));
    }
    // writing 62 bytes 0xff
    for (int j = 0; j < 32; ++j) {
        out.writeSymbol(Symbol(0xffffffff, static_cast<size_t>(j)));
    }
    out.close();
    // must read 63 bytes 0xff
    SymbolStream in("bits", SymbolStream::inStream);
    for (int k = 0; k < 63; ++k) {
        ASSERT_EQ(in.readByte().getCode(), 0xff);
    }
    in.readByte();
    ASSERT_FALSE(in.good());
}

// TODO write main test which checks writing and reading bits