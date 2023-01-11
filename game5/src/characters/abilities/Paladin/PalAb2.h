//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_PALAB2_H
#define GAME5_PALAB2_H

#include "../Ability.h"
#include "../../../common.h"

class PalAb2 : public Ability
{
public:
    PalAb2();
    ~PalAb2() override = default;
public:
    void activate(GameplayData&) override;
};


#endif //GAME5_PALAB2_H
