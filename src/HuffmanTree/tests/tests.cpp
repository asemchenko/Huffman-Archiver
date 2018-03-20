//
// Created by asem on 19.03.18.
//
#include <gtest/gtest.h>
#include "../HuffmanTree.h"

TEST(HuffmanTreeTest, singleByteConstruct) {
    ASSERT_THROW(HuffmanTree({{Symbol(0),1}}), std::logic_error);
}

TEST(HuffmanTreeTest, dumpTree) {

}