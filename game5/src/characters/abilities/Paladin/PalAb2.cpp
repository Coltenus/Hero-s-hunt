//
// Created by colte on 27.12.2022.
//

#include "PalAb2.h"

PalAb2::PalAb2()
{
    curDelay = 0;
    maxDelay = 8;
    abilityVal = 1;
    addAbilityVal = 0;
    numOfAb = 2;
    statusDur = 0;
    abTitle = "God's blessing";
}

void PalAb2::activate(GameplayData &gd)
{
    if (curDelay < 0) gd.hero.curDel += -curDelay;
    if (curDelay > 0) gd.hero.curDel--;
    else
    {
        gd.hero.statusDur += abilityVal;
        gd.hero.curDel += maxDelay;
    }
}