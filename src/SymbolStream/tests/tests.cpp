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

TEST(StreamTest, ioTest) {
    SymbolStreamInterface *stream = new SymbolStream("tmpTestFile.bin", SymbolStreamInterface::outStream);
    for (int i = 0; i < 10; ++i) {
        stream->writeSymbol(Symbol(0xaaaaaaaaaaaaaaaa, 64)); // writing 101010101...1010
    }
    stream->close();
    delete stream;
    stream =  new SymbolStream("tmpTestFile.bin", SymbolStreamInterface::inStream);
    // check summary 2 bytes
    ASSERT_EQ(stream->readSymbol(2), Symbol(0x2, 2));
    ASSERT_EQ(stream->readSymbol(4), Symbol(0xa, 4));
    ASSERT_EQ(stream->readSymbol(6), Symbol(0x2a, 6));
    ASSERT_EQ(stream->readSymbol(4), Symbol(0xa, 4));
    // check 4 bytes
    uint64_t  expectedBit = 1;
    for (int j = 0; j < 4*8; ++j) {
        ASSERT_EQ(stream->readSymbol(1), Symbol(expectedBit,1));
        expectedBit ^= 1;
    }
    // check one bit
    ASSERT_EQ(stream->readSymbol(1), Symbol(1,1));
    // check remained 73 byte and seven bits
    for (int k = 0; k < 9; ++k) { // check 72 byte
        ASSERT_EQ(stream->readSymbol(64), Symbol(0x5555555555555555, 64));
    }
    ASSERT_EQ(stream->readSymbol(8), Symbol(0x55,8)); // check one byte
    ASSERT_EQ(stream->readSymbol(7), Symbol(0x2a, 7));
    ASSERT_EQ(stream->readSymbol(1).size(), 0);
    ASSERT_FALSE(stream->good());
}