//
// Created by colte on 27.12.2022.
//

#include "SwAb3.h"

SwAb3::SwAb3()
{
    curDelay = 0;
    maxDelay = 5;
    abilityVal = 1;
    addAbilityVal = 0;
    numOfAb = 3;
    statusDur = 0;
    abTitle = "Make the strategy";
}

void SwAb3::activate(GameplayData &gd)
{
    if (curDelay < 0) gd.hero.curDel += -curDelay;
    if (curDelay > 0) gd.hero.curDel--;
    else
    {
        gd.hero.curDel += maxDelay;
        gd.hero.statusDur += abilityVal;
    }
}