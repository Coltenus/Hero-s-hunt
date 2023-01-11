//
// Created by colte on 04.01.2023.
//

#ifndef GAME5_SAVE_H
#define GAME5_SAVE_H

#include <cstdio>
#include "../common.h"

class Save {
private:
    struct GlobalData {
        char title[5];
        bool isDarkMode;
        short currentSave;
    } gd;
    struct SaveData sd;
    short currentSave;
    FILE *globalData, *save;
    Save();

public:
    static Save* pSave;
    static Save* CreateSave();
    ~Save();
    void SaveProgress(SaveData*);
    SaveData GetProgress();
    void SetCurrentSave(short);
    [[nodiscard]] short GetCurrentSave() const;
    static void ClearSaveData(SaveData&);
};


#endif //GAME5_SAVE_H
