//
// Created by colte on 27.12.2022.
//

#include "ArAb2.h"

ArAb2::ArAb2()
{
    curDelay = 0;
    maxDelay = 4;
    abilityVal = 1;
    addAbilityVal = 0;
    numOfAb = 2;
    statusDur = 0;
    abTitle = "Double Trouble";
}

void ArAb2::activate(GameplayData &gd)
{
    if (curDelay < 0) gd.hero.curDel += -curDelay;
    if (curDelay > 0) gd.hero.curDel--;
    else
    {
        gd.hero.statusDur += abilityVal;
        gd.hero.curDel += maxDelay;
    }
}