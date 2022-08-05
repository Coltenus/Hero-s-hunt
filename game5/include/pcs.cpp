#include "characters.h"
#include <string>
#include <iostream>

Hero::Hero()
{
	nA = nullptr;
	hA = nullptr;
	sp = nullptr;
	maxHP = 0;
	hp = 0;
	block = 0;
	evasion = 0;
	buffsN = 0;
	minNDMG = 0;
	minHDMG = 0;
	spValue = 0;
	gold = 0;
	mcN = 0;
	mcH = 0;
	ability = nullptr;
	charType = 0;
	slotN = 2;
	items = new Item*[slotN];
	items[0] = new Healing(1);
	items[0]->setName((char*)"Empty slot");
	items[0]->setVal(0);
	items[0]->setNum(0);
	items[1] = new Healing(1);
	items[1]->setName((char*)"Empty slot");
	items[1]->setVal(0);
	items[1]->setNum(0);
}

Hero::~Hero()
{
	if (nA != nullptr)
	{
		delete[] nA;
		nA = nullptr;
	}
	if (hA != nullptr)
	{
		delete[] hA;
		hA = nullptr;
	}
	if (sp != nullptr)
	{
		delete[] sp;
		sp = nullptr;
	}
	if (ability != nullptr)
	{
		delete ability;
		ability = nullptr;
	}
	if (items != nullptr)
	{
		delete[] items;
		items = nullptr;
	}
}

Swordsman::Swordsman() : Hero()
{
	minNDMG = 10;
	mcN = 20;
	nA = new char*[13];
	*nA = (char*)"Sword attack";
	minHDMG = 30;
	mcH = 35;
	hA = new char*[12];
	*hA = (char*)"Sword swing";
	spValue = 15;
	sp = new char*[7];
	*sp = (char*)"Shield";
	maxHP = 100;
	hp = 100;
	gold = 0;
	evasion = 18;
	buffsN = 0;
	charType = 1;
}

Swordsman::~Swordsman()
{
	delete[] nA;
	delete[] hA;
	delete[] sp;
	nA = nullptr;
	hA = nullptr;
	sp = nullptr;
	delete[] items;
	items = nullptr;
}

