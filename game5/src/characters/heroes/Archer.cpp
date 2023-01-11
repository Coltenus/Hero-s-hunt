//
// Created by colte on 28.12.2022.
//

#include <cstdlib>
#include "Archer.h"

Archer::Archer() : Hero()
{
    minNDMG = 5;
    mcN = 30;
    nA = "Triple shot";
    minHDMG = 20;
    mcH = 0;
    hA = "Accurate shot";
    spValue = 1;
    sp = "Invisibility";
    maxHP = 80;
    hp = 80;
    gold = 0;
    evasion = 26;
    buffsDur = 0;
    charType = 2;
}

Archer::~Archer()
{
    for(auto& el: items)
        delete el;
    items.clear();
}

void Archer::Attack(GameplayData &gd)
{
    static short shotCount;
    static int dmg;
    dmg = 0;
    shotCount = 3;
    if (ability->numOfAb == 2 && ability->statusDur > 0) shotCount *= 2;
    for(int i = 0; i < shotCount; i++)
    {
        if (rand() % 100 + 1 > mcN)
        {
            dmg += rand() % 6 + minNDMG;
        }
    }
    gd.enemy.hp -= dmg;
}

void Archer::HeavyAttack(GameplayData &gd)
{
    static int dmg;
    dmg = rand() % 4 + minHDMG;
    if (ability->numOfAb == 2 && ability->statusDur > 0) dmg *= 2;
    gd.enemy.hp -= dmg;
}

void Archer::Special(GameplayData &gd)
{
    if (ability->numOfAb == 2 && ability->statusDur > 0)
    {
        gd.hero.buffDur = spValue * 2;
    }
    else
    {
        gd.hero.buffDur = spValue;
    }
}

void Archer::setAbility(Ability* ab)
{
    ability = ab;
}

void Archer::useAbility(GameplayData &gd)
{
    ability->activate(gd);
}