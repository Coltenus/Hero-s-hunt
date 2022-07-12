#include "characters.h"
#include <string>
#include <iostream>
using namespace std;

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

Enemy::Enemy()
{
	maxHP = 0;
	hp = 0;
	rewGold = 0;
	modAt = 0;
	minNDMG = 0;
	minHDMG = 0;
	spValue = 0;
	enemType = 0;
	modInMoves = 0;
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
	sp = new char*[6];
	*sp = (char*)"Block";
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

Zombie::Zombie(unsigned short r)
{
	minNDMG = (short)(10 * (1 + 0.1 * (r-1)));
	minHDMG = (short)(18 * (1 + 0.1 * (r - 1)));
	spValue = (short)(5 * (1 + 0.1 * (r - 1)));
	maxHP = (short)(100 * (1 + 0.1 * (r - 1)));
	hp = maxHP;
	rewGold = 5;
	modAt = 1;
	enemType = 1;
	modInMoves = 0;
}

void Zombie::Attack(ROB** res, Hero** h)
{
	static short dmg;
	dmg = modAt * (rand() % 5 + minNDMG);
	if ((*h)->charType == 2 && (*h)->ability->numOfAb == 3 && (*h)->ability->statusDur > 0)
	{
		dmg /= 2;
		(*res)->hp += dmg;
	}
	if ((*h)->charType == 1 && (*h)->ability->numOfAb == 1 && modInMoves > 0)
	{
		modInMoves--;
		(*res)->enMiss = true;
	}
	else if ((*h)->charType == 3 && (*h)->ability->numOfAb == 1 && modInMoves > 0)
	{
		if (rand() % 100 + 1 > 65)
		{
			(*h)->block -= dmg;
			if ((*h)->block < 0)
			{
				hp -= (short)(0.25 * (*h)->block);
				(*h)->hp += (*h)->block;
				(*res)->hp -= (*h)->block;
				(*h)->block = 0;
			}
		}
		else
		{
			hp -= dmg;
			(*res)->enHP += dmg;
		}
		modInMoves--;
		(*res)->enMiss = false;
	}
	else
	{
		if ((*h)->buffsN == 0)
		{
			if (rand() % 100 + 1 > (*h)->evasion)
			{
				(*h)->block -= dmg;
				if ((*h)->block < 0)
				{
					(*h)->hp += (*h)->block;
					(*res)->hp -= (*h)->block;
					(*h)->block = 0;
				}
				(*res)->enMiss = false;
			}
			else (*res)->enMiss = true;
		}
		else (*res)->enMiss = true;
	}
	if ((*h)->charType == 2 && (*h)->ability->numOfAb == 1 && modInMoves > 0)
	{
		hp -= (short)(0.1 * maxHP);
		(*res)->enHP += (short)(0.1 * maxHP);
		modInMoves--;
	}
}

void Zombie::HeavyAttack(ROB** res, Hero** h)
{
	static short dmg;
	dmg = modAt * (rand() % 5 + minHDMG);
	if ((*h)->charType == 2 && (*h)->ability->numOfAb == 3 && (*h)->ability->statusDur > 0)
	{
		dmg /= 2;
		(*res)->hp += dmg;
	}
	if ((*h)->charType == 1 && (*h)->ability->numOfAb == 1 && modInMoves > 0)
	{
		modInMoves--;
		(*res)->enMiss = true;
	}
	else if ((*h)->charType == 3 && (*h)->ability->numOfAb == 1 && modInMoves > 0)
	{
		if (rand() % 100 + 1 > 65)
		{
			(*h)->block -= dmg;
			if ((*h)->block < 0)
			{
				hp -= (short)(0.25 * (*h)->block);
				(*h)->hp += (*h)->block;
				(*res)->hp -= (*h)->block;
				(*h)->block = 0;
			}
		}
		else
		{
			hp -= dmg;
			(*res)->enHP += dmg;
			
		}
		modInMoves--;
		(*res)->enMiss = false;
	}
	else
	{
		if ((*h)->buffsN == 0)
		{
			if (rand() % 100 + 1 > 2 * (*h)->evasion)
			{
				(*h)->block -= dmg;
				if ((*h)->block < 0)
				{
					hp -= (short)(0.25 * (*h)->block);
					(*h)->hp += (*h)->block;
					(*res)->hp -= (*h)->block;
					(*h)->block = 0;
				}
				(*res)->enMiss = false;
			}
			else (*res)->enMiss = true;
		}
		else (*res)->enMiss = true;
	}
	if ((*h)->charType == 2 && (*h)->ability->numOfAb == 1 && modInMoves > 0)
	{
		hp -= (short)(0.1 * maxHP);
		(*res)->enHP -= (short)(0.1 * maxHP);
		modInMoves--;
	}
}

void Zombie::Special(ROB** res)
{
	if (modInMoves > 0) modInMoves--;
	if (rand() % 100 + 1 > 30)
	{
		hp += spValue;
		(*res)->enHP -= spValue;
		(*res)->enMiss = false;
	}
	else (*res)->enMiss = true;
	if (hp > maxHP) hp = maxHP;
	modAt = 1;
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

Ability::Ability()
{
	abilityVal = 0;
	addAbilityVal = 0;
	curDelay = 0;
	maxDelay = 0;
	numOfAb = 0;
	statusDur = 0;
	abTitle = nullptr;
}

Ability::~Ability()
{
	if (abTitle != nullptr)
	{
		delete[] abTitle;
		abTitle = nullptr;
	}
}

SwAb1::SwAb1()
{
	curDelay = 0;
	maxDelay = 8;
	abilityVal = 2;
	addAbilityVal = 0;
	numOfAb = 1;
	statusDur = 0;
	abTitle = new char* [7];
	*abTitle = (char*)"Disarm";
}

SwAb1::~SwAb1()
{
	delete[] abTitle;
	abTitle = nullptr;
}

void SwAb1::activate(Hero** h, Enemy** en, ROB** res)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		(*en)->modInMoves = abilityVal;
		curDelay = maxDelay;
		(*res)->enDB += abilityVal;
		(*res)->curDel += maxDelay;
	}
}

