//
// Created by colte on 02.01.2023.
//

#ifndef GAME5_REST_H
#define GAME5_REST_H

#include "GameplayEvent.h"

class Rest : public GameplayEvent {
private:
    bool active;

public:
    Rest(Hero**, short);
    ~Rest();
    void Update() override;
    void Draw() override;
    bool IsDone();
};


#endif //GAME5_REST_H
