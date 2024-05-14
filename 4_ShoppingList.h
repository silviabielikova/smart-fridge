#pragma once

#include <string>
#include <map>
#include <fstream>
#include <sstream>

#include "4_ShoppingList.h"

const char SPACE = ' ';

//holds products and their quantities
class ShoppingList {
    std::string name = "My shopping list";
    std::map<std::string, int> listOfProducts; //product names and their wanted quantities
    int numberOfProducts = 0; //number of different products
    int numberOfItems = 0; //number of products, their quantities included

    private:
        bool isProductInShoppingList(const std::string &productName);

    public:
        ShoppingList() = default; //empty shopping list with default name

        ~ShoppingList();

        ShoppingList(const std::string &name); //empty shopping list with entered name

        ShoppingList(ShoppingList &&inputSL); //moves all contents from one shopping list to another

        void setName(const std::string &newName);

        int getNumberOfProducts() const { return numberOfProducts; };

        int getNumberOfItems() const { return numberOfItems; };

        bool exportToFile(const std::string &fileName); //exports to file and clears the shopping list

        bool addProduct(const std::string &productName, int number = 1); //adds up to existing quantity if product already in shopping list; returns false if number invalid

        bool removeProduct(const std::string &productName); //removes product and its quantity, returns false if product not found

        bool alterProductQuantity(const std::string &productName, int number); //alters quantity, returns falsie if product not found

        int getProductQuantity(const std::string &productName); //returns 0 if product with entered name is not in Shopping list

        bool removeAll(); //clears the shopping list, returns false if already empty
};