ArAb1::ArAb1()
{
	curDelay = 0;
	maxDelay = 6;
	abilityVal = 2;
	addAbilityVal = 0;
	numOfAb = 1;
	statusDur = 0;
	abTitle = new char* [9];
	*abTitle = (char*)"Bleeding";
}

ArAb1::~ArAb1()
{
	delete[] abTitle;
	abTitle = nullptr;
}

void ArAb1::activate(Hero** h, Enemy** en, ROB** res)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		(*en)->modInMoves = abilityVal;
		curDelay = maxDelay;
		(*res)->enDB += abilityVal;
		(*res)->curDel += maxDelay;
	}
}

PalAb1::PalAb1()
{
	curDelay = 0;
	maxDelay = 8;
	abilityVal = 3;
	addAbilityVal = 0;
	numOfAb = 1;
	statusDur = 0;
	abTitle = new char* [16];
	*abTitle = (char*)"God's infection";
}

PalAb1::~PalAb1()
{
	delete[] abTitle;
	abTitle = nullptr;
}

void PalAb1::activate(Hero** h, Enemy** en, ROB** res)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		(*en)->modInMoves = abilityVal;
		curDelay = maxDelay;
		(*res)->enDB += abilityVal;
		(*res)->curDel += maxDelay;
	}
}

SwAb2::SwAb2()
{
	curDelay = 0;
	maxDelay = 6;
	abilityVal = 2;
	addAbilityVal = 0;
	numOfAb = 2;
	statusDur = 0;
	abTitle = new char* [12];
	*abTitle = (char*)"Enchantment";
}

SwAb2::~SwAb2()
{
	delete[] abTitle;
	abTitle = nullptr;
}

