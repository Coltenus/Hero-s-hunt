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
	virtual void activate(Hero**, Enemy**, ROB**) = 0;
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
	void activate(Hero**, Enemy**, ROB**) override;
};

class Block : public Item
{
public:
	Block(short);
	~Block();
	void activate(Hero**, Enemy**, ROB**) override;
};

class DmgPotion : public Item
{
public:
	DmgPotion(short);
	~DmgPotion();
	void activate(Hero**, Enemy**, ROB**) override;
};

class UpMaxHP : public Item
{
public:
	UpMaxHP(short);
	~UpMaxHP();
	void activate(Hero**, Enemy**, ROB**) override;
};