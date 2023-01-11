//
// Created by colte on 30.12.2022.
//

#ifndef GAME5_CHOOSESTART_H
#define GAME5_CHOOSESTART_H

#include "GameplayEvent.h"

class ChooseStart : public GameplayEvent {
private:
    std::string title;
    bool chooseHero;
    Hero *buf, *sw, *ar, *pal;
    Ability *ab, *ab1, *ab2, *ab3;
    short heroNum;

public:
    ChooseStart(Hero**, short);
    ~ChooseStart();
    void Update() override;
    void Draw() override;
    bool IsDone() override;
};


#endif //GAME5_CHOOSESTART_H
