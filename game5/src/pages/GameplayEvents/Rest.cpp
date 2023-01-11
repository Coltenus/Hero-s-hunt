//
// Created by colte on 02.01.2023.
//

#include "Rest.h"

Rest::Rest(Hero **h, short rc) : GameplayEvent(h, rc), active(true) {
    buttons = {
            Button({WIDTH / 2 - 100, HEIGHT / 2 + 120}, {220, 60}, "Rest", 24, BLUE, true, textCol),
            Button({WIDTH / 2 - 100, HEIGHT / 2 + 220}, {220, 60}, "Random upgrade", 24, BLUE, true, textCol)
    };
    {
        short i = 1;
        for (auto &el: buttons) {
            el.SetValue(i++);
            el.SetOnceStatus(true);
        }
    }
}

void Rest::Update() {
    static short selection;
    static auto DisableButtons = [&]() {
        for(auto& el: buttons)
            el.SetStatus(false);
    };
    selection = 0;
    if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        active = false;
    for(auto& el: buttons)
    {
        el.Click(selection);
        if(selection != 0)
            break;
    }
    switch (selection) {
        case 1:
            hero->hp += static_cast<short>(hero->maxHP * 0.25f);
            if(hero->hp > hero->maxHP) hero->hp = hero->maxHP;
            DisableButtons();
            break;
        case 2:
            short sel = rand() % 5;
            short buf;
            switch (sel) {
                case 0:
                    buf = rand() % 3 + 1;
                    hero->maxHP += buf;
                    hero->hp += buf;
                    break;
                case 1:
                    hero->minNDMG += rand() % 3 + 1;
                    break;
                case 2:
                    hero->minHDMG += rand() % 3 + 1;
                    break;
                case 3:
                    if (hero->evasion < 60) hero->evasion += 1;
                    break;
                case 4:
                    if (hero->charType == 1) hero->spValue += rand() % 3 + 1;
                    else if (hero->charType == 3) hero->spValue += 1;
                    break;
            }
            DisableButtons();
            break;
    }
}

void Rest::Draw() {
    BeginDrawing();
    DrawTexture(background, 0, 0, WHITE);

    DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, textCol);
    DrawText(TextFormat("Room %d%", roomCount), 20, 20, 30, textCol);
    DrawText("Rest Room", WIDTH / 2 - 80, HEIGHT / 2 + 20, 30, textCol);

    for(auto& el: buttons)
        el.Show();

    ClearBackground(WHITE);
    EndDrawing();
}

bool Rest::IsDone() {
    return !active;
}

Rest::~Rest() {
    *refHero = hero;
}
