#pragma once

class Hero;
class Enemy;

class Hero
{
public:
	Hero();
	~Hero();
public:
	virtual void Attack(Enemy** e) = 0;
	virtual void HeavyAttack(Enemy** e) = 0;
	virtual void Special() = 0;
public:
	char* nA, * hA, * sp;
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
	virtual void Attack(Hero** h) = 0;
	virtual void HeavyAttack(Hero** h) = 0;
	virtual void Special() = 0;
public:
	short maxHP, hp, rewGold, modAt, enemType;
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

class  Archer : public Hero
{
public:
	Archer();
	~Archer();
	void Attack(Enemy** e) override;
	void HeavyAttack(Enemy** e) override;
	void Special() override;
};