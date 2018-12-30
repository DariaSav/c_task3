#include <iostream>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>

#include "Shop.h"



void IShop::printInfo(){

	std::lock_guard<std::mutex> lockp(printed);

	if (prods.size()){

	std::cout << name << " sells:" << std::endl;

	for (std::pair<std::string, float> element : prods){
		std::cout << element.first << " by price " << element.second << " $" << std::endl;
	}
}
	else std::cout << name << " sells no flowers" << std::endl;

 


//	for (const auto& prod : prods){
		//auto prod = prod_w.lock();
//		if (prod->sell) std::cout << " " << prod->GetPrice() << " " << prod->GetName() << name << std::endl;
 
//};

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

class Rose: public IProduct{

public:
 
Rose(float p): IProduct(p) {name = "Rose";};
Rose(Rose* r): IProduct(r) {name = "Rose";};

//std::string name = "Car";

};

class Tulip: public IProduct{

public:

Tulip(float p): IProduct(p) {name = "Tulip";};
Tulip(Tulip* t): IProduct(t) {name = "Tulip";};

//std::string name = "Elephant";

};

class Camomile: public IProduct{  

public: 

Camomile(float p): IProduct(p) {name = "Camomile";};
Camomile(Camomile* c): IProduct(c) {name = "Camomile";};

//std::string name = "Elephant";

};




int main() { 

	//IShop shop1("Flowers&co");
	//std::shared_ptr<IShop> flower_and_co = std::make_shared<IShop>(shop1);
	//IShop shop2("Golden Garden");
	//std::shared_ptr<IShop> golden_garden = std::make_shared<IShop>(shop2);
	//IShop shop3("Green Land");
	//std::shared_ptr<IShop> green_land = std::make_shared<IShop>(shop3);


	std::shared_ptr<IShop> flower_and_co = std::make_shared<IShop>("Flowers&co");
	std::shared_ptr<IShop> golden_garden = std::make_shared<IShop>("Golden Garden");
	std::shared_ptr<IShop> green_land = std::make_shared<IShop>("Green Land");


	std::thread product_thread([&]() {
        Rose rose(15);
        rose.StartSales();
        rose.Attach(flower_and_co);
        rose.Attach(golden_garden);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        Tulip tulip(13);
        tulip.StartSales();
        tulip.Attach(green_land);
        tulip.Attach(golden_garden);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        rose.Detach(golden_garden);
        tulip.Detach(green_land);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        tulip.ChangePrice(12.99);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        rose.ChangePrice(16);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        Camomile camomile(45);
        camomile.Attach(flower_and_co);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    });

    std::thread shop_thread([&]() {
        for(int i = 0; i < 5; i++) {
            flower_and_co->printInfo();
            golden_garden->printInfo();
            green_land->printInfo();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        flower_and_co.reset();
        golden_garden->printInfo();
        green_land->printInfo();

        golden_garden.reset();
        green_land->printInfo();
    });

    product_thread.join();
    shop_thread.join();
}

