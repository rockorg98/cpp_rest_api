#include "../include/product_manager.h"
#include<algorithm>
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

std::optional<Product> ProductManager::getProductById(int id)
{
	std::lock_guard<std::mutex> lock(mutex_);
	for(auto& i:products_)
	{
		if(i.m_nId == id) return i;
	}
	return std::nullopt;
}

bool ProductManager::updateProduct(int id,string& name,int price)
{
	std::lock_guard<std::mutex> lock(mutex_);
	for(auto& i:products_)
	{
		if(i.m_nId == id)
		{
			i.m_sName = name;
			i.m_nPrice = price;	
			return true;
		}
	}
	return false;
}

bool ProductManager::deleteProduct(int id)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = std::remove_if(products_.begin(), products_.end(),[id](const Product& p) { return p.m_nId == id; });
    if (it != products_.end()) {
        products_.erase(it, products_.end());
        return true;
    }
    return false;
}
