//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_SWAB3_H
#define GAME5_SWAB3_H

#include "../Ability.h"
#include "../../../common.h"

class SwAb3 : public Ability
{
public:
    SwAb3();
    ~SwAb3() override = default;
public:
    void activate(GameplayData&) override;
};


#endif //GAME5_SWAB3_H
