//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_ARAB2_H
#define GAME5_ARAB2_H

#include "../Ability.h"
#include "../../../common.h"

class ArAb2 : public Ability
{
public:
    ArAb2();
    ~ArAb2() override = default;
public:
    void activate(GameplayData&) override;
};


#endif //GAME5_ARAB2_H
