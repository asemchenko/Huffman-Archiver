//
// Created by asem on 19.03.18.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../HuffmanTree.h"
using testing::AtLeast;
class MockSymbolStreamInterface: public SymbolStreamInterface{
public:
    //MOCK_METHOD1(writeSymbol, bool(Symbol s));
    MOCK_METHOD0(good, bool());
    void open(const std::string &fileName, ioDirect streamDirection) override {}

    bool good() const override { return true;}

    Symbol readSymbol() override {return Symbol(0);}

    bool writeSymbol(Symbol s) override {return true;}

    void seekg(size_t pos) override {}

    void flush() override {}

    void close() override {}
};

TEST(HuffmanTreeTest, singleByteConstruct) {
    ASSERT_THROW(HuffmanTree({{Symbol(0), 1}}), std::logic_error);
}

TEST(HuffmanTreeTest, dumpTree) {
    HuffmanTree tree({
                             {Symbol(0), 10},
                             {Symbol(1), 5},
                             {Symbol(2), 1},
                             {Symbol(3), 1}
                     });
    MockSymbolStreamInterface stream;
    EXPECT_CALL(stream, good()).Times(AtLeast(1));
    stream.good();
    //tree.dump(&stream);
}