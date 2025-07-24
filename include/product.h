#pragma once
#include "string"
using namespace std;
struct Product
{
	public:
		int m_nId;
		std::string m_sName;
		int m_nPrice;

		Product(int id,std::string name,int price):m_nId(id),m_sName(name),m_nPrice(price)
		{
		}
};
