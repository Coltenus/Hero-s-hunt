#include "items.h"
#include "characters.h"
#include <iostream>
#include <string.h>

Item::Item()
{
	val = 0;
	numOfItem = 0;
	itemTitle = nullptr;
}

Item::~Item()
{
	if (itemTitle != nullptr)
	{
		delete[] itemTitle;
		itemTitle = nullptr;
	}
}

void Item::setVal(short val)
{
	this->val = val;
}

void Item::setName(char* name)
{
	if (itemTitle != nullptr)
	{
		delete[] itemTitle;
	}
	itemTitle = new char* [strlen(name) + 1];
	*itemTitle = name;
}

void Item::setNum(short num)
{
	numOfItem = num;
}

short Item::getVal()
{
	return val;
}

char** Item::getName()
{
	return itemTitle;
}

short Item::getNum()
{
	return numOfItem;
}

void Item::eraseName()
{
	if (itemTitle != nullptr)
	{
		delete[] itemTitle;
		itemTitle = nullptr;
	}
}

Healing::Healing(short i) : Item()
{
	setVal(10 + rand() % (i + 1));
	setName((char*)"Heal Potion");
	setNum(1);
}

Healing::~Healing()
{
	eraseName();
}

void Healing::activate(Hero** h, Enemy** en, ROB** res)
{
	(*h)->hp += getVal();
	(*res)->hp -= getVal();
	if ((*h)->hp > (*h)->maxHP) (*h)->hp = (*h)->maxHP;
}

Block::Block(short i) : Item()
{
	setVal(10 + rand() % (i + 1));
	setName((char*)"Shield");
	setNum(2);
}

Block::~Block()
{
	eraseName();
}

void Block::activate(Hero** h, Enemy** en, ROB** res)
{
	(*h)->block += getVal();
	(*res)->block += getVal();
}

DmgPotion::DmgPotion(short i) : Item()
{
	setVal(20 + rand() % (i + 1));
	setName((char*)"Fire potion");
	setNum(3);
}

DmgPotion::~DmgPotion()
{
	eraseName();
}

void DmgPotion::activate(Hero** h, Enemy** en, ROB** res)
{
	(*en)->hp -= getVal();
	(*res)->enHP += getVal();
	if ((*en)->hp < 1) (*en)->hp = 1;
}

UpMaxHP::UpMaxHP(short i) : Item()
{
	setVal(5 + (short)(rand() % (i + 1) / 4));
	setName((char*)"Fairy potion");
	setNum(4);
}

UpMaxHP::~UpMaxHP()
{
	eraseName();
}

void UpMaxHP::activate(Hero** h, Enemy** en, ROB** res)
{
	(*h)->maxHP += getVal();
}