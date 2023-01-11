//
// Created by colte on 26.12.2022.
//

#ifndef GAME5_GAMEPLAY_H
#define GAME5_GAMEPLAY_H

#include "Page.h"
#include "../characters/heroes.h"
#include "../characters/enemies.h"
#include "GameplayEvents/GameplayEvent.h"
#include "../utils/Save.h"

class Gameplay : public Page {
private:
    GameplayData gpData;
    Hero* hero;
    GameplayEvent* gameEv;
    short roomCount;
    Save* save;
    explicit Gameplay(PageType*, Save*);
    void NewRoom();
    void GenerateHero(SaveData::heroStats&);
    void SaveProgress();
    void GetData(SaveData&);

public:
    static Gameplay* page;
    static Gameplay* CreateGameplay(PageType*, Save*);
    ~Gameplay() override;
    void Update() override;
    void Draw() override;
};


#endif //GAME5_GAMEPLAY_H
