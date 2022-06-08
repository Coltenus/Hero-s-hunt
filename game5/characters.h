#pragma once

#include "common.h"

class Hero;
class Enemy;

class Hero
{
public:
	Hero();
	~Hero();
public:
	virtual void Attack(ROB**, Enemy**) = 0;
	virtual void HeavyAttack(ROB**, Enemy**) = 0;
	virtual void Special(ROB**) = 0;
public:
	char** nA, ** hA, ** sp;
	short maxHP, hp, block, evasion, buffsN;
	int minNDMG;
	int minHDMG;
	int spValue;
	unsigned short gold;
};

class Enemy
{
public:
	Enemy();
	~Enemy();
public:
	virtual void Attack(ROB**, Hero**) = 0;
	virtual void HeavyAttack(ROB**, Hero**) = 0;
	virtual void Special(ROB**) = 0;
public:
	short maxHP, hp, rewGold, modAt, enemType;
	int minNDMG;
	int minHDMG;
	int spValue;
};

class Swordsman : public Hero
{
public:
	Swordsman();
	~Swordsman();
	void Attack(ROB**, Enemy**) override;
	void HeavyAttack(ROB**, Enemy**) override;
	void Special(ROB**) override;
};

class Zombie : public Enemy
{
public:
	Zombie(unsigned short);
	~Zombie();
	void Attack(ROB**, Hero**) override;
	void HeavyAttack(ROB**, Hero**) override;
	void Special(ROB**) override;
};

class Archer : public Hero
{
public:
	Archer();
	~Archer();
	void Attack(ROB**, Enemy**) override;
	void HeavyAttack(ROB**, Enemy**) override;
	void Special(ROB**) override;
};

class Paladin : public Hero
{
public:
	Paladin();
	~Paladin();
	void Attack(ROB**, Enemy**) override;
	void HeavyAttack(ROB**, Enemy**) override;
	void Special(ROB**) override;
};