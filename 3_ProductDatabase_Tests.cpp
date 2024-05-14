// Copyright 2005, Google Inc.
// All rights reserved.

#include "gtest/gtest.h"

#include "3_ProductDatabase.h"

using namespace ::testing;

TEST(ProductDatabase_Tests, AddTwoProducts) {
    ProductDatabase newDatabase;
    std::string productName1 = "yoghurt";
    std::string productName2 = "beef";
    ASSERT_TRUE(newDatabase.addProduct(productName1, DAIRY));
    ASSERT_FALSE(newDatabase.addProduct(productName2, 8));
    ASSERT_EQ(1, newDatabase.getNumberOfProducts());
}

TEST(ProductDatabase_Tests, RemoveProduct) {
    ProductDatabase newDatabase;
    std::string productName1 = "milk";
    std::string productName2 = "chicken";
    ASSERT_TRUE(newDatabase.addProduct(productName1, DAIRY));
    ASSERT_TRUE(newDatabase.addProduct(productName2, PROTEINS));
    ASSERT_TRUE(newDatabase.removeProduct(productName1));
    ASSERT_EQ(1, newDatabase.getNumberOfProducts());
}