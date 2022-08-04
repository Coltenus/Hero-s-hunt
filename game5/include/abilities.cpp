#include "characters.h"
#include <iostream>

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