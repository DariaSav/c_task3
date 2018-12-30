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

mutable std::mutex printed;
mutable std::mutex changed;

std::string name = "general shop";
std::unordered_map<std::string, float> prods;

IShop(const std::string s): name(s) {};

void printInfo();

void ChangePrice(const std::string s, float p);
void Sell(const std::string s, float p);
void NoSell(const std::string s);

//IShop(const IShop& sh){

//	name = sh.name;
//	prods = std::unordered_map<std::string, float>(sh.prods);
//	printed = std::mutex(sh.printed);
//	changed = std::mutex(sh.changed);
	

//}/

~IShop(){

	std::cout << "Shop " << name << " closed" << std::endl;

};


};


class IProduct{

public:

	

	float price;
	std::string name = "general item";
	bool sell = false;
	bool closed = false;
	std::list<std::weak_ptr<IShop>> shops;

	IProduct(const float &p): price(p) {};

	IProduct(IProduct* pr){

		price = pr->price;
		name = pr->name;
		sell = pr->sell;
		closed = pr->closed;
		shops = std::list<std::weak_ptr<IShop>>(pr->shops);

	};

	virtual void Attach(std::weak_ptr<IShop> shop_w){

		//std::cout << "attach" << std::endl;
		auto shop = shop_w.lock();

		if (shop != nullptr) {
			if (sell) shop->Sell(name, price);//prods.insert({name, price});
			shops.push_back(shop_w);
		}
	};

	virtual void Detach(const std::weak_ptr<IShop> shop_w){

	//	std::cout << "detach" << std::endl;
		auto shop = shop_w.lock();

		if (shop != nullptr) shop->NoSell(name);//prods.erase(name);
		//shops.remove(shop_w);
		//std::cout << "detach2" << std::endl;

		//std::weak_ptr<IProduct> prod = weak_from_this();

	//	shop->prods.remove(std::make_weak<IProduct>(this));
	//	shops.remove(shop);
		
		//for (std::pair<std::string, float> element : shop->prods){
			
		//}

		

		for (auto iter=shops.begin(); iter != shops.end(); iter++) {
            		auto track_shop_ptr = (*iter).lock();
            		if (track_shop_ptr != nullptr) {
                		if (shop == track_shop_ptr) {
					//std::cout << "trytoerase" << std::endl;
                    			shops.erase(iter);
					//std::cout << "erase" << std::endl;
                    			break;
				}
			}
		}



	};

	//virtual void UpdatePrice(){

	//	if (sell)
	//	for (const auto& shop : shops){
			


	//};


	virtual float GetPrice(){

		//std::cout << "getprice" << std::endl;

		return price;

	};

	virtual void ChangePrice(float p){

		//std::cout << "changeprice" << std::endl;

		price = p;
		if (sell)
		for (auto & shop_w : shops){
			auto shop = shop_w.lock();
			if (shop != nullptr) shop->ChangePrice(name, price);	
		}

	

	};



	virtual std::string GetName(){

		//std::cout << "getname" << std::endl;

		return name;

	};

	virtual void StartSales(){

		//std::cout << "startsales" << std::endl;

		if (!closed){

			sell = true;
			for (auto & shop_w : shops){
				auto shop = shop_w.lock();
				if (shop != nullptr) shop->Sell(name, price);//prods.insert({name, price});	
			}
		}

	};

	virtual void StopSales(){

		//std::cout << "stopsales" << std::endl;

		sell = false;
		closed = true;
		std::list<std::weak_ptr<IShop>> iter_shops = std::list<std::weak_ptr<IShop>>(shops);
		for (const auto& shop_w : iter_shops){
			auto shop = shop_w.lock();
			if (shop != nullptr) this->Detach(shop_w);
	}

	};


	~IProduct(){

		StopSales();

	};




};
