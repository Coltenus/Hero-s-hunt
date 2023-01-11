//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_SWAB2_H
#define GAME5_SWAB2_H

#include "../Ability.h"
#include "../../../common.h"

class SwAb2 : public Ability
{
public:
    SwAb2();
    ~SwAb2() override = default;
public:
    void activate(GameplayData&) override;
};


#endif //GAME5_SWAB2_H
