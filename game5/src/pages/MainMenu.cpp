//
// Created by colte on 04.01.2023.
//

#include "MainMenu.h"
#include <raylib.h>
#include "../common.h"

MainMenu::MainMenu(PageType *pt) : Page(pt){
    buttons = {
            Button({WIDTH/2 - 150, HEIGHT/2 - 300}, {300, 100}, "Start", 30, LIGHT_BLUE, true, TEXT_COLOR),
            Button({WIDTH/2 - 150, HEIGHT/2 - 150}, {300, 100}, "Settings", 30, LIGHT_BLUE, true, TEXT_COLOR),
            Button({WIDTH/2 - 150, HEIGHT/2}, {300, 100}, "Credits", 30, LIGHT_BLUE, true, TEXT_COLOR),
            Button({WIDTH/2 - 150, HEIGHT/2 + 150}, {300, 100}, "Exit", 30, LIGHT_BLUE, true, TEXT_COLOR),
            Button({WIDTH/2 + 200, HEIGHT/2 - 300}, {100, 100}, "Saves", 30, LIGHT_BLUE, true, TEXT_COLOR)
    };
    {
        short i = 1;
        for (auto &el: buttons)
            el.SetValue(i++);
    }
}

MainMenu *MainMenu::CreateMainMenu(PageType *pt) {
    if(page != nullptr)
        return nullptr;
    else {
        page = new MainMenu(pt);
        return page;
    }
}

MainMenu::~MainMenu() {
    page = nullptr;
}

void MainMenu::Update() {
    static short selection;
    selection = 0;
    for(auto& el: buttons)
    {
        el.Click(selection);
        if(selection != 0)
            break;
    }
    switch (selection) {
        case 1:
            *pageType = GameplayPage;
            active = false;
            break;
        case 2:
            *pageType = SettingsPage;
            active = false;
            break;
        case 3:
            *pageType = CreditsPage;
            active = false;
            break;
        case 4:
            *pageType = Exit;
            active = false;
            break;
        case 5:
            *pageType = SavePage;
            active = false;
            break;
    }
}

void MainMenu::Draw() {
    BeginDrawing();
    ClearBackground(MAINMENU_BG);

    for(auto& el: buttons)
        el.Show();

    EndDrawing();
}
