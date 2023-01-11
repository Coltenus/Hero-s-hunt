//
// Created by colte on 29.12.2022.
//

#include "GameplayEvent.h"

GameplayEvent::GameplayEvent(Hero** h, short rc) : roomCount(rc) {
    hero = *h;
    refHero = h;
    if(roomCount%2 == 0) {
        SetBackground("res/night.png");
        SetObjects("res/night.png");
        textCol = {30, 255, 30, 200};
    }
    else {
        SetBackground("res/day.png");
        SetObjects("res/day.png");
        textCol = {50, 50, 255, 200};
    }
}

GameplayEvent::~GameplayEvent() {
    UnloadTexture(background);
    UnloadTexture(objects);
    hero = nullptr;
}

void GameplayEvent::SetBackground(const char *source) {
    UnloadTexture(background);
    background = LoadTexture(source);
}

void GameplayEvent::SetObjects(const char *source) {
    UnloadTexture(objects);
    objects = LoadTexture(source);
}
