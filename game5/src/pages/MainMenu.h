//
// Created by colte on 04.01.2023.
//

#ifndef GAME5_MAINMENU_H
#define GAME5_MAINMENU_H

#include "Page.h"
#include "../utils/Button.h"

class MainMenu : public Page {
private:
    explicit MainMenu(PageType*);

public:
    static MainMenu* page;
    static MainMenu* CreateMainMenu(PageType*);
    ~MainMenu() override;
    void Update() override;
    void Draw() override;
};


#endif //GAME5_MAINMENU_H
