#pragma once

#include "characters.h"
#include "common.h"
#include "audio.h"

bool Battle(Hero**, Enemy**, Rewards**, Save**, Info*, double*, bool, Audio*);
bool Shop(Hero**, Save**, double*, Info*, Audio*);
bool RestRoom(Hero**, Save**, double*, Info*, Audio*);