//
// Created by colte on 31.12.2022.
//

#ifndef GAME5_REWARD_H
#define GAME5_REWARD_H

#include <vector>
#include "GameplayEvent.h"
#include "../../utils/Button.h"

class Reward : public GameplayEvent {
private:
    short slot;
    bool active, rewardClaimed;
    Texture2D enemyTexture;
    Rectangle frameRec;
    Item *i1, *i2;
    std::vector<Button> buttons;
    RewardStats rewardStats;

public:
    Reward(Hero**, short, short, short);
    ~Reward();
    void Update() override;
    void Draw() override;
    bool IsDone() override;
};


#endif //GAME5_REWARD_H
