#include "4_ShoppingList.h"

ShoppingList::ShoppingList(const std::string &name) : name(name) {

}

ShoppingList::ShoppingList(ShoppingList &&inputSL)
        : name(std::move(inputSL.name)), listOfProducts(std::move(inputSL.listOfProducts)),
          numberOfProducts(inputSL.numberOfProducts), numberOfItems(inputSL.numberOfItems) {
    inputSL.numberOfItems = 0;
    inputSL.numberOfProducts = 0;
}

bool ShoppingList::exportToFile(const std::string &fileName) {
    if (fileName.empty()) {
        return false;
    }

    std::ofstream fileStream;
    fileStream.open(fileName, std::ios::out);

    if (!fileStream) {
        return false;
    }

    fileStream << name;

    for (auto row: listOfProducts) {
        std::string productName = row.first;
        int number = row.second;
        fileStream << std::endl << number << SPACE << productName;
    }

    removeAll();
    return true;
}

bool ShoppingList::addProduct(const std::string &productName, int number) {
    if (number < 0) {
        return false;
    }

    if (isProductInShoppingList(productName)) {
        listOfProducts[productName] += number;
    }

    else {
        listOfProducts.insert(std::pair<std::string, int>(productName, number));
        numberOfProducts++;
    }

    numberOfItems += number;
    return true;
}

bool ShoppingList::removeProduct(const std::string &productName) {
    if (isProductInShoppingList(productName)) {
        numberOfItems -= listOfProducts[productName];
        numberOfProducts--;
        listOfProducts.erase(productName);
        return true;
    }
    return false;
}

bool ShoppingList::alterProductQuantity(const std::string &productName, int number) {
    if (isProductInShoppingList(productName)) {
        if (0 < number) {
            int difference = listOfProducts[productName] - number;
            listOfProducts[productName] = number;
            numberOfItems -= difference;
            return true;
        }
    }
    return false;
}

bool ShoppingList::removeAll() {
    if (numberOfProducts == 0) {
        return false;
    }

    listOfProducts.clear();
    numberOfProducts = 0;
    numberOfItems = 0;
    return true;
}

bool ShoppingList::isProductInShoppingList(const std::string &productName) {
    if (listOfProducts.find(productName) == listOfProducts.end()) {
        return false;
    }
    return true;
}

int ShoppingList::getProductQuantity(const std::string &productName) {
    if (!isProductInShoppingList(productName)) {
        return 0;
    }
    return listOfProducts[productName];
}

void ShoppingList::setName(const std::string &newName) {
    name = newName;
}

ShoppingList::~ShoppingList() {
    listOfProducts.clear();
}
