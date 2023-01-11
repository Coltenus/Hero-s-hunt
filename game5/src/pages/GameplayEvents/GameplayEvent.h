//
// Created by colte on 29.12.2022.
//

#ifndef GAME5_GAMEPLAYEVENT_H
#define GAME5_GAMEPLAYEVENT_H

#include <raylib.h>
#include <vector>
#include "../../characters/heroes.h"
#include "../../utils/Button.h"

class GameplayEvent {
public:
    Hero* hero;
    Hero** refHero;
    Texture2D background, objects;
    std::vector<Button> buttons;
    short roomCount;
    Color textCol;
    explicit GameplayEvent(Hero**, short);
    virtual ~GameplayEvent();
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual bool IsDone() = 0;
    void SetBackground(const char*);
    void SetObjects(const char*);
};


#endif //GAME5_GAMEPLAYEVENT_H
