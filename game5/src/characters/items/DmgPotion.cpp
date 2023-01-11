//
// Created by colte on 27.12.2022.
//

#include "DmgPotion.h"
#include <iostream>

DmgPotion::DmgPotion(short i) : Item()
{
    setVal(20 + rand() % (i + 1));
    setName("Fire potion");
    setNum(3);
}

void DmgPotion::activate(GameplayData &gd)
{
    gd.enemy.hp -= getVal();
}