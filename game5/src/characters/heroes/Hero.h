//
// Created by colte on 26.12.2022.
//

#ifndef GAME5_HERO_H
#define GAME5_HERO_H

#include <vector>
#include <string>
#include "../../common.h"
#include "../abilities/Ability.h"
#include "../items/Item.h"


class Hero
{
public:
    Hero();
    virtual ~Hero() = 0;
public:
    virtual void Attack(GameplayData&) = 0;
    virtual void HeavyAttack(GameplayData&) = 0;
    virtual void Special(GameplayData&) = 0;
    virtual void setAbility(Ability*) = 0;
    virtual void useAbility(GameplayData&) = 0;
    void setItem(Item*);
    void useItem(GameplayData&, short);
    void clearSlot(short);
    short findFreeSlot();
    void GetData(GameplayData&);
    void SetData(GameplayData&);
    void SetData(RewardStats&);
public:
    Ability *ability;
    std::vector<Item*> items;
    std::string nA, hA, sp;
    short maxHP, hp, block, evasion, buffsDur;
    short minNDMG, mcN;
    short minHDMG, mcH;
    short spValue;
    unsigned short gold;
    short charType;
    short slotN;
};


#endif //GAME5_HERO_H
