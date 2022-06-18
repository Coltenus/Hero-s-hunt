#pragma once

#include "common.h"

class Hero;
class Enemy;

class Item
{
private:
	short val, numOfItem;
	char** itemTitle;
public:
	Item();
	~Item();
	virtual void activate(Hero**, Enemy**) = 0;
	void setVal(short);
	void setName(char*);
	void setNum(short);
	short getVal();
	char** getName();
	short getNum();
	void eraseName();
};

class Healing : public Item
{
public:
	Healing(short);
	~Healing();
	void activate(Hero**, Enemy**) override;
};

class Block : public Item
{
public:
	Block(short);
	~Block();
	void activate(Hero**, Enemy**) override;
};

class DmgPotion : public Item
{
public:
	DmgPotion(short);
	~DmgPotion();
	void activate(Hero**, Enemy**) override;
};

class UpMaxHP : public Item
{
public:
	UpMaxHP(short);
	~UpMaxHP();
	void activate(Hero**, Enemy**) override;
};

class Ability
{
public:
	short abilityVal, addAbilityVal;
	unsigned short curDelay, maxDelay, numOfAb, statusDur;
	char** abTitle;
public:
	Ability();
	virtual ~Ability();
public:
	virtual void activate(Hero**, Enemy**) = 0;
};

class SwAb1 : public Ability
{
public:
	SwAb1();
	~SwAb1() override;
public:
	void activate(Hero**, Enemy**);
};

class SwAb2 : public Ability
{
public:
	SwAb2();
	~SwAb2() override;
public:
	void activate(Hero**, Enemy**);
};

class SwAb3 : public Ability
{
public:
	SwAb3();
	~SwAb3() override;
public:
	void activate(Hero**, Enemy**);
};

class ArAb1 : public Ability
{
public:
	ArAb1();
	~ArAb1() override;
public:
	void activate(Hero**, Enemy**);
};

class ArAb2 : public Ability
{
public:
	ArAb2();
	~ArAb2() override;
public:
	void activate(Hero**, Enemy**);
};

class ArAb3 : public Ability
{
public:
	ArAb3();
	~ArAb3() override;
public:
	void activate(Hero**, Enemy**);
};

class PalAb1 : public Ability
{
public:
	PalAb1();
	~PalAb1() override;
public:
	void activate(Hero**, Enemy**);
};

class PalAb2 : public Ability
{
public:
	PalAb2();
	~PalAb2() override;
public:
	void activate(Hero**, Enemy**);
};

class PalAb3 : public Ability
{
public:
	PalAb3();
	~PalAb3() override;
public:
	void activate(Hero**, Enemy**);
};

class Hero
{
public:
	Hero();
	virtual ~Hero() = 0;
public:
	virtual void Attack(ROB**, Enemy**) = 0;
	virtual void HeavyAttack(ROB**, Enemy**) = 0;
	virtual void Special(ROB**) = 0;
	virtual void setAbility(Ability*) = 0;
	virtual void useAbility(ROB**, Hero**, Enemy**) = 0;
	void setItem(Item*);
	void useItem(Hero**, Enemy**, short);
	void clearSlot(short);
	short findFreeSlot();
public:
	Ability *ability;
	Item** items;
	char** nA, ** hA, ** sp;
	short maxHP, hp, block, evasion, buffsN;
	short minNDMG, mcN;
	short minHDMG, mcH;
	short spValue;
	unsigned short gold;
	short charType;
	short slotN;
};

class Enemy
{
public:
	Enemy();
public:
	virtual void Attack(ROB**, Hero**) = 0;
	virtual void HeavyAttack(ROB**, Hero**) = 0;
	virtual void Special(ROB**) = 0;
public:
	short maxHP, hp, rewGold, modAt, modInMoves, enemType;
	int minNDMG;
	int minHDMG;
	int spValue;
};

class Swordsman : public Hero
{
public:
	Swordsman();
	~Swordsman() override;
	void Attack(ROB**, Enemy**) override;
	void HeavyAttack(ROB**, Enemy**) override;
	void Special(ROB**) override;
	void setAbility(Ability*) override;
	void useAbility(ROB**, Hero**, Enemy**) override;
};

class Zombie : public Enemy
{
public:
	Zombie(unsigned short);
	void Attack(ROB**, Hero**) override;
	void HeavyAttack(ROB**, Hero**) override;
	void Special(ROB**) override;
};

class Archer : public Hero
{
public:
	Archer();
	~Archer() override;
	void Attack(ROB**, Enemy**) override;
	void HeavyAttack(ROB**, Enemy**) override;
	void Special(ROB**) override;
	void setAbility(Ability*) override;
	void useAbility(ROB**, Hero**, Enemy**) override;
};

class Paladin : public Hero
{
public:
	Paladin();
	~Paladin() override;
	void Attack(ROB**, Enemy**) override;
	void HeavyAttack(ROB**, Enemy**) override;
	void Special(ROB**) override;
	void setAbility(Ability*) override;
	void useAbility(ROB**, Hero**, Enemy**) override;
};