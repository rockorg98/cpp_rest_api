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


    CROW_ROUTE(app, "/product")([&productManager] 
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
    

    CROW_ROUTE(app, "/product/<int>").methods("GET"_method)([&productManager](int id) 
    {
	auto productOpt = productManager.getProductById(id);
	if (!productOpt.has_value()) {
        	return crow::response(404, "Product not found");
    	}
	const auto& product = productOpt.value();
        crow::json::wvalue res;
        res["id"] = product.m_nId;
        res["name"] = product.m_sName;
        res["price"] = product.m_nPrice;
        return crow::response{res};

    });  
    


    CROW_ROUTE(app,"/add_product").methods("POST"_method)
    ([&productManager](const crow::request& req){
        auto body = crow::json::load(req.body);
	
	if ( (!body) || 
	      !body.has("name") || 
	      !body.has("price") ||
	      (body["name"].t() != crow::json::type::String) || 
	      (body["price"].t() != crow::json::type::Number) )
	{
		return crow::response(400, "Incorrect JSON Input");
	}
            
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

    CROW_ROUTE(app,"/update_product/<int>").methods("PUT"_method)
    ([&productManager](const crow::request& req,int id){
        auto body = crow::json::load(req.body);
	
        if ( (!body) || 
	      !body.has("name") || 
	      !body.has("price") ||
	      (body["name"].t() != crow::json::type::String) || 
	      (body["price"].t() != crow::json::type::Number) )
	{
		return crow::response(400, "Incorrect JSON Input");
	}
    	
	std::string name = body["name"].s();
	int price = body["price"].i();
	
	if (name.empty() || price < 0) 
	{
    		return crow::response(400, "Validation failed");
	}
	
	bool updated = productManager.updateProduct(id,name,price);	
		
	if (!updated)
		return crow::response(400,"Unable to Update");
	else
	{
    		return crow::response(201,"PUT request successfull");
	}
	
    });
	
    CROW_ROUTE(app,"/product/<int>").methods("DELETE"_method)
    ([&productManager](int id){
	bool deleted = productManager.deleteProduct(id);
    	if (!deleted) 
	{
        	return crow::response(404, "Product not found");
    	}

    	return crow::response(200, "Product deleted successfully");
    });
	
    app.route_dynamic("/*").methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method)
	([](const crow::request& /*req*/) 
	{
    		return crow::response(404, "Route not found");
	});

    app.port(8080).multithreaded().run();
}

