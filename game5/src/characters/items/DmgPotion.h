//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_DMGPOTION_H
#define GAME5_DMGPOTION_H

#include "Item.h"
#include "../../common.h"

class DmgPotion : public Item
{
public:
    DmgPotion(short);
    ~DmgPotion() override = default;
    void activate(GameplayData&) override;
};


#endif //GAME5_DMGPOTION_H
