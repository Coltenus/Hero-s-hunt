//
// Created by colte on 27.12.2022.
//

#include "UpMaxHP.h"
#include <iostream>

UpMaxHP::UpMaxHP(short i) : Item()
{
    setVal(5 + (short)(rand() % (i + 1) / 4));
    setName("Fairy potion");
    setNum(4);
}

void UpMaxHP::activate(GameplayData &gd)
{
    gd.hero.maxHP += getVal();
    gd.hero.hp += getVal();
}