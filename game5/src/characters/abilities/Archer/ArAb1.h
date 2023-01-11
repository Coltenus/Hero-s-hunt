//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_ARAB1_H
#define GAME5_ARAB1_H

#include "../Ability.h"
#include "../../../common.h"

class ArAb1 : public Ability
{
public:
    ArAb1();
    ~ArAb1() override = default;
public:
    void activate(GameplayData&) override;
};


#endif //GAME5_ARAB1_H
