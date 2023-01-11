//
// Created by colte on 28.12.2022.
//

#ifndef GAME5_ZOMBIE_H
#define GAME5_ZOMBIE_H

#include "Enemy.h"

class Zombie : public Enemy
{
public:
    Zombie(unsigned short);
    ~Zombie() override = default;
    void Attack(GameplayData&) override;
    void HeavyAttack(GameplayData&) override;
    void Special(GameplayData&) override;
};


#endif //GAME5_ZOMBIE_H
