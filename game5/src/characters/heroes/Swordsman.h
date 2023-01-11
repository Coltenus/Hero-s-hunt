//
// Created by colte on 28.12.2022.
//

#ifndef GAME5_SWORDSMAN_H
#define GAME5_SWORDSMAN_H

#include "Hero.h"

class Swordsman : public Hero
{
public:
    Swordsman();
    ~Swordsman() override;
    void Attack(GameplayData&) override;
    void HeavyAttack(GameplayData&) override;
    void Special(GameplayData&) override;
    void setAbility(Ability*) override;
    void useAbility(GameplayData&) override;
};


#endif //GAME5_SWORDSMAN_H
