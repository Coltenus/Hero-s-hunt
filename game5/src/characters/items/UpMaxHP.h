//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_UPMAXHP_H
#define GAME5_UPMAXHP_H

#include "Item.h"
#include "../../common.h"

class UpMaxHP : public Item
{
public:
    UpMaxHP(short);
    ~UpMaxHP() override = default;
    void activate(GameplayData&) override;
};


#endif //GAME5_UPMAXHP_H