void SwAb2::activate(Hero** h, Enemy** en, ROB** res)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		statusDur = abilityVal;
		curDelay = maxDelay;
		(*res)->stDur += abilityVal;
		(*res)->curDel += maxDelay;
	}
}

SwAb3::SwAb3()
{
	curDelay = 0;
	maxDelay = 5;
	abilityVal = 1;
	addAbilityVal = 0;
	numOfAb = 3;
	statusDur = 0;
	abTitle = new char* [18];
	*abTitle = (char*)"Make the strategy";
}

SwAb3::~SwAb3()
{
	delete[] abTitle;
	abTitle = nullptr;
}

void SwAb3::activate(Hero** h, Enemy** en, ROB** res)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		statusDur = abilityVal;
		curDelay = maxDelay;
		(*res)->stDur += abilityVal;
		(*res)->curDel += maxDelay;
	}
}

ArAb2::ArAb2()
{
	curDelay = 0;
	maxDelay = 4;
	abilityVal = 1;
	addAbilityVal = 0;
	numOfAb = 2;
	statusDur = 0;
	abTitle = new char* [15];
	*abTitle = (char*)"Double Trouble";
}

ArAb2::~ArAb2()
{
	delete[] abTitle;
	abTitle = nullptr;
}

void ArAb2::activate(Hero** h, Enemy** en, ROB** res)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		statusDur = abilityVal;
		curDelay = maxDelay;
		(*res)->stDur += abilityVal;
		(*res)->curDel += maxDelay;
	}
}

ArAb3::ArAb3()
{
	curDelay = 0;
	maxDelay = 6;
	abilityVal = 2;
	addAbilityVal = 0;
	numOfAb = 3;
	statusDur = 0;
	abTitle = new char* [9];
	*abTitle = (char*)"Weakness";
}

ArAb3::~ArAb3()
{
	delete[] abTitle;
	abTitle = nullptr;
}

void ArAb3::activate(Hero** h, Enemy** en, ROB** res)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		(*en)->modInMoves = abilityVal;
		curDelay = maxDelay;
		(*res)->enDB += abilityVal;
		(*res)->curDel += maxDelay;
	}
}

PalAb2::PalAb2()
{
	curDelay = 0;
	maxDelay = 8;
	abilityVal = 1;
	addAbilityVal = 0;
	numOfAb = 2;
	statusDur = 0;
	abTitle = new char* [15];
	*abTitle = (char*)"God's blessing";
}

PalAb2::~PalAb2()
{
	delete[] abTitle;
	abTitle = nullptr;
}

void PalAb2::activate(Hero** h, Enemy** en, ROB** res)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		statusDur = abilityVal;
		curDelay = maxDelay;
		(*res)->stDur += abilityVal;
		(*res)->curDel += maxDelay;
	}
}

PalAb3::PalAb3()
{
	curDelay = 0;
	maxDelay = 8;
	abilityVal = 40;
	addAbilityVal = 0;
	numOfAb = 3;
	statusDur = 0;
	abTitle = new char* [17];
	*abTitle = (char*)"Chaotic offering";
}

PalAb3::~PalAb3()
{
	delete[] abTitle;
	abTitle = nullptr;
}

void PalAb3::activate(Hero** h, Enemy** en, ROB** res)
{
	static short buf;
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		buf = rand() % (abilityVal * 2 + 1) - abilityVal;
		(*h)->hp += buf;
		(*res)->hp -= buf;
		if ((*h)->hp > (*h)->maxHP) (*h)->hp = (*h)->maxHP;
		else if ((*h)->hp <= 0) (*h)->hp = 1;
		buf = rand() % (abilityVal * 2 + 1) - abilityVal;
		(*en)->hp += buf;
		(*res)->enHP -= buf;
		if ((*en)->hp > (*en)->maxHP) (*en)->hp = (*en)->maxHP;
		else if ((*en)->hp <= 0) (*en)->hp = 1;
		curDelay = maxDelay;
		(*res)->curDel += maxDelay;
	}
}

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
	itemTitle = new char* [strlen(name)+1];
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
