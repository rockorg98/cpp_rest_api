#include "../include/product_manager.h"

Product ProductManager::addProduct(const std::string& name, int price) {
    std::lock_guard<std::mutex> lock(mutex_);
    Product product{ nextId_++, name, price };
    products_.push_back(product);
    return product;
}

std::vector<Product> ProductManager::getAllProducts() {
    std::lock_guard<std::mutex> lock(mutex_);
    return products_;
}
