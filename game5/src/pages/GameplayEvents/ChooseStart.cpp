//
// Created by colte on 30.12.2022.
//

#include "ChooseStart.h"
#include "../../characters/abilities.h"

ChooseStart::ChooseStart(Hero **h, short rc) : GameplayEvent(h, rc), title("Choose hero"), chooseHero(true), buf(nullptr),
ab(nullptr), ab1(nullptr), ab2(nullptr), ab3(nullptr), heroNum(0){
    sw = new Swordsman;
    ar = new Archer;
    pal = new Paladin;
    buttons = {
            Button({WIDTH/2 - 175, HEIGHT/2 - 200}, {350, 100}, "Swordsman", 30, LIGHT_BLUE, true),
            Button({WIDTH/2 - 175, HEIGHT/2}, {350, 100}, "Archer", 30, LIGHT_GREEN, true),
            Button({WIDTH/2 - 175, HEIGHT/2 + 200}, {350, 100}, "Paladin", 30, LIGHT_YELLOW, true)
    };
    {
        short i = 1;
        for (auto &el: buttons)
            el.SetValue(i++);
    }
    SetBackground("res/night.png");
}

void ChooseStart::Update() {
    static short selection;
    static auto NewAbility = [](ChooseStart* cs, short selection) {
        switch(selection) {
            case 1:
                cs->hero->ability = cs->ab1;
                delete cs->ab2;
                cs->ab2 = nullptr;
                delete cs->ab3;
                cs->ab3 = nullptr;
                break;
            case 2:
                cs->hero->ability = cs->ab2;
                delete cs->ab1;
                cs->ab1 = nullptr;
                delete cs->ab3;
                cs->ab3 = nullptr;
                break;
            case 3:
                cs->hero->ability = cs->ab3;
                delete cs->ab1;
                cs->ab1 = nullptr;
                delete cs->ab2;
                cs->ab2 = nullptr;
                break;
        }
        switch (cs->heroNum) {
            case 0:
                delete cs->ar;
                cs->ar = nullptr;
                delete cs->pal;
                cs->pal = nullptr;
                break;
            case 1:
                delete cs->sw;
                cs->sw = nullptr;
                delete cs->pal;
                cs->pal = nullptr;
                break;
            case 2:
                delete cs->sw;
                cs->sw = nullptr;
                delete cs->ar;
                cs->ar = nullptr;
                break;
        }
    };
    selection = 0;

    for(auto& el: buttons)
    {
        el.Click(selection);
        if(selection != 0)
            break;
    }
    switch(selection) {
        case 1:
            if(chooseHero) {
                hero = sw;
                hero->ability = nullptr;
                heroNum = 0;
                chooseHero = false;
                buttons[0].SetText("Disarm");
                buttons[1].SetText("Enchantment");
                buttons[2].SetText("Make the strategy");
                title = "Choose ability";
                ab1 = new SwAb1;
                ab2 = new SwAb2;
                ab3 = new SwAb3;
            } else {
                NewAbility(this, selection);
            }
            break;
        case 2:
            if(chooseHero) {
                hero = ar;
                hero->ability = nullptr;
                heroNum = 1;
                chooseHero = false;
                buttons[0].SetText("Bleeding");
                buttons[1].SetText("Double Trouble");
                buttons[2].SetText("Weakness");
                title = "Choose ability";
                ab1 = new ArAb1;
                ab2 = new ArAb2;
                ab3 = new ArAb3;
            } else {
                NewAbility(this, selection);
            }
            break;
        case 3:
            if(chooseHero) {
                hero = pal;
                hero->ability = nullptr;
                heroNum = 2;
                chooseHero = false;
                buttons[0].SetText("God's infection");
                buttons[1].SetText("God's blessing");
                buttons[2].SetText("Chaotic offering");
                title = "Choose ability";
                ab1 = new PalAb1;
                ab2 = new PalAb2;
                ab3 = new PalAb3;
            } else {
                NewAbility(this, selection);
            }
            break;
    }
}

