//
// Created by colte on 27.12.2022.
//

#include "SwAb1.h"

SwAb1::SwAb1()
{
    curDelay = 0;
    maxDelay = 8;
    abilityVal = 2;
    addAbilityVal = 0;
    numOfAb = 1;
    statusDur = 0;
    abTitle = "Disarm";
}

void SwAb1::activate(GameplayData &gd)
{
    if (curDelay < 0) gd.hero.curDel += -curDelay;
    if (curDelay > 0) gd.hero.curDel--;
    else
    {
        gd.hero.curDel += maxDelay;
        gd.enemy.debuff += abilityVal;
    }
}