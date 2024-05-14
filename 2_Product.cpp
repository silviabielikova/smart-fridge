#include "2_Product.h"


Product::Product(const std::string &inputName, int inputCategory)
    : name(inputName), category(inputCategory) {
}

Product::Product(Product &&inputProduct)
    : name(std::move(inputProduct.name)), category(inputProduct.category) {
    inputProduct.category = 0;
}