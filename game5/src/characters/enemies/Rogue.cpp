//
// Created by colte on 28.12.2022.
//

#include <cstdlib>
#include "Rogue.h"

Rogue::Rogue(unsigned short r)
{
    minNDMG = (short)(20 * (1 + 0.1 * (r - 1)));
    minHDMG = (short)(12 * (1 + 0.1 * (r - 1)));
    spValue = (short)(5 * (1 + 0.1 * (r - 1)));
    maxHP = (short)(75 * (1 + 0.1 * (r - 1)));
    hp = maxHP;
    rewGold = 8 + rand() % 5;
    modAt = 1;
    enemyType = 2;
    modInMoves = 0;
    buffSp = 0;
}

void Rogue::Attack(GameplayData &gd)
{
    static short dmg;
    dmg = modAt * (rand() % 5 + minNDMG);
    if (gd.hero.charType == 2 && gd.hero.numOfAb == 3 && gd.hero.statusDur > 0)
    {
        dmg /= 2;
    }
    if (gd.hero.charType == 3 && gd.hero.numOfAb == 1 && modInMoves > 0)
    {
        if (rand() % 100 + 1 > 65)
        {
            gd.hero.hp -= dmg;
        }
        else
        {
            gd.enemy.hp -= dmg;
        }
    }
    else if(!(gd.hero.charType == 1 && gd.hero.numOfAb == 1 && modInMoves > 0))
    {
        if (gd.hero.buffDur == 0)
        {
            if (rand() % 100 + 1 > gd.hero.evasion)
            {
                gd.hero.hp -= dmg;
            }
        }
    }
    if (gd.hero.charType == 2 && gd.hero.numOfAb == 1 && modInMoves > 0)
    {
        gd.enemy.hp -= (short)(0.1 * maxHP);
    }
    if (buffSp > 0)
    {
        gd.hero.hp -= spValue;
    }
}

void Rogue::HeavyAttack(GameplayData &gd)
{
    static short dmg;
    dmg = modAt * (rand() % 5 + minHDMG);
    if (gd.hero.charType == 2 && gd.hero.numOfAb == 3 && gd.hero.statusDur > 0)
    {
        dmg /= 2;
    }
    if (gd.hero.charType == 3 && gd.hero.numOfAb == 1 && modInMoves > 0)
    {
        if (rand() % 100 + 1 > 65)
        {
            gd.hero.hp -= dmg;
        }
        else
        {
            gd.enemy.hp -= dmg;
        }
    }
    else if(!(gd.hero.charType == 1 && gd.hero.numOfAb == 1 && modInMoves > 0))
    {
        if (gd.hero.buffDur == 0)
        {
            if (rand() % 100 + 1 > gd.hero.evasion)
            {
                gd.hero.hp -= dmg;
            }
        }
    }
    if (gd.hero.charType == 2 && gd.hero.numOfAb == 1 && modInMoves > 0)
    {
        gd.enemy.hp -= (short)(0.1 * maxHP);
        gd.enemy.debuff--;
    }
    if (buffSp > 0)
    {
        gd.hero.hp -= spValue;
    }
}

void Rogue::Special(GameplayData &gd)
{
    if (buffSp > 0)
    {
        gd.enemy.hp += spValue;
    }
    gd.enemy.spVal++;
}