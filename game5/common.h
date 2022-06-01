#pragma once

#define WIDTH 1600
#define HEIGHT 900

typedef struct _rewards
{
	unsigned short gold, hp, minNDMG, minHDMG, evasion, spValue;
	bool isActive;
}Rewards;

typedef struct _save
{
	struct chOfStats
	{
		short dmgN, dmgH, hp, maxHP, evasion, spValue;
	};
	struct enSt
	{
		short dmgN, dmgH, hp, maxHP, rewGold, spV, modAt, enType;
	};
	int order;
	int minutes, hours, days;
	unsigned short charact;
	chOfStats stats;
	enSt enemyStats;
	unsigned short gold;
	unsigned short roomNum;
	unsigned short roomType;
}Save;

typedef struct _info
{
	char username[20];
}Info;