#ifndef HH_AUDIO_H
#define HH_AUDIO_H

#include "raylib.h"

class Audio
{
private:
	Music ms{};
public:
	Audio() = default;
	explicit Audio(char**);
	~Audio();
	void setParameters(char**);
	void update();
	void stop();
	void start();
};

#endif