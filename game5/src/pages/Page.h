//
// Created by colte on 26.12.2022.
//

#ifndef GAME5_PAGE_H
#define GAME5_PAGE_H

#include <vector>
#include "../common.h"
#include "../utils/Button.h"

class Page {
public:
    PageType* pageType;
    bool active;
    std::vector<Button> buttons;
    explicit Page(PageType*);
    virtual ~Page() = default;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    [[nodiscard]] bool GetStatus() const {return active;}
    void SetStatus(bool st) {active = st;}
};


#endif //GAME5_PAGE_H
