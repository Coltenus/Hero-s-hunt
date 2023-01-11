//
// Created by colte on 27.12.2022.
//

#include "PalAb1.h"

PalAb1::PalAb1()
{
    curDelay = 0;
    maxDelay = 8;
    abilityVal = 3;
    addAbilityVal = 0;
    numOfAb = 1;
    statusDur = 0;
    abTitle = "God's infection";
}

void PalAb1::activate(GameplayData &gd)
{
    if (curDelay < 0) gd.hero.curDel += -curDelay;
    if (curDelay > 0) gd.hero.curDel--;
    else
    {
        gd.enemy.debuff += abilityVal;
        gd.hero.curDel += maxDelay;
    }
}