//
// Created by colte on 27.12.2022.
//

#ifndef GAME5_BLOCK_H
#define GAME5_BLOCK_H

#include "Item.h"
#include "../../common.h"

class Block : public Item
{
public:
    Block(short);
    ~Block() override = default;
    void activate(GameplayData&) override;
};


#endif //GAME5_BLOCK_H
