//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_ARAB3_H
#define GAME5_ARAB3_H

#include "../Ability.h"
#include "../../../common.h"

class ArAb3 : public Ability
{
public:
    ArAb3();
    ~ArAb3() override = default;
public:
    void activate(GameplayData&) override;
};


#endif //GAME5_ARAB3_H
