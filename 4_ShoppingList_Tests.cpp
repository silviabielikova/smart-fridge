// Copyright 2005, Google Inc.
// All rights reserved.

#include "gtest/gtest.h"

#include "4_ShoppingList.h"

using namespace ::testing;

TEST(ShoppingList_Tests, AddAndRemoveProducts) {
    ShoppingList newSL;
    newSL.addProduct("strawberry jam");
    newSL.addProduct("butter", 8);
    ASSERT_EQ(2, newSL.getNumberOfProducts());
    ASSERT_EQ(9, newSL.getNumberOfItems());
    newSL.removeProduct("butter");
    ASSERT_EQ(1, newSL.getNumberOfProducts());
    ASSERT_EQ(1, newSL.getNumberOfItems());
}

TEST(ShoppingList_Tests, AlteringQuantity) {
    ShoppingList newSL;
    newSL.addProduct("hummus", 2);
    ASSERT_FALSE(newSL.removeProduct("olives"));
    newSL.alterProductQuantity("hummus", 4);
    ASSERT_EQ(4, newSL.getNumberOfItems());
}

TEST(ShoppingList_Tests, Export) {
    ShoppingList newSL;
    newSL.addProduct("heavy cream", 4);
    newSL.addProduct("feta cheese", 2);
    ASSERT_TRUE(newSL.exportToFile("my_shopping_list.txt"));
}

TEST(ShoppingList_Tests, Move) {
    ShoppingList lidlSL;
    lidlSL.addProduct("ketchup");
    lidlSL.addProduct("pickles", 2);
    lidlSL.addProduct("milk", 5);
    lidlSL.addProduct("jam", 2);
    ShoppingList tescoSL(std::move(lidlSL));
    ASSERT_EQ(0, lidlSL.getNumberOfProducts());
    ASSERT_EQ(4, tescoSL.getNumberOfProducts());
    ASSERT_EQ(0, lidlSL.getProductQuantity("milk"));
    ASSERT_EQ(5, tescoSL.getProductQuantity("milk"));
}