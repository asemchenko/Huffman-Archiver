//
// Created by asem on 19.03.18.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../HuffmanTree.h"
using testing::AtLeast;
class MockSymbolStreamInterface: public SymbolStreamInterface{
public:
    MOCK_METHOD1(writeSymbol, bool(Symbol s));
    void open(const std::string &fileName, ioDirect streamDirection) override {}

    bool good() const override { return true;}

    Symbol readByte() override {return Symbol(0);}

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
    {
        // dummy object which says gmock that expects strict order of calls
        ::testing::InSequence dummy;
        // checking header-codes length
        EXPECT_CALL(stream, writeSymbol(Symbol(7,64))).Times(1);
        // checking leafs count
        EXPECT_CALL(stream, writeSymbol(Symbol(4,64))).Times(1);
        // tree codes by range DDDUUU
        EXPECT_CALL(stream, writeSymbol(HuffmanTree::TREE_DUMP_DOWN_CODE)).Times(3); // D*3
        EXPECT_CALL(stream, writeSymbol(HuffmanTree::TREE_DUMP_UP_CODE)).Times(4);
        // leafs range - [2,3,1,0]
        EXPECT_CALL(stream, writeSymbol(Symbol(2))).Times(1);
        EXPECT_CALL(stream, writeSymbol(Symbol(3))).Times(1);
        EXPECT_CALL(stream, writeSymbol(Symbol(1))).Times(1);
        EXPECT_CALL(stream, writeSymbol(Symbol(0))).Times(1);
    }
    tree.dump(&stream);
}