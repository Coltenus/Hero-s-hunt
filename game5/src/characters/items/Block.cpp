//
// Created by colte on 27.12.2022.
//

#include "Block.h"
#include <iostream>

Block::Block(short i) : Item()
{
    setVal(10 + rand() % (i + 1));
    setName("Shield");
    setNum(2);
}

void Block::activate(GameplayData &gd)
{
    gd.hero.block += getVal();
}