//
// Created by colte on 26.12.2022.
//

#include "Audio.h"

Audio::Audio() : isMuted(false), isActive(false), num(-1) {}

Audio::Audio(const char* path, short n) : isMuted(false), isActive(true), num(n)
{
    InitAudioDevice();
    ms = LoadMusicStream(path);
    PlayMusicStream(ms);
    SetMusicVolume(ms, (float)0.1);
}

Audio::~Audio()
{
    StopMusicStream(ms);
    UnloadMusicStream(ms);
    CloseAudioDevice();
}

void Audio::setParameters(const char* path, short n)
{
    isActive = true;
    isMuted = false;
    num = n;
    UnloadMusicStream(ms);
    ms = LoadMusicStream(path);
    PlayMusicStream(ms);
    SetMusicVolume(ms, (float)0.1);
}

void Audio::Update()
{
    if(isActive) {
        if (IsKeyPressed(KEY_M)) {
            if (!isMuted) {
                SetMusicVolume(ms, (float) 0);
                isMuted = true;
            }
            else {
                SetMusicVolume(ms, (float) 0.1);
                isMuted = false;
            }
        }
        UpdateMusicStream(ms);
    }
}

short Audio::GetLastNum() {
    return num;
}
