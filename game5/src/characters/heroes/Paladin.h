//
// Created by colte on 28.12.2022.
//

#ifndef GAME5_PALADIN_H
#define GAME5_PALADIN_H

#include "Hero.h"

class Paladin : public Hero
{
public:
    Paladin();
    ~Paladin() override;
    void Attack(GameplayData&) override;
    void HeavyAttack(GameplayData&) override;
    void Special(GameplayData&) override;
    void setAbility(Ability*) override;
    void useAbility(GameplayData&) override;
};


#endif //GAME5_PALADIN_H
