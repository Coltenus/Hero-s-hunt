//
// Created by colte on 31.12.2022.
//

#include "Reward.h"
#include "../../characters/items.h"

Reward::Reward(Hero **h, short rc, short enemyNum, short er) : GameplayEvent(h, rc), slot(-1),
active(true), rewardClaimed(false) {
    switch (enemyNum)
    {
        case 1:
            SetObjects("res/zombie_bg.png");
            enemyTexture = LoadTexture("res/Zombie.png");
            break;
        case 2:
            SetObjects("res/rogue_bg.png");
            enemyTexture = LoadTexture("res/Rogue.png");
            break;
        default:
            SetObjects("res/zombie_bg.png");
            enemyTexture = LoadTexture("res/Zombie.png");
            break;
    }
    frameRec = { (float)enemyTexture.width / 4 * 3, 0, (float)enemyTexture.width / 4, (float)enemyTexture.height };
    {
        short item = rand() % 101;
        if(item <= 25)
            i1 = new Healing(roomCount);
        else if(item <= 50)
            i1 = new Block(roomCount);
        else if(item <= 75)
            i1 = new DmgPotion(roomCount);
        else i1 = new UpMaxHP(roomCount);
    }
    {
        short item = rand() % 101;
        if(item <= 25)
            i2 = new Healing(roomCount);
        else if(item <= 50)
            i2 = new Block(roomCount);
        else if(item <= 75)
            i2 = new DmgPotion(roomCount);
        else i2 = new UpMaxHP(roomCount);
    }
    buttons = {
            Button({WIDTH / 2 - 525, HEIGHT / 2 - 400}, {200, 100}, i1->getName().c_str(), 26, BLUE, true, textCol),
            Button({WIDTH / 2 - 75, HEIGHT / 2 - 400}, {200, 100}, i2->getName().c_str(), 26, BLUE, true, textCol),
            Button({WIDTH / 2 + 350, HEIGHT / 2 - 400}, {200, 100}, "Decline", 26, BLUE, true, textCol)
    };
    {
        short i = 1;
        for(auto& el: buttons)
        {
            el.SetValue(i++);
            el.SetOnceStatus(true);
        }
    }
    rewardStats.gold = er;
    rewardStats.hp = rand() % 4;
    rewardStats.nDMG = rand() % 3;
    rewardStats.hDMG = rand() % 3;
    switch (hero->charType) {
        case 1:
            rewardStats.spVal = rand() % 4;
            break;
        case 2:
            rewardStats.spVal = 0;
            break;
        case 3:
            rewardStats.spVal = rand() % 2;
            break;
        default:
            rewardStats.spVal = 0;
    }
    if (hero->evasion < 60) rewardStats.evasion = rand() % 2;
    else rewardStats.evasion = 0;
    hero->SetData(rewardStats);
}

void Reward::Update() {
    static short selection;
    static auto DisableButtons = [&]() {
        for(auto& el: buttons)
            el.SetStatus(false);
    };
    selection = 0;
    if((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) && rewardClaimed)
        active = false;
    for(auto& el: buttons)
    {
        el.Click(selection);
        if(selection != 0)
            break;
    }
    switch (selection) {
        case 1:
            if (!rewardClaimed) {
                slot = hero->findFreeSlot();
                if (slot < 2)
                {
                    delete hero->items[slot];
                    hero->items[slot] = i1;
                }
                DisableButtons();
            }
            break;
        case 2:
            if (!rewardClaimed) {
                slot = hero->findFreeSlot();
                if (slot < 2)
                {
                    delete hero->items[slot];
                    hero->items[slot] = i2;
                }
                DisableButtons();
            }
            break;
        case 3:
            if (!rewardClaimed)
            {
                slot = 2;
                DisableButtons();
            }
            break;
    }
    if(slot != -1)
        rewardClaimed = true;
}

void Reward::Draw() {
    BeginDrawing();
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(objects, 0, 0, WHITE);
    DrawRectangle(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, Color{0, 0, 0, 150});
    DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, textCol);

    DrawTextureRec(enemyTexture, frameRec, { WIDTH / 2 - 75, HEIGHT / 2 - 450 }, WHITE);
    DrawText(TextFormat("Room %hu", roomCount), WIDTH / 2 - 25, HEIGHT / 2 + 50, 30, textCol);
    DrawText(TextFormat("+%hu gold", rewardStats.gold), WIDTH / 2 - 25, HEIGHT / 2 + 200, 30, textCol);
    DrawText(TextFormat("+%hu hp", rewardStats.hp), 100, HEIGHT / 2 + 300, 24, textCol);
    DrawText(TextFormat("+%hu min normal DMG", rewardStats.nDMG), 400, HEIGHT / 2 + 300, 24, textCol);
    DrawText(TextFormat("+%hu min heavy DMG", rewardStats.hDMG), 700, HEIGHT / 2 + 300, 24, textCol);
    DrawText(TextFormat("+%hu special value", rewardStats.spVal), 1000, HEIGHT / 2 + 300, 24, textCol);
    DrawText(TextFormat("+%hu evasion", rewardStats.evasion), 1300, HEIGHT / 2 + 300, 24, textCol);

    DrawText("Choose your reward item", WIDTH / 2 - 180, HEIGHT / 2 - 440, 30, textCol);

    for(auto& el: buttons)
        el.Show();
    switch (i1->getNum())
    {
        case 1:
            DrawText(TextFormat("Heals by value of %d", i1->getVal()), WIDTH / 2 - 550,
                     HEIGHT / 2 - 290, 26, textCol);
            break;
        case 2:
            DrawText(TextFormat("Gives block by value of %d", i1->getVal()), WIDTH / 2 - 550,
                     HEIGHT / 2 - 290, 26, textCol);
            break;
        case 3:
            DrawText(TextFormat("Deal damage to the\nenemy by value of %d", i1->getVal()),
                     WIDTH / 2 - 550, HEIGHT / 2 - 290, 26, textCol);
            break;
        case 4:
            DrawText(TextFormat("Ups your maximum Hp\nby value of %d", i1->getVal()),
                     WIDTH / 2 - 550, HEIGHT / 2 - 290, 26, textCol);
            break;
    }

    switch (i2->getNum())
    {
        case 1:
            DrawText(TextFormat("Heals by value of %d", i2->getVal()), WIDTH / 2 - 100,
                     HEIGHT / 2 - 290, 26, textCol);
            break;
        case 2:
            DrawText(TextFormat("Gives block by value of %d", i2->getVal()), WIDTH / 2 - 100,
                     HEIGHT / 2 - 290, 26, textCol);
            break;
        case 3:
            DrawText(TextFormat("Deal damage to the\nenemy by value of %d", i2->getVal()),
                     WIDTH / 2 - 100, HEIGHT / 2 - 290, 26, textCol);
            break;
        case 4:
            DrawText(TextFormat("Ups your maximum Hp\nby value of %d", i2->getVal()),
                     WIDTH / 2 - 100, HEIGHT / 2 - 290, 26, textCol);
            break;
    }

    ClearBackground(WHITE);
    EndDrawing();
}

bool Reward::IsDone() {
    return !active;
}

Reward::~Reward() {
    *refHero = hero;
    switch(slot) {
        case -1:
        case 3:
            delete i1;
            delete i2;
            i1 = nullptr;
            i2 = nullptr;
            break;
        case 1:
            delete i2;
            i2 = nullptr;
            break;
        case 2:
            delete i1;
            i1 = nullptr;
            break;
    }
}