void ChooseStart::Draw() {
    static short selection = 0;
    static Vector2 mouse;
    static auto DrawHeroStats = [](ChooseStart* cs, short selection) {
        if(cs->buf != nullptr)
        {
            DrawText(cs->buf->nA.c_str(), WIDTH / 2 + 200, HEIGHT / 2 - 240, 30, cs->textCol);
            DrawText(TextFormat("Minimal DMG: %d", cs->buf->minNDMG), WIDTH / 2 + 200, HEIGHT / 2 - 200, 30, cs->textCol);
            DrawText(TextFormat("Miss chance: %d%%", cs->buf->mcN), WIDTH / 2 + 200, HEIGHT / 2 - 160, 30, cs->textCol);

            DrawText(cs->buf->hA.c_str(), WIDTH / 2 + 200, HEIGHT / 2 - 40, 30, cs->textCol);
            DrawText(TextFormat("Minimal DMG: %d", cs->buf->minHDMG), WIDTH / 2 + 200, HEIGHT / 2, 30, cs->textCol);
            DrawText(TextFormat("Miss chance: %d%%", cs->buf->mcH), WIDTH / 2 + 200, HEIGHT / 2 + 40, 30, cs->textCol);
            if (selection == 2)DrawText("Do three independent attacks", WIDTH / 2 + 200, HEIGHT / 2 + 80, 30, cs->textCol);
            else if (selection == 3)
                DrawText("As block gain 30% of\nminimal DMG value", WIDTH / 2 + 200, HEIGHT / 2 + 80, 30, cs->textCol);

            DrawText(cs->buf->sp.c_str(), WIDTH / 2 + 200, HEIGHT / 2 + 200, 30, cs->textCol);
            DrawText(TextFormat("Special value: %d", cs->buf->spValue), WIDTH / 2 + 200, HEIGHT / 2 + 240, 30, cs->textCol);
            if (selection == 3)
                DrawText("Randomly heal by a value\nfrom 1 to special value", WIDTH / 2 + 200, HEIGHT / 2 + 280, 30,
                         cs->textCol);
        }
    };
    static auto DrawHeroAbilities = [](ChooseStart* cs, short selection) {
        if(cs->ab != nullptr)
        {
            DrawText(cs->ab->abTitle.c_str(), WIDTH / 2 + 200, HEIGHT / 2 - 60, 30, cs->textCol);
            DrawText(TextFormat("Effect time in moves: %d", cs->ab->abilityVal), WIDTH / 2 + 200, HEIGHT / 2 - 20, 30, cs->textCol);
            DrawText(TextFormat("Cooldown in moves: %d", cs->ab->maxDelay), WIDTH / 2 + 200, HEIGHT / 2 + 20, 30, cs->textCol);
            switch (selection)
            {
                case 1:
                    switch (cs->heroNum) {
                        case 0:
                            DrawText("Disarms the enemy", WIDTH / 2 + 200, HEIGHT / 2 + 60, 30, cs->textCol);
                            break;
                        case 1:
                            DrawText("Enemy loses 10% of\nhis maximum HP", WIDTH / 2 + 200, HEIGHT / 2 + 60, 30,
                                     cs->textCol);
                            break;
                        case 2:
                            DrawText("Enemy deals damage to\nhimself with a 65% chance", WIDTH / 2 + 200,
                                     HEIGHT / 2 + 60, 30, cs->textCol);
                            break;
                    }
                break;
                case 2:
                    switch (cs->heroNum) {
                        case 0:
                            DrawText("Your abilities will have double\nvalues for two moves", WIDTH / 2 + 200,
                                     HEIGHT / 2 + 60, 30, cs->textCol);
                            break;
                        case 1:
                            DrawText("Your next ability will\nbe done twice", WIDTH / 2 + 200, HEIGHT / 2 + 60, 30,
                                     cs->textCol);
                            break;
                        case 2:
                            DrawText("Your next ability will be done\nmaximum accuracy with double value",
                                     WIDTH / 2 + 200, HEIGHT / 2 + 60, 30, cs->textCol);
                            break;
                    }
                break;
                case 3:
                    switch (cs->heroNum) {
                        case 0:
                            DrawText("Your next attack won't miss", WIDTH / 2 + 200, HEIGHT / 2 + 60, 30, cs->textCol);
                            break;
                        case 1:
                            DrawText("Next two moves enemy will\nattack with 0.5x damage", WIDTH / 2 + 200,
                                     HEIGHT / 2 + 60, 30, cs->textCol);
                            break;
                        case 2:
                            DrawText(
                                    "Deal damage or heal you and\nyour enemy by random value.\nAbility's value its maximum.",
                                    WIDTH / 2 + 200, HEIGHT / 2 + 60, 30, cs->textCol);
                            break;
                    }
                break;
            }
        }
    };
    BeginDrawing();
    DrawTexture(background, 0, 0, WHITE);

    DrawText(title.c_str(), WIDTH/2 - 120, HEIGHT/2 - 300, 30, textCol);

    mouse = GetMousePosition();
    if(mouse.x >= WIDTH/2 - 175 && mouse.x <= WIDTH/2 + 175
       && mouse.y >= HEIGHT/2 - 200 && mouse.y <= HEIGHT/2 - 100)
        selection = 1;
    else if(mouse.x >= WIDTH/2 - 175 && mouse.x <= WIDTH/2 + 175
            && mouse.y >= HEIGHT/2 && mouse.y <= HEIGHT/2 + 100)
        selection = 2;
    else if(mouse.x >= WIDTH/2 - 175 && mouse.x <= WIDTH/2 + 175
            && mouse.y >= HEIGHT/2 + 200 && mouse.y <= HEIGHT/2 + 300)
        selection = 3;

    switch (selection) {
        case 1:
            if(chooseHero) {
                buf = sw;
                DrawHeroStats(this, selection);
            } else {
                ab = ab1;
                DrawHeroAbilities(this, selection);
            }
            break;
        case 2:
            if(chooseHero) {
                buf = ar;
                DrawHeroStats(this, selection);
            } else {
                ab = ab2;
                DrawHeroAbilities(this, selection);
            }
            break;
        case 3:
            if(chooseHero) {
                buf = sw;
                DrawHeroStats(this, selection);
            } else {
                ab = ab3;
                DrawHeroAbilities(this, selection);
            }
            break;
    }

    for(auto& el: buttons)
        el.Show();

    ClearBackground(WHITE);
    EndDrawing();
}

bool ChooseStart::IsDone() {
    return hero != nullptr && hero->ability != nullptr;
}

ChooseStart::~ChooseStart() {
    *refHero = hero;
}
