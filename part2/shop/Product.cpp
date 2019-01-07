#include <iostream>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>
#include <list>
#include <unordered_map>

#include "header.h"

void IProduct::Attach(std::weak_ptr<IShop> shop_w){

		//std::cout << "attach" << std::endl;
		std::lock_guard<std::mutex> lock(changed);
		auto shop = shop_w.lock();
		//std::lock_guard<std::mutex> lockc(shop->changed);
		

		if (shop != nullptr) {
			if (sell) shop->Sell(name, price);
			shops.push_back(shop_w);
		}
	};

void IProduct::Detach(const std::weak_ptr<IShop> shop_w){


		std::lock_guard<std::mutex> lock(changed);
		auto shop = shop_w.lock();

		if (shop != nullptr) shop->NoSell(name);
		

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


void IProduct::ChangePrice(float p){

		//std::cout << "changeprice" << std::endl;
		std::lock_guard<std::mutex> lock(changed);

		price = p;
		if (sell)
		for (auto & shop_w : shops){
			auto shop = shop_w.lock();
			if (shop != nullptr) shop->ChangePrice(name, price);	
		}

	

	};


void IProduct::StartSales(){

		//std::cout << "startsales" << std::endl;
		std::lock_guard<std::mutex> lock(changed);

		if (!closed){

			sell = true;
			for (auto & shop_w : shops){
				auto shop = shop_w.lock();
				if (shop != nullptr) shop->Sell(name, price);//prods.insert({name, price});	
			}
		}

	};

void IProduct::StopSales(){

		//std::cout << "stopsales" << std::endl;
		//std::lock_guard<std::mutex> lock(changed);

		sell = false;
		closed = true;
		std::list<std::weak_ptr<IShop>> iter_shops = std::list<std::weak_ptr<IShop>>(shops);
		for (const auto& shop_w : iter_shops){
			auto shop = shop_w.lock();
			if (shop != nullptr) this->Detach(shop_w);
	}

	};

float IProduct::GetPrice(){

		//std::cout << "getprice" << std::endl;

		return price;

	};

std::string IProduct::GetName(){

		//std::cout << "getname" << std::endl;

		return name;

	};


std::list<std::weak_ptr<IShop>> IProduct::GetShopsList(){

		//std::cout << "getname" << std::endl;

		return shops;

	};


