//
// Created by colte on 04.01.2023.
//

#ifndef GAME5_CHOOSESAVE_H
#define GAME5_CHOOSESAVE_H

#include "Page.h"
#include "../utils/Button.h"
#include "../utils/Save.h"

class ChooseSave : public Page {
private:
    Save* save;
    short currentSave;
    explicit ChooseSave(PageType*, Save*);

public:
    static ChooseSave* page;
    static ChooseSave* CreateChooseSave(PageType*, Save*);
    ~ChooseSave() override;
    void Update() override;
    void Draw() override;
};


#endif //GAME5_CHOOSESAVE_H
