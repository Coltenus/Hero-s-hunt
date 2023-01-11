//
// Created by colte on 02.01.2023.
//

#ifndef GAME5_SHOP_H
#define GAME5_SHOP_H

#include "GameplayEvent.h"
#include <map>

class Shop : public GameplayEvent {
private:
    struct StatPrice {
        short stat, price;
    };
    std::map<short, StatPrice> shopItems;
    bool active;

public:
    Shop(Hero**, short);
    ~Shop();
    void Update() override;
    void Draw() override;
    bool IsDone() override;
};


#endif //GAME5_SHOP_H
