//
// Created by colte on 29.12.2022.
//

#include "Battle.h"
#include "../../characters/enemies.h"
#include <thread>

Battle::Battle(Hero **h, short rc) : GameplayEvent(h, rc) {
    frameCounter = 0;
    frameSpeed = 3;
    currentFrame = 0;
    {
        short enemyChoose = rand() % 101;
        if(enemyChoose < 60)
            enemy = new Zombie(roomCount);
        else enemy = new Rogue(roomCount);
    }
    ClearGD();
    hero->GetData(gd);
    enemy->GetData(gd);
    switch (enemy->enemyType)
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
    frameRec = { 0, 0, (float)enemyTexture.width / 4, (float)enemyTexture.height };
    buttons = {
            Button({40, HEIGHT / 2 + 20}, {240, 60}, hero->nA.c_str(), 20, BLUE, true, textCol),
            Button({40, HEIGHT / 2 + 120}, {240, 60}, hero->hA.c_str(), 20, BLUE, true, textCol),
            Button({40, HEIGHT / 2 + 220}, {240, 60}, hero->sp.c_str(), 20, BLUE, true, textCol),
            Button({40, HEIGHT / 2 + 320}, {240, 60}, hero->ability->abTitle.c_str(), 20, BLUE, true, textCol),
            Button({650, HEIGHT / 2 + 315}, {200, 70}, hero->items[0]->getName().c_str(), 24, BLUE, true, textCol),
            Button({900, HEIGHT / 2 + 315}, {200, 70}, hero->items[1]->getName().c_str(), 24, BLUE, true, textCol)
    };
    {
        short i = 1;
        for (auto &el: buttons)
            el.SetValue(i++);
    }
}

Battle::~Battle() {
    *refHero = hero;
    delete enemy;
    enemy = nullptr;
    UnloadTexture(enemyTexture);
}

void Battle::Update() {
    static short selection;
    static bool newGD, nextTurn;
    selection = 0;
    nextTurn = false;
    newGD = false;
    frameCounter++;
    if (frameCounter >= 60 / frameSpeed)
    {
        frameCounter = 0;
        currentFrame++;
        if (currentFrame > 2) currentFrame = 0;
        frameRec.x = (float)currentFrame * (float)enemyTexture.width / 4;
    }
    for(auto& el: buttons)
    {
        el.Click(selection);
        if(selection != 0)
            break;
    }
    if(selection != 0) ClearGD();
    switch(selection) {
        case 1:
            hero->Attack(gd);
            nextTurn = true;
            newGD = true;
            break;
        case 2:
            hero->HeavyAttack(gd);
            nextTurn = true;
            newGD = true;
            break;
        case 3:
            if(!(hero->charType == 3 && hero->buffsDur > 0))
            {
                hero->Special(gd);
                nextTurn = true;
                newGD = true;
            }
            break;
        case 4:
            if(hero->ability->curDelay == 0)
            {
                hero->useAbility(gd);
                nextTurn = true;
                newGD = true;
            }
            break;
        case 5:
            if(hero->items[0]->getNum() != 0)
            {
                hero->useItem(gd, 0);
                buttons[4].SetText(hero->items[0]->getName().c_str());
                newGD = true;
            }
            break;
        case 6:
            if(hero->items[1]->getNum() != 0)
            {
                hero->useItem(gd, 1);
                buttons[5].SetText(hero->items[1]->getName().c_str());
                newGD = true;
            }
            break;
    }
    if(nextTurn)
    {
        short move = rand() % 101;
        if(move < 50)
            enemy->Attack(gd);
        else if(move < 80)
            enemy->HeavyAttack(gd);
        else enemy->Special(gd);
        if(hero->buffsDur > 0)
            gd.hero.buffDur--;
        if(hero->ability->curDelay > 0)
            gd.hero.curDel--;
        if(hero->ability->statusDur > 0)
            gd.hero.statusDur--;
        if(enemy->modInMoves > 0)
            gd.enemy.debuff--;
        if(enemy->buffSp > 0)
            gd.enemy.spVal--;
    }
    if(newGD)
    {
        hero->SetData(gd);
        enemy->SetData(gd);
    }
}

