// Copyright 2005, Google Inc.
// All rights reserved.

#include "gtest/gtest.h"

#include "2_Product.h"

using namespace ::testing;

TEST(Product_Tests, ConstructedProduct) {
    std::string productName = "carrot";
    Product newProduct(productName, 8);
    ASSERT_EQ("carrot", newProduct.getName());
}

TEST(Product_Tests, MoveProduct) {
    std::string productName = "beef";
    Product oldProduct(productName, 6);
    Product newProduct(std::move(oldProduct));
    ASSERT_EQ("beef", newProduct.getName());
    ASSERT_EQ(0, oldProduct.getCategory());
    ASSERT_EQ("", oldProduct.getName());
}