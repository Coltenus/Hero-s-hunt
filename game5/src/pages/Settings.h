//
// Created by colte on 04.01.2023.
//

#ifndef GAME5_SETTINGS_H
#define GAME5_SETTINGS_H

#include "Page.h"
#include "../utils/Button.h"
#include "../utils/RadioButton.h"

class Settings : public Page {
private:
    std::vector<RadioButton> rButtons;
    explicit Settings(PageType*);

public:
    static Settings* page;
    static Settings* CreateSettings(PageType*);
    ~Settings() override;
    void Update() override;
    void Draw() override;
};


#endif //GAME5_SETTINGS_H
