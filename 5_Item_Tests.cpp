// Copyright 2005, Google Inc.
// All rights reserved.

#include "gtest/gtest.h"

#include "5_Item.h"

using namespace ::testing;

TEST(Item_Tests, ConstructedItem) {
    std::string productName = "ketchup";
    Date expDate(3, 4, 2023);
    Item newItem(productName, expDate, 5);
    ASSERT_EQ("ketchup", newItem.getProductName());
}