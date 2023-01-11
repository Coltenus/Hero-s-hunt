//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_HEALING_H
#define GAME5_HEALING_H

#include "Item.h"
#include "../../common.h"

class Healing : public Item
{
public:
    Healing(short);
    ~Healing() override = default;
    void activate(GameplayData&) override;
};


#endif //GAME5_HEALING_H
