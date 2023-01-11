//
// Created by colte on 27.12.2022.
//

#include "PalAb3.h"
#include <iostream>

PalAb3::PalAb3()
{
    curDelay = 0;
    maxDelay = 8;
    abilityVal = 40;
    addAbilityVal = 0;
    numOfAb = 3;
    statusDur = 0;
    abTitle = "Chaotic offering";
}

void PalAb3::activate(GameplayData &gd)
{
    static short buf;
    if (curDelay < 0) gd.hero.curDel += -curDelay;
    if (curDelay > 0) gd.hero.curDel--;
    else
    {
        buf = rand() % (abilityVal * 2 + 1) - abilityVal;
        gd.hero.hp += buf;
        buf = rand() % (abilityVal * 2 + 1) - abilityVal;
        gd.enemy.hp += buf;
        gd.hero.curDel += maxDelay;
    }
}