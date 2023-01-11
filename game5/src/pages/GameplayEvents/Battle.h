//
// Created by colte on 29.12.2022.
//

#ifndef GAME5_BATTLE_H
#define GAME5_BATTLE_H

#include "GameplayEvent.h"
#include "../../characters/enemies.h"

class Battle : public GameplayEvent {
private:
    Enemy* enemy;
    Texture2D enemyTexture;
    Rectangle frameRec;
    int frameSpeed, frameCounter, currentFrame;
    GameplayData gd;
    void ClearGD();

public:
    Battle(Hero**, short);
    ~Battle();
    void Update() override;
    void Draw() override;
    bool IsDone() override;
    short EnemyNumber() const;
    short EnemyReward() const;
};


#endif //GAME5_BATTLE_H
