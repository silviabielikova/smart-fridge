// Copyright 2005, Google Inc.
// All rights reserved.

#include "gtest/gtest.h"

#include "6_Fridge.h"

using namespace ::testing;

TEST(Fridge_Tests, ImportCorrectItems) {
    Fridge myFridge;
    ASSERT_EQ(14, myFridge.importToFridgeFromFile("correct_import.txt"));
}

TEST(Fridge_Tests, ImportIncorrectItems) {
    Fridge myFridge;
    ASSERT_EQ(11, myFridge.importToFridgeFromFile("incorrect_import.txt"));
    ASSERT_EQ(0, myFridge.getProductQuantity("cheese"));
}

TEST(Fridge_Tests, TwoExpirationDates) {
    Fridge myFridge;
    myFridge.insertItem("ham", Date(1, 1, 2023), 2);
    myFridge.insertItem("ham", Date(6, 1, 2023), 1);
    ASSERT_EQ(3, myFridge.getProductQuantity("ham"));
}

TEST(Fridge_Tests, PickItemOut) {
    Fridge myFridge;
    myFridge.insertItem("milk", Date(31, 12, 2022), 2);
    myFridge.insertItem("milk", Date(25, 12, 2022), 1);
    myFridge.insertItem("milk", Date(27, 12, 2022), 2);
    ASSERT_EQ(5, myFridge.getProductQuantity("milk"));
    ASSERT_EQ("25/12/2022", myFridge.pickOutItem("milk").getDate());
    ASSERT_EQ("27/12/2022", myFridge.pickOutItem("milk").getDate());
}

TEST(Fridge_Tests, RemoveAndAddProduct) {
    Fridge myFridge;
    myFridge.removeProductFromDatabase("avocado");
    ASSERT_FALSE(myFridge.insertItem("avocado", Date(26, 12, 2022)));
    myFridge.addProductToDatabase("avocado", VEGETABLES);
    ASSERT_TRUE(myFridge.insertItem("avocado", Date(26, 12, 2022)));
}

TEST(Fridge_Tests, RemoveLastItem) {
    Fridge myFridge("My smart fridge");
    ASSERT_TRUE(myFridge.insertItem("avocado", Date(26, 12, 2022), 2));
    ASSERT_NE("00/00/0000", myFridge.pickOutItem("avocado").getDate());
    ASSERT_NE("00/00/0000", myFridge.pickOutItem("avocado").getDate());
    ASSERT_EQ(0, myFridge.getProductQuantity("avocado"));
}

TEST(Fridge_Tests, ShoppingList) {
    Fridge myFridge;
    myFridge.createNewShoppingList("Birthday party");
    myFridge.addToShoppingList("Birthday party", "soda", 5);
    myFridge.addToShoppingList("avocado", 2);
    ASSERT_EQ(myFridge.getProductQuantityInShoppingList("Groceries", "avocado"), 2);
    ASSERT_EQ(myFridge.getNumberOfProductsInShoppingList("Birthday party"), 1);
    ASSERT_TRUE(myFridge.exportShoppingList("Groceries"));
}

TEST(Fridge_Tests, GetAll) {
    Fridge myFridge;
    ASSERT_TRUE(myFridge.insertItem("heavy cream", Date(26, 12, 2022), 5));
    ASSERT_EQ(5, myFridge.getAll()->find("heavy cream")->second.size());
}

TEST(Fridge_Tests, NoneSoonToExpire) {
    Fridge myFridge;
    Date today = getTodaysDate();
    Date futureDate = today + 50;
    myFridge.insertItem("ketchup", futureDate);
    ASSERT_EQ(myFridge.getSoonToExpire(), std::vector<Item*>());
}

TEST(Fridge_Tests, SomeSoonToExpire) {
    Fridge myFridge;
    Date today = getTodaysDate();
    myFridge.insertItem("cheese", today + 2);
    myFridge.insertItem("cheese", today + 20);
    ASSERT_EQ(myFridge.getSoonToExpire().size(), 1);
}

TEST(Fridge_Tests, SoonToExpireWithDaysEntered) {
    Fridge myFridge;
    Date today = getTodaysDate();
    myFridge.insertItem("milk", today + 2, 2);
    myFridge.insertItem("cheese", today + 15);
    ASSERT_EQ(myFridge.getSoonToExpire(15).size(), 3);
    ASSERT_EQ(myFridge.getSoonToExpire(2).size(), 2);
}

TEST(Fridge_Tests, EssentialsMissing) {
    Fridge myFridge;
    ASSERT_EQ(myFridge.getProductQuantityInShoppingList("Groceries", "butter"), 2);
    myFridge.exportShoppingList("Groceries");
    myFridge.insertItem("butter", Date(29, 3, 2023));
    myFridge.insertItem("butter", Date(27, 3, 2023));
    myFridge.pickOutItem("butter");
    ASSERT_EQ(myFridge.getProductQuantityInShoppingList("Groceries", "butter"), 1);
}

TEST(Fridge_Tests, AddingEssentials) {
    Fridge myFridge;
    myFridge.insertItem("yoghurt", Date(22, 2, 2023), 2);
    myFridge.addToEssentials("yoghurt", 5);
    ASSERT_EQ(myFridge.getProductQuantityInShoppingList("Groceries", "yoghurt"), 3);
}

TEST(Fridge_Tests, StockUpNewFridge) {
    Fridge myFridge;
    ASSERT_EQ(myFridge.getProductQuantityInShoppingList("Groceries", "butter"), 2);
    ASSERT_EQ(myFridge.getProductQuantityInShoppingList("Groceries", "milk"), 2);
}