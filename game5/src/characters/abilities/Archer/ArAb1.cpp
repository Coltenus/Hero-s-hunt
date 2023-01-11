//
// Created by colte on 27.12.2022.
//

#include "ArAb1.h"

ArAb1::ArAb1()
{
    curDelay = 0;
    maxDelay = 6;
    abilityVal = 2;
    addAbilityVal = 0;
    numOfAb = 1;
    statusDur = 0;
    abTitle = "Bleeding";
}

void ArAb1::activate(GameplayData &gd)
{
    if (curDelay < 0) gd.hero.curDel += -curDelay;
    if (curDelay > 0) gd.hero.curDel--;
    else
    {
        gd.enemy.debuff += abilityVal;
        gd.hero.curDel += maxDelay;
    }
}