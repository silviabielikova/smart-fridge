#pragma once

#include "1_Date.h"

//distinct physical object, characterized by its product name, expiration date and ID, connected to product through product database
class Item {
    std::string productName;
    Date expirationDate;
    int id = 0;

    public:
        Item() = default;  //empty name, empty date and id = 0

        Item(const std::string &product, Date expDate, int id);

        const std::string &getProductName() const { return productName; }

        Date getExpirationDate() const { return expirationDate; }

        int getId() const { return id; }
};