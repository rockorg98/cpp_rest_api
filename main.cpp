#include "crow.h"
#include "vector"
#include "mutex"
#include "string"
#include "product_manager.h"
#include "product.h"
using namespace std;

int main() {
    crow::SimpleApp app;  
	
    ProductManager productManager;
    // GET /hello
    CROW_ROUTE(app, "/hello")([] {
        crow::json::wvalue response;
        response["message"] = "Hello, Rishabh!";
        return response;
    });


    CROW_ROUTE(app, "/products")([&productManager] 
    {
        crow::json::wvalue response;
	auto productList = productManager.getAllProducts();
	
	std::lock_guard lg(productManager.mutex_);
	for(int i = 0 ; i < productList.size();i++)
	{
	    response["products"][i]["id"] = productList[i].m_nId;
       	    response["products"][i]["name"] = productList[i].m_sName;
            response["products"][i]["price"] = productList[i].m_nPrice;
	}
	return response;
    });  
    
    CROW_ROUTE(app,"/add_products").methods("POST"_method)
    ([&productManager](const crow::request& req){
        auto body = crow::json::load(req.body);
	
 	if (!body)
            return crow::response(400, "Invalid JSON");

        if (!body.has("name") || !body.has("price"))
            return crow::response(400, "Missing name or price");
	
	std::cout << "Received POST request\n";
	std::string name = body["name"].s();
	int price = body["price"].i();

			
	{	
		std::cout << "Inside Scope\n";
		productManager.addProduct(name,price);
	}	
	std::cout << "Product added Received POST request\n";
	crow::json::wvalue response;
    	response["message"] = "Added";
    	return crow::response(201, response);
    });
    app.port(8080).multithreaded().run();
}

