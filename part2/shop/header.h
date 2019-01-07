#include <iostream>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>
#include <list>
#include <unordered_map>



class IProduct;

class IShop{

public:

mutable std::mutex changed;

std::string name = "General shop";
std::unordered_map<std::string, float> prods;

IShop(const std::string s): name(s) {};

void printInfo();

void ChangePrice(const std::string s, float p);
void Sell(const std::string s, float p);
void NoSell(const std::string s);

std::string GetName(); 
std::unordered_map<std::string, float> GetProdsList();

~IShop(){

	std::cout << "Shop " << name << " closed" << std::endl;

};


};


class IProduct{

public:

	mutable std::mutex changed;

	std::atomic<float> price;
	std::string name = "General item";
	std::atomic_bool sell;
	std::atomic_bool closed;
	std::list<std::weak_ptr<IShop>> shops;

	IProduct(const float &p): price(p), sell(false), closed(false) {};

	virtual void Attach(std::weak_ptr<IShop> shop_w);
	virtual void Detach(const std::weak_ptr<IShop> shop_w);
	virtual void ChangePrice(float p);
	virtual float GetPrice();
	virtual std::string GetName();
	virtual std::list<std::weak_ptr<IShop>> GetShopsList();
	virtual void StartSales();
	virtual void StopSales();

	~IProduct(){

		StopSales();

	};


};



class Rose: public IProduct{

public:
Rose(float p): IProduct(p) {name = "Rose";};

};

class Tulip: public IProduct{

public:
Tulip(float p): IProduct(p) {name = "Tulip";};

};


class Camomile: public IProduct{  

public: 
Camomile(float p): IProduct(p) {name = "Camomile";};

};
