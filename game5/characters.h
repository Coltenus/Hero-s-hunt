#pragma once

class Hero;
class Enemy;

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
	int order;
	int minutes, hours, days;
	unsigned short charact;
	chOfStats stats;
	unsigned short gold;
	unsigned short roomNum;
}Save;

typedef struct _info
{
	char username[20];
}Info;

class Hero
{
public:
	Hero(){}
	~Hero(){}
public:
	virtual void Attack(Enemy** e) = 0;
	virtual void HeavyAttack(Enemy** e) = 0;
	virtual void Special() = 0;
public:
	char* nA, * hA, * sp;
	short maxHP, hp, block, evasion;
	int minNDMG;
	int minHDMG;
	int spValue;
	unsigned short gold;
};

class Enemy
{
public:
	Enemy() {}
	~Enemy() {}
public:
	virtual void Attack(Hero** h) = 0;
	virtual void HeavyAttack(Hero** h) = 0;
	virtual void Special() = 0;
public:
	short maxHP, hp, rewGold;
	int minNDMG;
	int minHDMG;
	int spValue;
};

class Warrior : public Hero
{
public:
	Warrior();
	~Warrior();
	void Attack(Enemy** e) override;
	void HeavyAttack(Enemy** e) override;
	void Special() override;
};

class Zombie : public Enemy
{
public:
	Zombie(unsigned short);
	~Zombie();
	void Attack(Hero** h) override;
	void HeavyAttack(Hero** h) override;
	void Special() override;
};