//
// Created by colte on 04.01.2023.
//

#ifndef GAME5_CREDITS_H
#define GAME5_CREDITS_H

#include "Page.h"
#include "../utils/Button.h"
#include "../utils/TextFrame.h"

class Credits : public Page {
private:
    std::vector<TextFrame> textFrames;
    explicit Credits(PageType*);

public:
    static Credits* page;
    static Credits* CreateCredits(PageType*);
    ~Credits() override;
    void Update() override;
    void Draw() override;
};


#endif //GAME5_CREDITS_H
