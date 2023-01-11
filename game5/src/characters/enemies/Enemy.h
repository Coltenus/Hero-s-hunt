//
// Created by colte on 26.12.2022.
//

#ifndef GAME5_ENEMY_H
#define GAME5_ENEMY_H

#include "../../common.h"

class Enemy
{
public:
    Enemy();
    virtual ~Enemy() = default;
public:
    virtual void Attack(GameplayData&) = 0;
    virtual void HeavyAttack(GameplayData&) = 0;
    virtual void Special(GameplayData&) = 0;
    void GetData(GameplayData&);
    void SetData(GameplayData&);
public:
    short maxHP, hp, rewGold, modAt, modInMoves, enemyType, buffSp;
    int minNDMG;
    int minHDMG;
    int spValue;
};


#endif //GAME5_ENEMY_H
