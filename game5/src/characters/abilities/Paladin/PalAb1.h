//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_PALAB1_H
#define GAME5_PALAB1_H

#include "../Ability.h"
#include "../../../common.h"

class PalAb1 : public Ability
{
public:
    PalAb1();
    ~PalAb1() override = default;
public:
    void activate(GameplayData&) override;
};


#endif //GAME5_PALAB1_H
