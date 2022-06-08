#pragma once
#include "raylib.hpp"

class Audio
{
private:
	Music ms;
	bool isMuted;
public:
	Audio();
	Audio(char**);
	~Audio();
	void setParameters(char**);
	void update();
	void stop();
	void start();
};