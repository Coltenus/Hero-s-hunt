//
// Created by colte on 27.12.2022.
//

#include "SwAb2.h"

SwAb2::SwAb2()
{
    curDelay = 0;
    maxDelay = 6;
    abilityVal = 2;
    addAbilityVal = 0;
    numOfAb = 2;
    statusDur = 0;
    abTitle = "Enchantment";
}

void SwAb2::activate(GameplayData &gd)
{
    if (curDelay < 0) gd.hero.curDel += -curDelay;
    if (curDelay > 0) gd.hero.curDel--;
    else
    {
        gd.hero.curDel += maxDelay;
        gd.hero.statusDur += abilityVal;
    }
}