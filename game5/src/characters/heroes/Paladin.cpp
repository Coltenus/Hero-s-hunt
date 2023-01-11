//
// Created by colte on 28.12.2022.
//

#include <cstdlib>
#include "Paladin.h"

Paladin::Paladin() : Hero()
{
    minNDMG = 20;
    mcN = 25;
    nA = "Sword swing";
    minHDMG = 14;
    mcH = 15;
    hA = "Shield attack";
    spValue = 15;
    sp = "Help from above";
    maxHP = 100;
    hp = 100;
    gold = 0;
    evasion = 10;
    buffsDur = 0;
    charType = 3;
}

Paladin::~Paladin()
{
    for(auto& el: items)
        delete el;
    items.clear();
}

void Paladin::Attack(GameplayData &gd)
{
    static int dmg;
    dmg = rand() % 5 + minNDMG;
    if (ability->numOfAb == 2 && ability->statusDur > 0)
    {
        dmg *= 2;
        gd.enemy.hp -= dmg;
    }
    else if (rand() % 100 + 1 > mcN)
    {
        gd.enemy.hp -= dmg;
    }
}

void Paladin::HeavyAttack(GameplayData &gd)
{
    static int dmg, bl;
    dmg = minHDMG;
    bl = (short)(minHDMG * 0.3);
    if (ability->numOfAb == 2 && ability->statusDur > 0)
    {
        dmg *= 2;
        gd.enemy.hp -= dmg;
        bl *= 2;
    }
    else if (rand() % 100 + 1 > mcH)
    {
        gd.enemy.hp -= dmg;
    }
    gd.hero.block += bl;
}

void Paladin::Special(GameplayData &gd)
{
    static int HP;
    HP = rand() % (spValue + 1);
    if (ability->numOfAb == 2 && ability->statusDur > 0)
    {
        HP = spValue * 2;
    }
    gd.hero.hp += HP;
    gd.hero.buffDur += 3;
}

void Paladin::setAbility(Ability* ab)
{
    ability = ab;
}

void Paladin::useAbility(GameplayData &gd)
{
    ability->activate(gd);
}