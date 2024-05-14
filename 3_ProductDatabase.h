#pragma once

#include <map>

#include "2_Product.h"

enum categories {VEGETABLES = 1, FRUITS, DAIRY, PROTEINS, SWEET, OTHER}; //0 is saved for non-existent default category

//collection of products
class ProductDatabase {
    std::string name = "My products";
    std::map<std::string, Product*> listOfProducts;
    int numberOfProducts = 0;

    const int numberOfCategories = 6; //default food categories characterized in enum categories

    private:
        void clearDatabase(); //clears listOfProducts and frees memory

    public:
        ProductDatabase() = default;

        ProductDatabase(const std::string &name, int categories); //sets name and number of food categories

        ~ProductDatabase();

        int getNumberOfProducts() const { return numberOfProducts; }

        bool isProductInDatabase(const std::string &productName); //checks if Product with given name is in listOfProducts

        bool addProduct(const std::string &productName, int category); //creates new Product, allocates memory, adds to listOfProducts, returns false if category invalid

        bool removeProduct(const std::string &productName); //removes Product from listOfProducts (if Product exists), frees memory

        int importProductsFromFile(const std::string &fileName); //returns number of imported products
};