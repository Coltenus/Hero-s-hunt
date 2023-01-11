//
// Created by colte on 31.12.2022.
//

#ifndef GAME5_TRANSITION_H
#define GAME5_TRANSITION_H

#include "GameplayEvent.h"

class Transition : public GameplayEvent {
private:
    bool active;

public:
    Transition(Hero**, short);
    ~Transition() = default;
    void Update() override;
    void Draw() override;
    bool IsDone() override;
};


#endif //GAME5_TRANSITION_H
