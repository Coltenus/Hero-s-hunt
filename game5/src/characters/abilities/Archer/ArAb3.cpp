//
// Created by colte on 27.12.2022.
//

#include "ArAb3.h"

ArAb3::ArAb3()
{
    curDelay = 0;
    maxDelay = 6;
    abilityVal = 2;
    addAbilityVal = 0;
    numOfAb = 3;
    statusDur = 0;
    abTitle = "Weakness";
}

void ArAb3::activate(GameplayData &gd)
{
    if (curDelay < 0) gd.hero.curDel += -curDelay;
    if (curDelay > 0) gd.hero.curDel--;
    else
    {
        gd.enemy.debuff += abilityVal;
        gd.hero.curDel += maxDelay;
    }
}