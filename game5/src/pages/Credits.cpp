//
// Created by colte on 04.01.2023.
//

#include "Credits.h"

Credits::Credits(PageType *pt) : Page(pt){
    buttons = {
            Button({20, 100}, {100, 80}, "Back", 30, LIGHT_BLUE, true, TEXT_COLOR)
    };
    {
        short i = 1;
        for(auto& el: buttons)
            el.SetValue(i++);
    }
    textFrames = {
            TextFrame("At first you have to choose one of there different      characters. "
                      "Then each next  room generate randomly. "
                      "Each enemy has two different    attacks and one special     action. "
                      "Strength of enemy   depends on number of room   you reached. \n\n"
                      "Controls\n"
                      "Right Click - next room in Shops and Rest rooms\n"
                      "M - mute/unmute music\n"
                      "Escape - back to menu"
                      , {WIDTH/2 - 300, HEIGHT/2 - 300}, {600, 600}, 34, true),
            TextFrame("Made by Coltenus", {WIDTH - 300, HEIGHT - 50}, {300, 50}, 30, false),
    };
}

Credits *Credits::CreateCredits(PageType *pt) {
    if(page != nullptr)
        return nullptr;
    else {
        page = new Credits(pt);
        return page;
    }
}

Credits::~Credits() {
    page = nullptr;
}

void Credits::Update() {
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
            *pageType = MainPage;
            active = false;
            break;
    }
    for(auto& el: textFrames)
        el.Update();
}

void Credits::Draw() {
    BeginDrawing();
    ClearBackground(MAINMENU_BG);

    DrawText("Credits", 100, 20, 30, TEXT_COLOR);

    for(auto& el: buttons)
        el.Show();

    for(auto& el: textFrames)
        el.Show();

    EndDrawing();
}