void Swordsman::Attack(ROB** res, Enemy** e)
{
	static short dmg;
	dmg = rand() % 10 + minNDMG;
	(*res)->enHP += dmg;
	if (ability->numOfAb == 3 && ability->statusDur > 0)
	{
		(*e)->hp -= dmg;
		(*res)->hMiss = false;
	}
	else if (rand() % 100 + 1 > mcN)
	{
		if (ability->numOfAb == 2 && ability->statusDur > 0)
		{
			(*res)->enHP += dmg;
			dmg *= 2;
		}
		(*e)->hp -= dmg;
		(*res)->hMiss = false;
	}
	else (*res)->hMiss = true;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Swordsman::HeavyAttack(ROB** res, Enemy** e)
{
	static short dmg;
	dmg = rand() % 10 + minHDMG;
	(*res)->enHP = dmg;
	if (ability->numOfAb == 3 && ability->statusDur > 0)
	{
		(*e)->hp -= dmg;
		(*res)->hMiss = false;
	}
	else if (rand() % 100 + 1 > mcH)
	{
		if (ability->numOfAb == 2 && ability->statusDur > 0)
		{
			(*res)->enHP += dmg;
			dmg *= 2;
		}
		(*e)->hp -= dmg;
		(*res)->hMiss = false;
	}
	else (*res)->hMiss = true;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Swordsman::Special(ROB** res)
{
	(*res)->block = spValue;
	if (ability->numOfAb == 2 && ability->statusDur > 0)
	{
		(*res)->block += spValue;
		block += spValue;
	}
	block += spValue;
	(*res)->hMiss = false;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Swordsman::setAbility(Ability* ab)
{
	ability = ab;
}

void Swordsman::useAbility(ROB** res, Hero** h, Enemy** en)
{
	if (ability->statusDur > 0) ability->statusDur--;
	ability->activate(h, en, res);
	(*res)->hMiss = false;
}

Archer::Archer() : Hero()
{
	minNDMG = 5;
	mcN = 30;
	nA = new char*[12];
	*nA = (char*)"Triple shot";
	minHDMG = 20;
	mcH = 0;
	hA = new char*[14];
	*hA = (char*)"Accurate shot";
	spValue = 1;
	sp = new char*[12];
	*sp = (char*)"Invisiblity";
	maxHP = 80;
	hp = 80;
	gold = 0;
	evasion = 26;
	buffsN = 0;
	charType = 2;
}

Archer::~Archer()
{
	delete[] nA;
	delete[] hA;
	delete[] sp;
	nA = nullptr;
	hA = nullptr;
	sp = nullptr;
	delete[] items;
	items = nullptr;
}

void Archer::Attack(ROB** res, Enemy** e)
{
	static short shotCount;
	static int* i;
	static int dmg;
	dmg = 0;
	shotCount = 3;
	if (buffsN > 0) buffsN--;
	i = new int;
	if (ability->numOfAb == 2 && ability->statusDur > 0) shotCount *= 2;
	*i = 0;
	while (*i < shotCount)
	{
		if (rand() % 100 + 1 > mcN)
		{
			dmg += rand() % 6 + minNDMG;
		}
		(*i)++;
	}
	(*e)->hp -= dmg;
	(*res)->enHP += dmg;
	if(dmg > 0) (*res)->hMiss = false;
	else (*res)->hMiss = true;
	delete i;
	i = nullptr;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Archer::HeavyAttack(ROB** res, Enemy** e)
{
	static int dmg;
	dmg = rand() % 4 + minHDMG;
	if (buffsN > 0) buffsN--;
	if (ability->numOfAb == 2 && ability->statusDur > 0) dmg *= 2;
	(*e)->hp -= dmg;
	(*res)->enHP += dmg;
	(*res)->hMiss = false;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Archer::Special(ROB** res)
{
	if (buffsN > 0) buffsN--;
	if (ability->numOfAb == 2 && ability->statusDur > 0)
	{
		buffsN += spValue * 2;
		(*res)->bDur = spValue * 2;
	}
	else
	{
		buffsN += spValue;
		(*res)->bDur = spValue;
	}
	(*res)->hMiss = false;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Archer::setAbility(Ability* ab)
{
	ability = ab;
}

void Archer::useAbility(ROB** res, Hero** h, Enemy** en)
{
	if (ability->statusDur > 0) ability->statusDur--;
	ability->activate(h, en, res);
	(*res)->hMiss = false;
}

Paladin::Paladin() : Hero()
{
	minNDMG = 20;
	mcN = 25;
	nA = new char* [12];
	*nA = (char*)"Sword swing";
	minHDMG = 14;
	mcH = 15;
	hA = new char* [14];
	*hA = (char*)"Shield attack";
	spValue = 15;
	sp = new char* [16];
	*sp = (char*)"Help from above";
	maxHP = 100;
	hp = 100;
	gold = 0;
	evasion = 10;
	buffsN = 0;
	charType = 3;
}

Paladin::~Paladin()
{
	delete[] nA;
	delete[] hA;
	delete[] sp;
	nA = nullptr;
	hA = nullptr;
	sp = nullptr;
	delete[] items;
	items = nullptr;
}

void Paladin::Attack(ROB** res, Enemy** e)
{
	static int dmg;
	if (buffsN > 0) buffsN--;
	dmg = rand() % 5 + minNDMG;
	if (ability->numOfAb == 2 && ability->statusDur > 0)
	{
		dmg *= 2;
		(*e)->hp -= dmg;
		(*res)->enHP += dmg;
		(*res)->hMiss = false;
	}
	else if (rand() % 100 + 1 > mcN)
	{
		(*e)->hp -= dmg;
		(*res)->enHP += dmg;
		(*res)->hMiss = false;
	}
	else (*res)->hMiss = true;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Paladin::HeavyAttack(ROB** res, Enemy** e)
{
	static int dmg, bl;
	if (buffsN > 0) buffsN--;
	dmg = minHDMG;
	bl = (short)(minHDMG * 0.3);
	if (ability->numOfAb == 2 && ability->statusDur > 0)
	{
		dmg *= 2;
		(*e)->hp -= dmg;
		(*res)->enHP += dmg;
		bl *= 2;
		(*res)->hMiss = false;
	}
	else if (rand() % 100 + 1 > mcH)
	{
		(*e)->hp -= dmg;
		(*res)->enHP += dmg;
		(*res)->hMiss = false;
	}
	else (*res)->hMiss = true;
	block += bl;
	(*res)->block += bl;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Paladin::Special(ROB** res)
{
	static int HP;
	HP = rand() % (spValue + 1);
	if (ability->numOfAb == 2 && ability->statusDur > 0)
	{
		HP = spValue * 2;
	}
	hp += HP;
	if (hp > maxHP) hp = maxHP;
	(*res)->hp -= HP;
	(*res)->hMiss = false;
	buffsN = 3;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Paladin::setAbility(Ability* ab)
{
	ability = ab;
}

void Paladin::useAbility(ROB** res, Hero** h, Enemy** en)
{
	if (ability->statusDur > 0) ability->statusDur--;
	ability->activate(h, en, res);
	(*res)->hMiss = false;
}

void Hero::setItem(Item* it)
{
	short sl = findFreeSlot();
	if (sl != slotN)
	{
		delete items[sl];
		items[sl] = it;
	}
}

void Hero::useItem(Hero** h, Enemy** en, short i, ROB** res)
{
	items[i]->activate(h, en, res);
	clearSlot(i);
}

void Hero::clearSlot(short i)
{
	delete items[i];
	items[i] = nullptr;
	items[i] = new Healing(1);
	items[i]->setName((char*)"Empty slot");
	items[i]->setVal(0);
	items[i]->setNum(0);
}

short Hero::findFreeSlot()
{
	short i = 0;
	while (i < slotN && items[i]->getNum() != 0)
	{
		i++;
	}
	return i;
}
