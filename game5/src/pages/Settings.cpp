//
// Created by colte on 04.01.2023.
//

#include "Settings.h"

Settings::Settings(PageType *pt) : Page(pt){
    buttons = {
            Button({20, 100}, {100, 80}, "Back", 30, LIGHT_BLUE, true, TEXT_COLOR)
    };
    rButtons = {
            RadioButton("Light", {WIDTH/2 - 100, HEIGHT/2 - 200}, {100, 80}, 30, !IsDarkMode),
            RadioButton("Dark", {WIDTH/2 - 100, HEIGHT/2 - 100}, {100, 80}, 30, IsDarkMode)
    };
    {
        short i = 1;
        for(auto& el: buttons)
            el.SetValue(i++);
        for(auto& el: rButtons)
            el.SetValue(i++);
    }
}

Settings *Settings::CreateSettings(PageType *pt) {
    if(page != nullptr)
        return nullptr;
    else {
        page = new Settings(pt);
        return page;
    }
}

Settings::~Settings() {
    page = nullptr;
}

void Settings::Update() {
    static short selection;
    selection = 0;
    for(auto& el: buttons)
    {
        el.Click(selection);
        if(selection != 0)
            break;
    }
    if(selection == 0) {
        for (auto &el: rButtons) {
            el.Click(selection);
            if (selection != 0)
                break;
        }
    }
    switch (selection) {
        case 1:
            *pageType = MainPage;
            active = false;
            break;
        case 2:
            IsDarkMode = false;
            rButtons[0].SetState(true);
            rButtons[1].SetState(false);
            for(auto &el: buttons)
                el.SetTextColor(TEXT_COLOR);
            break;
        case 3:
            IsDarkMode = true;
            rButtons[0].SetState(false);
            rButtons[1].SetState(true);
            for(auto &el: buttons)
                el.SetTextColor(TEXT_COLOR);
            break;
    }
}

void Settings::Draw() {
    BeginDrawing();
    ClearBackground(MAINMENU_BG);

    DrawText("Settings", 100, 20, 30, TEXT_COLOR);

    for(auto& el: buttons)
        el.Show();

    DrawText("Choose theme", WIDTH/2 - 100, HEIGHT/2 - 300, 30, TEXT_COLOR);

    for(auto& el: rButtons)
        el.Show();

    EndDrawing();
}
