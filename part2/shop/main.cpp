#include <iostream>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>

#include "header.h"


int main() { 

	std::shared_ptr<IShop> flower_and_co = std::make_shared<IShop>("Flowers&co");
	std::shared_ptr<IShop> golden_garden = std::make_shared<IShop>("Golden Garden");
	std::shared_ptr<IShop> green_land = std::make_shared<IShop>("Green Land");


	std::thread flower_thread([&]() { 
        Rose rose(1);
	Tulip tulip(2);
	Camomile camomile(3);
	
	std::this_thread::sleep_for(std::chrono::milliseconds(2));

	rose.Attach(flower_and_co);
        rose.Attach(golden_garden);
        rose.StartSales();
	rose.Attach(green_land);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        
        tulip.StartSales();

	std::this_thread::sleep_for(std::chrono::milliseconds(1));

        tulip.Attach(green_land);
	rose.ChangePrice(16);
	rose.Detach(golden_garden);
        tulip.Attach(golden_garden);
	camomile.Attach(golden_garden);
	camomile.StartSales();
	tulip.StopSales();

        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        camomile.Attach(flower_and_co);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        tulip.Detach(green_land);
	tulip.ChangePrice(7);
	rose.Detach(green_land);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

	camomile.ChangePrice(42);
	camomile.Detach(flower_and_co);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    });

    std::thread shop_thread([&]() {

        flower_and_co->printInfo();
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
        golden_garden->printInfo();
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
        green_land->printInfo();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        flower_and_co.reset();
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
        golden_garden->printInfo();
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
        green_land->printInfo();
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
        golden_garden.reset();
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
        green_land->printInfo();
    });

    flower_thread.join();
    shop_thread.join();
}

