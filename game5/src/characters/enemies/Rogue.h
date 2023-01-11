//
// Created by colte on 28.12.2022.
//

#ifndef GAME5_ROGUE_H
#define GAME5_ROGUE_H

#include "Enemy.h"

class Rogue : public Enemy
{
public:
    Rogue(unsigned short);
    ~Rogue() override = default;
    void Attack(GameplayData&) override;
    void HeavyAttack(GameplayData&) override;
    void Special(GameplayData&) override;
};


#endif //GAME5_ROGUE_H
