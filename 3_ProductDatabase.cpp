#include <iostream>
#include <fstream>
#include <sstream>

#include "3_ProductDatabase.h"

ProductDatabase::ProductDatabase(const std::string &inputName, int categories)
    : name(inputName), numberOfCategories(categories) {
}

ProductDatabase::~ProductDatabase() {
    clearDatabase();
}

bool ProductDatabase::addProduct(const std::string &productName, int category) {
    if (isProductInDatabase(productName)) {
        return false;
    }

    if (category <= 0 || numberOfCategories < category) {
        return false;
    }

    Product *newProductPtr = new Product(productName, category);
    listOfProducts.insert(std::pair(productName, newProductPtr));
    numberOfProducts++;
    return true;
}

bool ProductDatabase::removeProduct(const std::string &productName) {
    if (!isProductInDatabase(productName)) {
        return false;
    }

    delete listOfProducts[productName];
    listOfProducts.erase(productName);
    numberOfProducts--;
    return true;
}

bool ProductDatabase::isProductInDatabase(const std::string &productName) {
    if (listOfProducts.find(productName) == listOfProducts.end()) {
        return false;
    }
    return true;
}

int ProductDatabase::importProductsFromFile(const std::string &fileName) {
    std::ifstream fileStream;
    fileStream.open(fileName);
    if (!fileStream) {
        return 0;
    }

    int cnt = 0;
    int category;
    std::string productName;

    while (!fileStream.eof()) {
        if (fileStream >> category) {
            std::getline(fileStream, productName);
            productName = productName.substr(1);

            if (addProduct(productName, category)) {
                cnt++;
            }
        }
    }
    return cnt;
}

void ProductDatabase::clearDatabase() {
    for (const auto &product: listOfProducts) {
        delete product.second;
    }
    listOfProducts.clear();
}