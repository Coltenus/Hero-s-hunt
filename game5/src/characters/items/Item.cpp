//
// Created by colte on 26.12.2022.
//

#include "Item.h"
#include <cstring>

Item::Item()
{
    val = 0;
    numOfItem = 0;
    itemTitle = "";
}

void Item::setVal(short val)
{
    this->val = val;
}

void Item::setName(const char* name)
{
    itemTitle = name;
}

void Item::setName(std::string name)
{
    itemTitle = name;
}

void Item::setNum(short num)
{
    numOfItem = num;
}

short Item::getVal()
{
    return val;
}

std::string Item::getName()
{
    return itemTitle;
}

short Item::getNum()
{
    return numOfItem;
}