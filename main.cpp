#include "crow.h"
#include "vector"
#include "mutex"
#include "string"
using namespace std;

struct product
{
    public:
	int m_nId;
	std::string m_sName;
	int m_nPrice;
	
    product(int id,std::string name,int price):m_nId(id),m_sName(name),m_nPrice(price){
    }
};

vector<product> vProdList;
std::mutex mtx;

int next_id = 0;

int main() {
    crow::SimpleApp app;  

    // GET /hello
    CROW_ROUTE(app, "/hello")([] {
        crow::json::wvalue response;
        response["message"] = "Hello, Rishabh!";
        return response;
    });


    CROW_ROUTE(app, "/products")([] 
    {
        crow::json::wvalue response;
	
	std::lock_guard lg(mtx);
	for(int i = 0 ; i < vProdList.size();i++)
	{
	    response["products"][i]["id"] = vProdList[i].m_nId;
       	    response["products"][i]["name"] = vProdList[i].m_sName;
            response["products"][i]["price"] = vProdList[i].m_nPrice;
	}
	return response;
    });  
    
    CROW_ROUTE(app,"/add_products").methods("POST"_method)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body);
	
 	if (!body)
            return crow::response(400, "Invalid JSON");

        if (!body.has("name") || !body.has("price"))
            return crow::response(400, "Missing name or price");
	

	std::string name = body["name"].s();
	int price = body["price"].i();

			
	{	
		std::lock_guard ld(mtx);
		product temp(next_id++,name,price);
		vProdList.push_back(temp);
	}	
	crow::json::wvalue response;
    	response["message"] = "Added";
    	return crow::response(201, response);
    });
    app.port(8080).multithreaded().run();
}

