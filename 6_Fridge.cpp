#include "6_Fridge.h"

Date getTodaysDate() {
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::stringstream dateStream;
    dateStream << std::put_time(localtime(&now), "%d/%m/%Y");

    Date today;
    dateStream >> today;

    return today;
}


Fridge::Fridge() {
    importDefaultProductDatabase();
    createNewShoppingList("Groceries");
    setDefaultShoppingList("Groceries");
    setDefaultEssentials();
}

Fridge::Fridge(const std::string &newName) : Fridge() {
    this->name = newName;
}

Fridge::~Fridge() {
    removeAllFromFridge();
    removeAllShoppingLists();
    removeAllEssentials();
}

bool Fridge::insertItem(const std::string &productName, Date expDate, int number) {
    if (!isProductInDatabase(productName)) {
        return false;
    }

    if (expDate.isEmpty()) {
        return false;
    }

    if (number < 1) {
        return false;
    }

    for (int i = 0; i < number; i++) {
        Item *newItemPtr = new Item(productName, expDate, itemIdGenerator++);
        if (isProductInFridge(productName)) {
            listOfItems[productName].insert(newItemPtr);
        } else {
            std::set<Item *, Less> newSet;
            newSet.insert(newItemPtr);
            listOfItems.insert(std::pair<std::string, std::set<Item *, Less>>(productName, newSet));
            numberOfProducts++;
        }
    }

    numberOfItems += number;

    return true;
}

Date Fridge::pickOutItem(const std::string &productName) {
    if (!isProductInFridge(productName)) {
        return {};
    }

    auto chosen = listOfItems[productName].begin();
    Item* itemPtr = *chosen;
    Date outputDate = itemPtr->getExpirationDate();
    listOfItems[productName].erase(chosen);

    if (listOfItems[productName].empty()) {
        listOfItems.erase(productName);
        numberOfProducts--;
    }

    delete itemPtr;
    numberOfItems--;

    checkIfNeedsToStockUp(productName);

    return outputDate;
}

std::vector<Item *> Fridge::getSoonToExpire() {
    return getSoonToExpire(SOON_TO_EXPIRE_CONST);
}

std::vector<Item *> Fridge::getSoonToExpire(int days) {
    Date today = getTodaysDate();
    Date soonToExpireDate = today + days;

    std::vector<Item *> output;

    auto current = listOfItems.begin();
    while (current != listOfItems.end()) {
        auto items = current->second;
        for (Item *item: items) {
            if (soonToExpireDate < item->getExpirationDate()) {
                break;
            }
            output.push_back(item);
        }
        current++;
    }
    return output;
}

std::map<std::string, std::set<Item *, Less>> *Fridge::getAll() {
    return &listOfItems;
}

void Fridge::removeAllFromFridge() {
    for (auto &element: listOfItems) {
        auto itemSet = element.second;
        for (auto item: itemSet) {
            delete item;
        }
        itemSet.clear();
    }
    listOfItems.clear();
}

int Fridge::importToFridgeFromFile(const std::string &fileName) {
    std::ifstream fileStream;
    fileStream.open(fileName);
    if (!fileStream) {
        return 0;
    }

    int cnt = 0;

    int number;
    Date expDate;
    std::string productName;

    while (!fileStream.eof()) {
        if (fileStream >> number >> expDate) {
            std::getline(fileStream, productName);
            productName = productName.substr(1);
            if (insertItem(productName, expDate, number)) {
                cnt += number;
            }
        }
    }
    return cnt;
}

bool Fridge::createNewShoppingList(const std::string &slName) {
    if (!doesShoppingListExist(slName)) {
        ShoppingList *newSLPtr = new ShoppingList(slName);
        shoppingLists.insert(std::pair<std::string, ShoppingList *>(slName, newSLPtr));
        numberOfShoppingLists++;
        return true;
    }
    return false;
}

bool Fridge::setDefaultShoppingList(const std::string &slName) {
    if (doesShoppingListExist(slName)) {
        defaultShoppingList = slName;
        return true;
    }
    return false;

}

