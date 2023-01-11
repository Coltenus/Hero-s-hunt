//
// Created by colte on 02.01.2023.
//

#include "Shop.h"

Shop::Shop(Hero **h, short rc) : GameplayEvent(h, rc), active(true) {
    {
        short buf;
        shopItems = {
                {1, {(buf = rand() % 15 + 5), buf}},
                {2, {(buf = rand() % 6 + 4), static_cast<short>(buf*3)}},
                {3, {(buf = rand() % 6 + 4), static_cast<short>(buf*3)}},
                {4, {(buf = rand() % 4 + 1), static_cast<short>(buf*8)}},
                {5, {0, 0}}
        };
        if (hero->charType == 1)
        {
            shopItems[5].stat = rand() % 5 + 5;
            shopItems[5].price = shopItems[4].stat * 5;
        }
        else if (hero->charType == 2)
        {
            shopItems[5].stat = 1;
            shopItems[5].price = shopItems[5].stat * 40;
        }
        else if (hero->charType == 3)
        {
            shopItems[5].stat = rand() % 4 + 1;
            shopItems[5].price = shopItems[5].stat * 10;
        }
    }
    buttons = {
            Button({110, HEIGHT / 4 * 3 + 40}, {150, 40}, TextFormat("%d G", shopItems[1].price), 24, LIGHT_YELLOW, true, textCol),
            Button({410, HEIGHT / 4 * 3 + 40}, {150, 40}, TextFormat("%d G", shopItems[2].price), 24, LIGHT_YELLOW, true, textCol),
            Button({760, HEIGHT / 4 * 3 + 40}, {150, 40}, TextFormat("%d G", shopItems[3].price), 24, LIGHT_YELLOW, true, textCol),
            Button({1065, HEIGHT / 4 * 3 + 40}, {150, 40}, TextFormat("%d G", shopItems[4].price), 24, LIGHT_YELLOW, true, textCol),
            Button({1335, HEIGHT / 4 * 3 + 40}, {150, 40}, TextFormat("%d G", shopItems[5].price), 24, LIGHT_YELLOW, true, textCol),
    };
    {
        short i = 1;
        for (auto &el: buttons) {
            el.SetValue(i++);
            el.SetOnceStatus(true);
        }
    }
    if (hero->evasion >= 60) buttons[3].SetStatus(false);
}

void Shop::Update() {
    static short selection;
    selection = 0;
    if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        active = false;
    for(auto& el: buttons)
    {
        el.Click(selection);
        if(selection != 0)
            break;
    }
    if(selection != 0)
    {
        if(hero->gold >= shopItems[selection].price){
            hero->gold -= shopItems[selection].price;
            switch (selection) {
                case 1:
                    hero->maxHP += shopItems[selection].stat;
                    hero->hp += shopItems[selection].stat;
                    break;
                case 2:
                    hero->minNDMG += shopItems[selection].stat;
                    break;
                case 3:
                    hero->minHDMG += shopItems[selection].stat;
                    break;
                case 4:
                    hero->evasion += shopItems[selection].stat;
                    break;
                case 5:
                    hero->spValue += shopItems[selection].stat;
                    break;
            }
        }
        else buttons[selection-1].SetStatus(true);
    }
}

void Shop::Draw() {
    BeginDrawing();
    DrawTexture(background, 0, 0, WHITE);

    DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, textCol);
    DrawText(TextFormat("Room %d%", roomCount), 20, 20, 30, textCol);
    DrawText(TextFormat("%d G", hero->gold), 70, HEIGHT / 2 + 20, 24, textCol);

    DrawText(TextFormat("+%d maximum HP", shopItems[1].stat), 100, HEIGHT / 4 * 3 - 12, 24, textCol);
    DrawText(TextFormat("+%d minimum normal DMG", shopItems[2].stat), 350, HEIGHT / 4 * 3 - 12, 24, textCol);
    DrawText(TextFormat("+%d minimum heavy DMG", shopItems[3].stat), 700, HEIGHT / 4 * 3 - 12, 24, textCol);
    DrawText(TextFormat("+%d evasion", shopItems[4].stat), 1075, HEIGHT / 4 * 3 - 12, 24, textCol);
    DrawText(TextFormat("+%d special value", shopItems[5].stat), 1300, HEIGHT / 4 * 3 - 12, 24, textCol);
    for(auto& el: buttons)
        el.Show();

    ClearBackground(WHITE);
    EndDrawing();
}

bool Shop::IsDone() {
    return !active;
}

Shop::~Shop() {
    *refHero = hero;
}
