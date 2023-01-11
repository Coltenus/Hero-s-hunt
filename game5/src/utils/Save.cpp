//
// Created by colte on 04.01.2023.
//

#include "Save.h"
#include <filesystem>
#include <unistd.h>

Save::Save() {
    if(fopen_s(&globalData, "global_data", "rb") != 0)
    {
        std::string buf("GAME5");
        for(int i = 0;auto& el: buf)
            gd.title[i++] = el;
        gd.isDarkMode = true;
        gd.currentSave = 1;

        fopen_s(&globalData, "global_data", "wb");
        fwrite(&gd, sizeof(GlobalData), 1, globalData);
    }
    else
    {
        fread(&gd, sizeof(GlobalData), 1, globalData);
    }
    fclose(globalData);
    IsDarkMode = gd.isDarkMode;
    currentSave = gd.currentSave;
    if(!std::filesystem::is_directory("saves"))
        mkdir("saves");
}

Save *Save::CreateSave() {
    if(pSave != nullptr)
        return nullptr;
    else {
        pSave = new Save();
        return pSave;
    }
}

Save::~Save() {
    if(pSave != nullptr) {
        fopen_s(&globalData, "global_data", "rb+");
        fread(&gd.title, sizeof(char), 5, globalData);
        gd.isDarkMode = IsDarkMode;
        gd.currentSave = currentSave;
        fseek(globalData, SEEK_SET, 0);
        fwrite(&gd, sizeof(GlobalData), 1, globalData);
        fclose(globalData);
        pSave = nullptr;
    }
}

void Save::SaveProgress(SaveData* data) {
    std::string buf("saves/save");
    buf += std::to_string(currentSave);
    fopen_s(&save, buf.c_str(), "wb");
    if(data != nullptr)
        sd = *data;
    else ClearSaveData(sd);
    fwrite(&sd, sizeof(SaveData), 1, save);
    fclose(save);
}

SaveData Save::GetProgress() {
    std::string buf("saves/save");
    buf += std::to_string(currentSave);
    if(fopen_s(&save, buf.c_str(), "rb") != 0)
    {
        ClearSaveData(sd);
        fopen_s(&save, buf.c_str(), "wb");
        fwrite(&sd, sizeof(SaveData), 1, save);
    }
    else
    {
        fread(&sd, sizeof(SaveData), 1, save);
    }
    fclose(save);
    return sd;
}

void Save::SetCurrentSave(short sv) {
    currentSave = sv;
}

short Save::GetCurrentSave() const {
    return currentSave;
}

void Save::ClearSaveData(SaveData& sd) {
    sd.roomNumber = 0;
    sd.hs.character = 0;
    sd.hs.ability = 0;
    sd.hs.gold = 0;
    sd.hs.stats.maxHP = 0;
    sd.hs.stats.hp = 0;
    sd.hs.stats.spValue = 0;
    sd.hs.stats.evasion = 0;
    sd.hs.stats.block = 0;
    sd.hs.stats.curDelay = 0;
    sd.hs.stats.buffDur = 0;
    sd.hs.stats.dmgN = 0;
    sd.hs.stats.dmgH = 0;
    sd.hs.stats.statDur = 0;
}
