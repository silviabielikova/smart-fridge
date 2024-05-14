#pragma once

#include <string>

//abstract (is not an item), holds its name and category
class Product {
    std::string name;
    int category = 0;

    public:
        Product() = default; //empty name and category 0

        Product(const std::string &inputName, int inputCategory);

        Product(Product &&inputProduct); //moves name and sets category

        const std::string &getName() const { return name; }

        int getCategory() const { return category; }
};