//
// Created by colte on 04.01.2023.
//

#include "ChooseSave.h"

ChooseSave::ChooseSave(PageType *pt, Save* sv) : Page(pt), save(sv) {
        buttons = {
                Button({20, 100}, {100, 80}, "Back", 30, LIGHT_BLUE, true, TEXT_COLOR),
                Button({WIDTH/2 - 100, HEIGHT/2 - 200}, {200, 80}, "Save 1", 30, LIGHT_GREEN, true, TEXT_COLOR),
                Button({WIDTH/2 - 100, HEIGHT/2 - 100}, {200, 80}, "Save 2", 30, LIGHT_GREEN, true, TEXT_COLOR),
                Button({WIDTH/2 - 100, HEIGHT/2}, {200, 80}, "Save 3", 30, LIGHT_GREEN, true, TEXT_COLOR),
                Button({WIDTH/2 - 220, HEIGHT/2 - 200}, {100, 80}, "Clear", 30, LIGHT_GREEN, true, TEXT_COLOR),
                Button({WIDTH/2 - 220, HEIGHT/2 - 100}, {100, 80}, "Clear", 30, LIGHT_GREEN, true, TEXT_COLOR),
                Button({WIDTH/2 - 220, HEIGHT/2}, {100, 80}, "Clear", 30, LIGHT_GREEN, true, TEXT_COLOR)
        };
        {
            short i = 1;
            for(auto& el: buttons)
                el.SetValue(i++);
        }
        currentSave = save->GetCurrentSave() - 1;
}

ChooseSave *ChooseSave::CreateChooseSave(PageType *pt, Save* sv) {
    if(page != nullptr)
        return nullptr;
    else {
        page = new ChooseSave(pt, sv);
        return page;
    }
}

ChooseSave::~ChooseSave() {
    page = nullptr;
}

void ChooseSave::Update() {
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
        case 2:
            save->SetCurrentSave(1);
            currentSave = 0;
            break;
        case 3:
            save->SetCurrentSave(2);
            currentSave = 1;
            break;
        case 4:
            save->SetCurrentSave(3);
            currentSave = 2;
            break;
        case 5:
        case 6:
        case 7:
            short buf = save->GetCurrentSave();
            save->SetCurrentSave(selection-4);
            save->SaveProgress(nullptr);
            save->SetCurrentSave(buf);
            break;
    }
}

void ChooseSave::Draw() {
    BeginDrawing();
    ClearBackground(MAINMENU_BG);

    DrawText("Saves", 100, 20, 30, TEXT_COLOR);

    for(auto& el: buttons)
        el.Show();

    DrawRectangleV({WIDTH/2 + 140, HEIGHT/2 - 180 + currentSave * 100.f}, {40, 40}, GREEN);

    EndDrawing();
}
