//
// Created by colte on 26.12.2022.
//

#ifndef GAME5_AUDIO_H
#define GAME5_AUDIO_H

#include "raylib.h"

class Audio
{
private:
    Music ms;
    bool isMuted, isActive;
    short num;
public:
    Audio();
    explicit Audio(const char*, short);
    ~Audio();
    void setParameters(const char*, short);
    void Update();
    short GetLastNum();
};


#endif //GAME5_AUDIO_H
