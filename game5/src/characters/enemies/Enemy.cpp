//
// Created by colte on 26.12.2022.
//

#include "Enemy.h"

Enemy::Enemy()
{
    maxHP = 0;
    hp = 0;
    rewGold = 0;
    modAt = 0;
    minNDMG = 0;
    minHDMG = 0;
    spValue = 0;
    enemyType = 0;
    modInMoves = 0;
    buffSp = 0;
}

void Enemy::GetData(GameplayData &gd) {
    gd.enemy.enemyType = enemyType;
}

void Enemy::SetData(GameplayData &gd) {
    hp += gd.enemy.hp;
    if(hp > maxHP) hp = maxHP;
    else if(hp < 0) hp = 0;
    modInMoves += gd.enemy.debuff;
    buffSp += gd.enemy.spVal;
}
