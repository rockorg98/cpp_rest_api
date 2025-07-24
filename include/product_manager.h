#pragma once

#include "product.h"
#include <vector>
#include <mutex>
#include <optional>

class ProductManager {
public:
    Product addProduct(const std::string& name, int price);
    std::vector<Product> getAllProducts();

    std::mutex mutex_;
    int nextId_ = 1;
private:
    std::vector<Product> products_;
    
};
