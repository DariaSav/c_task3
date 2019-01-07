// tests.cpp
//#include "whattotest.cpp"
#include <gtest/gtest.h>
#include "../shop/header.h"
 
TEST(CheckProduct, InitIProduct) { 
    IProduct product(16);
    ASSERT_EQ(16, product.GetPrice());
}

TEST(CheckProduct, InitRose) { 
    Rose rose(16);
    ASSERT_STREQ("Rose", rose.GetName().c_str());
    ASSERT_EQ(16, rose.GetPrice());
}

TEST(CheckProduct, ChangePrice) { 

    IProduct product(16);
    Rose rose(16);
    product.ChangePrice(10);
    rose.ChangePrice(9);

  //  ASSERT_STREQ("Rose", rose.GetName().c_str());
    ASSERT_EQ(10, product.GetPrice());
    ASSERT_EQ(9, rose.GetPrice());
}


TEST(CheckProduct, Attach) { 

    Tulip tulip(16);
    std::shared_ptr<IShop> shop = std::make_shared<IShop>("shop");

    tulip.StartSales();
    tulip.Attach(shop);

    for (const auto& shop_w : tulip.GetShopsList()){
        auto shop = shop_w.lock();
        ASSERT_STREQ("shop", shop->GetName().c_str());
    }

}


TEST(CheckProduct, Detach) { 

    Tulip tulip(16);
    std::shared_ptr<IShop> shop = std::make_shared<IShop>("shop");

    tulip.StartSales();
    tulip.Attach(shop);
    tulip.Detach(shop);

    ASSERT_EQ(0, tulip.GetShopsList().size());

}


TEST(CheckShop, Attach) { 

    Tulip tulip(16);
    Rose rose(10);
    std::shared_ptr<IShop> shop = std::make_shared<IShop>("shop");

    tulip.StartSales();
    tulip.Attach(shop);

    rose.StartSales();
    rose.Attach(shop);

    ASSERT_EQ(2, shop->GetProdsList().size());

}


TEST(CheckShop, StartSales) { 

    Tulip tulip(16);
    Rose rose(10);
    std::shared_ptr<IShop> shop = std::make_shared<IShop>("shop");

    tulip.StartSales();
    tulip.Attach(shop);

  //  rose.StartSales();
    rose.Attach(shop);

    ASSERT_EQ(1, shop->GetProdsList().size());

}

TEST(CheckShop, StopSales) { 

    Tulip tulip(16);
    Rose rose(10);
    std::shared_ptr<IShop> shop = std::make_shared<IShop>("shop");

    tulip.StartSales();
    tulip.Attach(shop);

    rose.StartSales();
    rose.Attach(shop);
    rose.StopSales();

    ASSERT_EQ(1, shop->GetProdsList().size());

}


 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
