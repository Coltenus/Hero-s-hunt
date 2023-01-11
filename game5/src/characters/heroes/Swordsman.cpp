//
// Created by colte on 28.12.2022.
//

#include <cstdlib>
#include "Swordsman.h"

Swordsman::Swordsman() : Hero()
{
    minNDMG = 10;
    mcN = 20;
    nA = "Sword attack";
    minHDMG = 30;
    mcH = 35;
    hA = "Sword swing";
    spValue = 15;
    sp = "Block";
    maxHP = 100;
    hp = 100;
    gold = 0;
    evasion = 18;
    buffsDur = 0;
    charType = 1;
}

Swordsman::~Swordsman()
{
    for(auto& el: items)
        delete el;
    items.clear();
}

void Swordsman::Attack(GameplayData &gd)
{
    static short dmg;
    dmg = rand() % 10 + minNDMG;
    if (ability->numOfAb == 3 && ability->statusDur > 0)
    {
        gd.enemy.hp -= dmg;
    }
    else if (rand() % 100 + 1 > mcN)
    {
        if (ability->numOfAb == 2 && ability->statusDur > 0)
        {
            dmg *= 2;
        }
        gd.enemy.hp -= dmg;
    }
}

void Swordsman::HeavyAttack(GameplayData &gd)
{
    static short dmg;
    dmg = rand() % 10 + minHDMG;
    if (ability->numOfAb == 3 && ability->statusDur > 0)
    {
        gd.enemy.hp -= dmg;
    }
    else if (rand() % 100 + 1 > mcH)
    {
        if (ability->numOfAb == 2 && ability->statusDur > 0)
        {
            dmg *= 2;
        }
        gd.enemy.hp -= dmg;
    }
}

void Swordsman::Special(GameplayData &gd)
{
    gd.hero.block += spValue;
}

void Swordsman::setAbility(Ability* ab)
{
    ability = ab;
}

void Swordsman::useAbility(GameplayData &gd)
{
    ability->activate(gd);
}