//
// Created by colte on 26.12.2022.
//

#ifndef GAME5_ABILITY_H
#define GAME5_ABILITY_H

#include "../../common.h"
#include <string>

class Ability
{
public:
    short abilityVal, addAbilityVal;
    unsigned short curDelay, maxDelay, numOfAb, statusDur;
    std::string abTitle;
public:
    Ability();
    virtual ~Ability() = default;
public:
    virtual void activate(GameplayData&) = 0;
};


#endif //GAME5_ABILITY_H
