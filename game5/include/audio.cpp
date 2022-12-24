#include "audio.h"

Audio::Audio(char** path)
{
	ms = LoadMusicStream(*path);
	PlayMusicStream(ms);
	SetMusicVolume(ms, (float)0.1);
}

Audio::~Audio()
{
	StopMusicStream(ms);
	UnloadMusicStream(ms);
}

void Audio::setParameters(char** path)
{
	ms = LoadMusicStream(*path);
	PlayMusicStream(ms);
	SetMusicVolume(ms, (float)0.1);
}

void Audio::update()
{
	if (IsKeyPressed(KEY_M))
	{
		StopMusicStream(ms);
		SetMusicVolume(ms, (float)0);
	}
	if (IsKeyPressed(KEY_N))
	{
		SetMusicVolume(ms, (float)0.1);
		PlayMusicStream(ms);
	}
	UpdateMusicStream(ms);
}

void Audio::stop()
{
	StopMusicStream(ms);
}

void Audio::start()
{
	PlayMusicStream(ms);
}
