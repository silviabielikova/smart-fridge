#pragma once

#include <map>
#include <set>
#include <vector>
#include <chrono>
#include <iomanip>

#include "5_Item.h"
#include "3_ProductDatabase.h"
#include "4_ShoppingList.h"

const std::string DEFAULT_PRODUCTS_FILE = "default_products.txt";
const std::string DEFAULT_ESSENTIALS_FILE = "default_essentials.txt";

struct Less {
    bool operator()(Item *first, Item *second) const {
        if (first->getExpirationDate() < second->getExpirationDate()) {
            return true;
        }
        return first->getId() < second->getId();
    }
};

Date getTodaysDate(); //returns today's date in Date object

//contains items, shopping lists, products marked essential and product database
class Fridge {
    std::string name = "My fridge";
    ProductDatabase productDatabase;
    std::map<std::string, std::set<Item*, Less>> listOfItems; //contents of the fridge
    std::map<std::string, ShoppingList*> shoppingLists; //all shopping lists
    std::string defaultShoppingList; //shopping list to add essential products to
    std::map<std::string, int> essentials; //essential products with their lowest acceptable quantities (limits)

    int itemIdGenerator = 0; //generates new IDs for added items

    int numberOfItems = 0;
    int numberOfProducts = 0;
    int numberOfShoppingLists = 0;

    const int SOON_TO_EXPIRE_CONST = 3; //defines the "soon" in "soon to expire"

    private:
        void importDefaultProductDatabase(); //product database for a brand-new fridge

        bool setDefaultEssentials(); //loads essentials from file, updates shopping list with essentials to stock up a new fridge

        bool isProductInDatabase(const std::string &productName);

        bool doesShoppingListExist(const std::string &productName);

        bool isProductInFridge(const std::string &productName);

        bool isProductInEssentials(const std::string &productName);

        void checkIfNeedsToStockUp(const std::string &name); //if quantity of an essential product drops below its limit, product is added to the default shopping list (quantity is calculated)

        void removeAllFromFridge(); //clears the fridge, removes all of its contents, frees memory

        void removeAllShoppingLists(); //clears and removes all the shopping lists, frees memory

        void removeAllEssentials(); //clears essentials, does not change the shopping lists


    public:
        Fridge();

        Fridge(const std::string &name);

        ~Fridge(); //clears everything, frees all the memory


        int getProductQuantity(const std::string &productName); //returns quantity of said product in the fridge

        bool insertItem(const std::string &productName, Date expDate, int number = 1); //return false if product not in database, number below 0 or date invalid

        Date pickOutItem(const std::string &productName); //returns Date of picked out item, it is always the earliest possible expiration date of said product

        int importToFridgeFromFile(const std::string &fileName); //returns number of imported items, ignores incorrect

        int importToDatabaseFromFile(const std::string &fileName); //returns number of imported products, ignores incorrect


        bool createNewShoppingList(const std::string &slName); //creates new SL, allocates memory

        bool setDefaultShoppingList(const std::string &slName);

        bool addToShoppingList(const std::string &slName, const std::string &productName, int number = 1);

        bool addToShoppingList(const std::string &productName, int number = 1); //adds to default shopping list

        bool removeFromShoppingList(const std::string &slName, const std::string &productName);

        int getProductQuantityInShoppingList(const std::string &slName, const std::string &productName);

        bool exportShoppingList(const std::string &slName); //exports shopping list and clears its contents, relies on compliance (you will eventually buy what you have in the SL)

        int getNumberOfProductsInShoppingList(const std::string &slName); //returns -1 if shopping list with entered name does not exist

        bool addProductToDatabase(const std::string &productName, int category); //returns false if category invalid

        bool removeProductFromDatabase(const std::string &productName);


        bool addToEssentials(const std::string &productName, int quantity); //adds product to essentials, saves its limit and immediately adds required quantity to shopping list

        bool removeFromEssentials(const std::string &productName); //removes from essentials, does not change the shopping lists


        std::vector<Item *> getSoonToExpire(); //returns items with expiration dates earlier than <current date + SOON_TO_EXPIRE_CONST>

        std::vector<Item *> getSoonToExpire(int days); //returns items with expiration dates earlier than <current date + days>

        std::map<std::string, std::set<Item *, Less>> *getAll(); //returns all contents of the fridge
    };