#include "5_Item.h"

Item::Item(const std::string &product, Date expDate, int id)
        : productName(product), expirationDate(expDate), id(id) {
}