//
// Created by colte on 27.12.2022.
//

#include "Healing.h"
#include <iostream>

Healing::Healing(short i) : Item()
{
    setVal(10 + rand() % (i + 1));
    setName("Heal Potion");
    setNum(1);
}

void Healing::activate(GameplayData &gd)
{
    gd.hero.hp += getVal();
}