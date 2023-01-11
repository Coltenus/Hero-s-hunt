//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_PALAB3_H
#define GAME5_PALAB3_H

#include "../Ability.h"
#include "../../../common.h"

class PalAb3 : public Ability
{
public:
    PalAb3();
    ~PalAb3() override = default;
public:
    void activate(GameplayData&) override;
};


#endif //GAME5_PALAB3_H
