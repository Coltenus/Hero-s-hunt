#ifndef GAME5_COMMON_H
#define GAME5_COMMON_H

#define WIDTH 1600
#define HEIGHT 900

//typedef struct _rewards
//{
//	unsigned short gold, hp, minNDMG, minHDMG, evasion, spValue;
//	bool isActive;
//	short item1, item2;
//}Rewards;

//typedef struct _save
//{
//	struct chOfStats
//	{
//		short dmgN, dmgH, hp, maxHP, evasion, spValue, buffN, block, curDelay, statDur;
//	};
//	struct enSt
//	{
//		short dmgN, dmgH, hp, maxHP, rewGold, spV, modAt, enType, modIM;
//	};
//	struct _item {
//		short val, num;
//	};
//	int order;
//	int minutes, hours, days;
//	unsigned short charact, ability;
//	chOfStats stats;
//	_item item1, item2;
//	enSt enemyStats;
//	unsigned short gold;
//	unsigned short roomNum;
//	unsigned short roomType;
//}Save;

//typedef struct _info
//{
//	char username[20];
//}Info;
//
//typedef struct _resultOfBattle
//{
//	short hp, block, bDur, curDel, stDur, enHP, enDB;
//	bool hMiss, enMiss;
//}ROB;

enum PageType : unsigned char {
    MainPage = 1,
    SettingsPage,
    CreditsPage,
    Exit,
    GameplayPage,
    SavePage
};

enum RoomType : unsigned char {
    ChooseRoom = 1,
    TransitionFrame,
    RewardFrame,
    DeadFrame,
    BattleRoom,
    ShopRoom,
    RestRoom
};

typedef struct HeroData {
    short charType, numOfAb, evasion;
    short hp, curDel, statusDur, buffDur, block, maxHP;
} HeroData;

typedef struct EnemyData {
    short enemyType;
    short hp, debuff, spVal;
} EnemyData;

typedef struct GameplayData {
    RoomType roomType;
    HeroData hero;
    EnemyData enemy;
} GameplayData;

extern bool IsDarkMode;

#define BG_MENU ((IsDarkMode) ? DARKGRAY : LIGHTGRAY)
#define BTN_MENU GRAY
#define TEXT_COLOR ((IsDarkMode) ? WHITE : BLACK)
#define BG_GP ((IsDarkMode) ? DARKBLUE : GREEN)
#define LIGHT_BLUE Color{60, 120, 240, 200}
#define LIGHT_GREEN Color{90, 240, 70, 200}
#define LIGHT_YELLOW Color{253, 255, 70, 200}
#define BTN_HIGHLIGHT LIGHT_BLUE
#define MAINMENU_BG ((IsDarkMode) ? Color{16, 18, 77, 200} : Color{29, 23, 235, 200} )

typedef struct _RewardStats {
    short gold, hp, nDMG, hDMG, spVal, evasion;
} RewardStats;

struct SaveData {
    struct _stats {
        short dmgN, dmgH, hp, maxHP, evasion, spValue, buffDur, block, curDelay, statDur;
    };
    struct _item {
		short val, num;
	};
    struct heroStats {
        short character, ability, gold;
        _stats stats;
        _item i1, i2;
	};
    short roomNumber;
    heroStats hs;
};

#endif //GAME5_COMMON_H