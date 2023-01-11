//
// Created by colte on 26.12.2022.
//

#include "Gameplay.h"
#include "GameplayEvents/gameplay_events.h"
#include "../characters/abilities.h"
#include "../characters/items.h"

Gameplay::Gameplay(PageType *pt, Save* sv) : Page(pt), roomCount(0), save(sv)
{
    SaveData buf;
    buf = save->GetProgress();
    roomCount = buf.roomNumber;
    if(roomCount == 0) {
        gpData.roomType = ChooseRoom;
        hero = nullptr;
        gameEv = new ChooseStart(&hero, roomCount);
    } else {
        GenerateHero(buf.hs);
        gameEv = nullptr;
        gpData.roomType = TransitionFrame;
        NewRoom();
    }
}

Gameplay *Gameplay::CreateGameplay(PageType *pt, Save* sv) {
    if(page != nullptr)
        return nullptr;
    else {
        page = new Gameplay(pt, sv);
        return page;
    }
}

Gameplay::~Gameplay() {
    if(hero != nullptr)
    {
        delete hero;
        hero = nullptr;
    }
    if(gameEv != nullptr)
    {
        delete gameEv;
        gameEv = nullptr;
    }
    page = nullptr;
}

void Gameplay::Update() {
    gameEv->Update();
    if((IsKeyPressed(KEY_ESCAPE) && WindowShouldClose()) || (gpData.roomType == DeadFrame && gameEv->IsDone())) {
        *pageType = MainPage;
        active = false;
    } else if (gameEv->IsDone() || (hero != nullptr && hero->hp <= 0 && gpData.roomType != DeadFrame)){
        NewRoom();
    }
}

void Gameplay::Draw() {
    gameEv->Draw();
}

void Gameplay::NewRoom() {
    short room = rand() % 101;
    short enemyNum, enemyRew;
    if(hero != nullptr && hero->hp <= 0) {
        delete gameEv;
        gameEv = new DeadScreen(&hero, roomCount);
        gpData.roomType = DeadFrame;
        SaveProgress();
    }
    else {
        if(gpData.roomType == BattleRoom) {
            enemyNum = reinterpret_cast<Battle*>(gameEv)->EnemyNumber();
            enemyRew = reinterpret_cast<Battle*>(gameEv)->EnemyReward();
        }
        else {
            enemyNum = 0;
            enemyRew = 0;
        }
        if(gameEv != nullptr) delete gameEv;
        if(gpData.roomType == BattleRoom) {
            gameEv = new Reward(&hero, roomCount, enemyNum, enemyRew);
            gpData.roomType = RewardFrame;
        }
        else if(gpData.roomType != TransitionFrame) {
            roomCount++;
            SaveProgress();
            gameEv = new Transition(&hero, roomCount);
            gpData.roomType = TransitionFrame;
        }
        else if(room <= 60) {
            gameEv = new Battle(&hero, roomCount);
            gpData.roomType = BattleRoom;
        }
        else if(room <= 80) {
            gameEv = new Shop(&hero, roomCount);
            gpData.roomType = ShopRoom;
        }
        else {
            gameEv = new Rest(&hero, roomCount);
            gpData.roomType = RestRoom;
        }
    }
}

void Gameplay::GenerateHero(SaveData::heroStats& heroStats) {
    {
        Ability *ab1, *ab2, *ab3;
        switch (heroStats.character) {
            case 1:
                hero = new Swordsman;
                ab1 = new SwAb1;
                ab2 = new SwAb2;
                ab3 = new SwAb3;
                break;
            case 2:
                hero = new Archer;
                ab1 = new ArAb1;
                ab2 = new ArAb2;
                ab3 = new ArAb3;
                break;
            case 3:
                hero = new Paladin;
                ab1 = new PalAb1;
                ab2 = new PalAb2;
                ab3 = new PalAb3;
                break;
        }
        switch (heroStats.ability) {
            case 1:
                hero->ability = ab1;
                delete ab2;
                delete ab3;
                break;
            case 2:
                hero->ability = ab2;
                delete ab1;
                delete ab3;
                break;
            case 3:
                hero->ability = ab3;
                delete ab1;
                delete ab2;
                break;
        }
    }
    {
        Item *i1 = nullptr;
        Item *i2 = nullptr;
        auto CreateItem = [](Item** item, short num, short val) {
            switch (num) {
                case 1:
                    *item = new Healing(0);
                    break;
                case 2:
                    *item = new Block(0);
                    break;
                case 3:
                    *item = new DmgPotion(0);
                    break;
                case 4:
                    *item = new UpMaxHP(0);
                    break;
            }
            if(*item != nullptr)
                (*item)->setVal(val);
        };
        CreateItem(&i1, heroStats.i1.num, heroStats.i1.val);
        CreateItem(&i2, heroStats.i2.num, heroStats.i2.val);
        if(i1 != nullptr)
            hero->items[0] = i1;
        if(i2 != nullptr)
            hero->items[1] = i2;
    }
    hero->gold = heroStats.gold;
    hero->block = heroStats.stats.block;
    hero->hp = heroStats.stats.hp;
    hero->maxHP = heroStats.stats.maxHP;
    hero->evasion = heroStats.stats.evasion;
    hero->spValue = heroStats.stats.spValue;
    hero->minNDMG = heroStats.stats.dmgN;
    hero->minHDMG = heroStats.stats.dmgH;
    hero->buffsDur = heroStats.stats.buffDur;
    hero->ability->statusDur = heroStats.stats.statDur;
}

void Gameplay::SaveProgress() {
    SaveData buf;
    if(hero->hp > 0)
        GetData(buf);
    else Save::ClearSaveData(buf);
    save->SaveProgress(&buf);
}

void Gameplay::GetData(SaveData& sd) {
    sd.roomNumber = roomCount;
    sd.hs.character = hero->charType;
    sd.hs.ability = hero->ability->numOfAb;
    sd.hs.gold = hero->gold;
    sd.hs.i1.num = hero->items[0]->getNum();
    sd.hs.i1.val = hero->items[0]->getVal();
    sd.hs.i2.num = hero->items[1]->getNum();
    sd.hs.i2.val = hero->items[1]->getVal();
    sd.hs.stats.block = hero->block;
    sd.hs.stats.hp = hero->hp;
    sd.hs.stats.maxHP = hero->maxHP;
    sd.hs.stats.evasion = hero->evasion;
    sd.hs.stats.spValue = hero->spValue;
    sd.hs.stats.dmgN = hero->minNDMG;
    sd.hs.stats.dmgH = hero->minHDMG;
    sd.hs.stats.buffDur = hero->buffsDur;
    sd.hs.stats.statDur = hero->ability->statusDur;
}