bool Fridge::addToShoppingList(const std::string &slName, const std::string &productName, int number) {
    if (doesShoppingListExist(slName)) {
        if (isProductInDatabase(productName)) {
            return shoppingLists[slName]->addProduct(productName, number);
        }
        return false;
    }
    return false;
}

bool Fridge::addToShoppingList(const std::string &productName, int number) {
    if (isProductInDatabase(productName)) {
        return shoppingLists[defaultShoppingList]->addProduct(productName, number);
    }
    return false;
}

bool Fridge::removeFromShoppingList(const std::string &slName, const std::string &productName) {
    if (doesShoppingListExist(slName)) {
        return shoppingLists[slName]->removeProduct(productName);
    }
    return false;
}

bool Fridge::exportShoppingList(const std::string &slName) {
    if (doesShoppingListExist(slName)) {
        std::string fileName = slName + "_shopping_list.txt";
        return shoppingLists[slName]->exportToFile(fileName);
    }
    return false;
}

bool Fridge::addProductToDatabase(const std::string &productName, int category) {
    return productDatabase.addProduct(productName, category);
}

bool Fridge::removeProductFromDatabase(const std::string &productName) {
    return productDatabase.removeProduct(productName);
}

bool Fridge::doesShoppingListExist(const std::string &SLname) {
    if (shoppingLists.find(SLname) != shoppingLists.end()) {
        return true;
    }
    return false;
}

bool Fridge::isProductInFridge(const std::string &productName) {
    if (listOfItems.find(productName) != listOfItems.end()) {
        return true;
    }
    return false;
}

int Fridge::getProductQuantity(const std::string &productName) {
    if (isProductInFridge(productName)) {
        return listOfItems[productName].size();
    }
    return 0;
}

bool Fridge::isProductInDatabase(const std::string &productName) {
    return productDatabase.isProductInDatabase(productName);
}

void Fridge::importDefaultProductDatabase() {
    importToDatabaseFromFile(DEFAULT_PRODUCTS_FILE);
}

bool Fridge::setDefaultEssentials() {
    std::ifstream fileStream;
    fileStream.open(DEFAULT_ESSENTIALS_FILE);
    if (!fileStream) {
        return false;
    }

    int quantity;
    std::string productName;

    while (!fileStream.eof()) {
        if (fileStream >> quantity) {
            std::getline(fileStream, productName);
            productName = productName.substr(1);

            addToEssentials(productName, quantity);
        }
    }
    return true;

}

int Fridge::importToDatabaseFromFile(const std::string &fileName) {
    return productDatabase.importProductsFromFile(fileName);
}

void Fridge::removeAllShoppingLists() {
    for (auto &element: shoppingLists) {
        delete element.second;
    }
    shoppingLists.clear();
}

int Fridge::getNumberOfProductsInShoppingList(const std::string &slName) {
    if (doesShoppingListExist(slName)) {
        return shoppingLists[slName]->getNumberOfProducts();
    }
    return -1;
}

bool Fridge::addToEssentials(const std::string &productName, int quantity) {
    if (!isProductInDatabase(productName)) {
        return false;
    }

    if (quantity < 1) {
        return false;
    }

    essentials.insert(std::pair<std::string, int>(productName, quantity));
    checkIfNeedsToStockUp(productName);
    return true;
}

bool Fridge::removeFromEssentials(const std::string &productName) {
    if (essentials.find(productName) == essentials.end()) {
        return false;
    }

    essentials.erase(productName);
    return true;
}

void Fridge::removeAllEssentials() {
    essentials.clear();
}

bool Fridge::isProductInEssentials(const std::string &productName) {
    if (essentials.find(productName) == essentials.end()) {
        return false;
    }
    return true;
}

int Fridge::getProductQuantityInShoppingList(const std::string &slName, const std::string &productName) {
    if (!doesShoppingListExist(slName)) {
        return -1;
    }

    return shoppingLists[slName]->getProductQuantity(productName);
}

void Fridge::checkIfNeedsToStockUp(const std::string &productName) {
    if (isProductInEssentials(productName)) {
        int quantityLimit = essentials[productName];
        int currentQuantity = getProductQuantity(productName);
        if (currentQuantity < quantityLimit) {
            addToShoppingList(productName, quantityLimit - currentQuantity);
        }
    }
}
