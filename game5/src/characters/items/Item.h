//
// Created by colte on 26.12.2022.
//

#ifndef GAME5_ITEM_H
#define GAME5_ITEM_H

#include "../../common.h"
#include <string>

class Item
{
private:
    short val, numOfItem;
    std::string itemTitle;
public:
    Item();
    virtual ~Item() = default;
    virtual void activate(GameplayData&) = 0;
    void setVal(short);
    void setName(const char*);
    void setName(std::string);
    void setNum(short);
    short getVal();
    std::string getName();
    short getNum();
};


#endif //GAME5_ITEM_H
