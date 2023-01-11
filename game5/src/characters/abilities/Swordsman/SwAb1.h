//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_SWAB1_H
#define GAME5_SWAB1_H

#include "../Ability.h"
#include "../../../common.h"

class SwAb1 : public Ability
{
public:
    SwAb1();
    ~SwAb1() override = default;
public:
    void activate(GameplayData&) override;
};


#endif //GAME5_SWAB1_H
