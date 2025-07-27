#pragma once

#include "product.h"
#include <vector>
#include <mutex>
#include <optional>

class ProductManager {
public:
    Product addProduct(const std::string& name, int price);
    std::vector<Product> getAllProducts();
    std::optional<Product> getProductById(int id);	
    bool updateProduct(int id, string& name, int price);    
    bool deleteProduct(int id);

    std::mutex mutex_;
    int nextId_ = 1;
private:
    std::vector<Product> products_;
    
};
