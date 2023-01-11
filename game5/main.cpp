//
// Created by colte on 29.12.2022.
//
#include <iostream>
#include "src/pages.h"
#include "src/common.h"
#include "src/pages/Gameplay.h"
#include "src/utils/Save.h"
#include "src/utils/Audio.h"


Gameplay* Gameplay::page = nullptr;
MainMenu* MainMenu::page = nullptr;
Settings* Settings::page = nullptr;
Credits* Credits::page = nullptr;
ChooseSave* ChooseSave::page = nullptr;
Save* Save::pSave = nullptr;
bool IsDarkMode = true;

int main()
{
    setbuf(stdout, nullptr);
    bool isShouldExit = false;
    PageType pageType = MainPage;
    Page* page = nullptr;
    Save* save = Save::CreateSave();
    InitWindow(WIDTH, HEIGHT, "Game 5");
    Audio audio("res/sound0.mp3", 0);
    SetTargetFPS(60);
    auto changeOption = [&]() {
        if(page != nullptr)
        {
            delete page;
            page = nullptr;
        }
        if(pageType == GameplayPage)
            audio.setParameters("res/sound1.mp3", 1);
        else if(audio.GetLastNum() == 1)
            audio.setParameters("res/sound0.mp3", 0);
        switch (pageType) {
            case GameplayPage:
                page = Gameplay::CreateGameplay(&pageType, save);
                break;
            case MainPage:
                page = MainMenu::CreateMainMenu(&pageType);
                break;
            case SettingsPage:
                page = Settings::CreateSettings(&pageType);
                break;
            case CreditsPage:
                page = Credits::CreateCredits(&pageType);
                break;
            case SavePage:
                page = ChooseSave::CreateChooseSave(&pageType, save);
                break;
            case Exit:
                isShouldExit = true;
                break;
        }
    };
    changeOption();
    while (!isShouldExit)
    {
        audio.Update();
        page->Draw();
        page->Update();
        if(!page->GetStatus())
            changeOption();
        if(WindowShouldClose())
            isShouldExit = true;
    }
    CloseWindow();
    delete save;
    save = nullptr;
    return 0;
}
