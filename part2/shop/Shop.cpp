#include <iostream>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>

#include "header.h"

std::mutex printed;

 
void IShop::printInfo(){

	std::lock_guard<std::mutex> lockp(printed);

	if (prods.size()){

	std::cout << name << " sells:" << std::endl;

	for (std::pair<std::string, float> element : prods){
		std::cout << element.first << " by price " << element.second << " $" << std::endl;
	}
}
	else std::cout << name << " sells no flowers" << std::endl;

 

}; 




void IShop::ChangePrice(const std::string s, float price){

	std::lock_guard<std::mutex> lockp(printed);
	std::lock_guard<std::mutex> lockc(changed);   


	prods[s] = price;
	std::cout << "Price of " << s << " changed in shop " << name << " to " << price << "$" << std::endl;
 
  
} 

void IShop::Sell(const std::string s, float price){
  

	std::lock_guard<std::mutex> lockp(printed);
	std::lock_guard<std::mutex> lockc(changed);

	prods.insert({s, price});
	//std::cout << s << " startechanged in shop " << name << " to " << price << "$" << std::endl;
	std::cout << "Shop " << name << " started selling " << s << " by price " << price << "$" << std::endl;


}


void IShop::NoSell(const std::string s){

	std::lock_guard<std::mutex> lockp(printed);
	std::lock_guard<std::mutex> lockc(changed);

	prods.erase(s);
	std::cout << "Shop " << name << " stopped selling " << s << std::endl;


};


std::string IShop::GetName(){

		//std::cout << "getname" << std::endl;

		return name;

	};

std::unordered_map<std::string, float> IShop::GetProdsList(){

		//std::cout << "getname" << std::endl;

		return prods;

	};