void Battle::Draw() {
    BeginDrawing();
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(objects, 0, 0, WHITE);
    DrawRectangle(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, Color{0, 0, 0, 150});
    DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, textCol);

    if (gd.hero.charType == 3 && hero->buffsDur > 0) DrawRectangle(40, HEIGHT / 2 + 220, 240, 60, DARKGRAY);
    if (hero->ability->curDelay != 0) DrawRectangle(40, HEIGHT / 2 + 320, 240, 60, DARKGRAY);

    for(auto& el: buttons)
        el.Show();

    //DrawText(inf->username, 300, HEIGHT / 2 + 20, 24, WHITE);
    switch (gd.hero.charType)
    {
        case 1:
            DrawText("Swordsman", 300, HEIGHT / 2 + 60, 24, textCol);
            break;
        case 2:
            DrawText("Archer", 300, HEIGHT / 2 + 60, 24, textCol);
            break;
        case 3:
            DrawText("Paladin", 300, HEIGHT / 2 + 60, 24, textCol);
            break;
    }
    DrawText(TextFormat("HP: %d/%d", hero->hp, hero->maxHP), 300, HEIGHT / 2 + 100, 24, textCol);
    DrawText(TextFormat("Block: %d", hero->block), 300, HEIGHT / 2 + 140, 24, textCol);
    DrawText(TextFormat("Normal attack damage: %d", hero->minNDMG), 300, HEIGHT / 2 + 180, 24, textCol);
    DrawText(TextFormat("Heavy attack damage: %d", hero->minHDMG), 300, HEIGHT / 2 + 220, 24, textCol);
    DrawText(TextFormat("Special value: %d", hero->spValue), 300, HEIGHT / 2 + 260, 24, textCol);
    DrawText(TextFormat("Evasion: %d%", hero->evasion), 300, HEIGHT / 2 + 300, 24, textCol);
    DrawText(TextFormat("Buff duration: %d", hero->buffsDur), 300, HEIGHT / 2 + 340, 24, textCol);
    DrawText(TextFormat("Gold: %d", hero->gold), 300, HEIGHT / 2 + 380, 24, textCol);
    if (!(gd.hero.charType == 3 && gd.hero.numOfAb == 3))
        DrawText(TextFormat("Effect in moves: %d", hero->ability->abilityVal), 650, HEIGHT / 2 + 100, 24, textCol);
    else DrawText(TextFormat("Fourth ability's value: %d", hero->ability->abilityVal), 650, HEIGHT / 2 + 100, 24, textCol);
    DrawText(TextFormat("Maximum delay: %d", hero->ability->maxDelay), 650, HEIGHT / 2 + 140, 24, textCol);
    DrawText(TextFormat("Current delay: %d", hero->ability->curDelay), 650, HEIGHT / 2 + 180, 24, textCol);
    DrawText(TextFormat("Status duration: %d", hero->ability->statusDur), 650, HEIGHT / 2 + 220, 24, textCol);

    if (gd.hero.hp > 0) DrawText(TextFormat("%d", gd.hero.hp), 600, HEIGHT / 2 + 100, 24, GREEN);
    else if (gd.hero.hp < 0) DrawText(TextFormat("%d", gd.hero.hp), 600, HEIGHT / 2 + 100, 24, RED);

    if(gd.hero.block > 0) DrawText(TextFormat("%d", gd.hero.block), 600, HEIGHT / 2 + 140, 24, GREEN);
    else if (gd.hero.block < 0) DrawText(TextFormat("%d", gd.hero.block), 600, HEIGHT / 2 + 140, 24, RED);

    if(gd.hero.buffDur != 0) DrawText(TextFormat("%d", gd.hero.buffDur), 600, HEIGHT / 2 + 340, 24, GREEN);

    if (gd.hero.curDel != 0) DrawText(TextFormat("%d", gd.hero.curDel), 950, HEIGHT / 2 + 180, 24, RED);

    if (gd.hero.statusDur != 0) DrawText(TextFormat("%d", gd.hero.statusDur), 950, HEIGHT / 2 + 220, 24, GREEN);

    if (gd.enemy.hp < 0) DrawText(TextFormat("%d", gd.enemy.hp), 1375, HEIGHT / 2 + 60, 24, GREEN);
    else if (gd.enemy.hp > 0) DrawText(TextFormat("%d", gd.enemy.hp), 1375, HEIGHT / 2 + 60, 24, RED);

    if (gd.enemy.debuff > 0) DrawText(TextFormat("%d", gd.enemy.debuff), 1375, HEIGHT / 2 + 260, 24, GREEN);
    else if (gd.enemy.debuff < 0) DrawText(TextFormat("%d", gd.enemy.debuff), 1375, HEIGHT / 2 + 260, 24, RED);

    //if(isBoss) DrawText("Boss", 1050, HEIGHT / 2 + 20, 24, WHITE);
    switch (gd.enemy.enemyType)
    {
        case 1:
            DrawText("Zombie", 1050, HEIGHT / 2 + 20, 24, textCol);
            break;
        case 2:
            DrawText("Rogue", 1050, HEIGHT / 2 + 20, 24, textCol);
            break;
        default:
            DrawText("Enemy", 1050, HEIGHT / 2 + 20, 24, textCol);
            break;
    }
    DrawText(TextFormat("HP: %d/%d", enemy->hp, enemy->maxHP), 1050, HEIGHT / 2 + 60, 24, textCol);
    DrawText(TextFormat("Normal attack damage: %d", enemy->minNDMG), 1050, HEIGHT / 2 + 100, 24, textCol);
    DrawText(TextFormat("Heavy attack damage: %d", enemy->minHDMG), 1050, HEIGHT / 2 + 140, 24, textCol);
    DrawText(TextFormat("Special value: %d", enemy->spValue), 1050, HEIGHT / 2 + 180, 24, textCol);
    DrawText(TextFormat("Gold reward: %d%", enemy->rewGold), 1050, HEIGHT / 2 + 220, 24, textCol);
    DrawText(TextFormat("Current debuff value: %d%", enemy->modInMoves), 1050, HEIGHT / 2 + 260, 24, textCol);

    DrawText(TextFormat("Room %d%", roomCount), 20, 20, 30, textCol);

    DrawTextureRec(enemyTexture, frameRec, { WIDTH / 2 - 90, HEIGHT / 4 - 210 }, WHITE);

    ClearBackground(WHITE);
    EndDrawing();
}

void Battle::ClearGD() {
    gd.hero.hp = 0;
    gd.hero.block = 0;
    gd.hero.curDel = 0;
    gd.hero.buffDur = 0;
    gd.hero.statusDur = 0;
    gd.hero.maxHP = 0;
    gd.hero.evasion = 0;
    gd.enemy.hp = 0;
    gd.enemy.debuff = 0;
    gd.enemy.spVal = 0;
}

bool Battle::IsDone() {
    return enemy->hp <= 0;
}

short Battle::EnemyNumber() const {
    return gd.enemy.enemyType;
}

short Battle::EnemyReward() const {
    return enemy->rewGold + rand() % 4;
}
