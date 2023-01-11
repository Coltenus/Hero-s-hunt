//
// Created by colte on 28.12.2022.
//

#ifndef GAME5_ARCHER_H
#define GAME5_ARCHER_H

#include "Hero.h"

class Archer : public Hero
{
public:
    Archer();
    ~Archer() override;
    void Attack(GameplayData&) override;
    void HeavyAttack(GameplayData&) override;
    void Special(GameplayData&) override;
    void setAbility(Ability*) override;
    void useAbility(GameplayData&) override;
};


#endif //GAME5_ARCHER_H
