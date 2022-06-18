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

Swordsman::Swordsman()
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
}

void Swordsman::Attack(ROB** res, Enemy** e)
{
	(*res)->hAct = 1;
	(*res)->hVal = rand() % 10 + minNDMG;
	if (ability->numOfAb == 3 && ability->statusDur > 0)
	{
		(*e)->hp -= (*res)->hVal;
		(*res)->hMiss = false;
	}
	else if (rand() % 100 + 1 > mcN)
	{
		if (ability->numOfAb == 2 && ability->statusDur > 0) (*res)->hVal *= 2;
		(*e)->hp -= (*res)->hVal;
		(*res)->hMiss = false;
	}
	else (*res)->hMiss = true;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Swordsman::HeavyAttack(ROB** res, Enemy** e)
{
	(*res)->hAct = 2;
	(*res)->hVal = rand() % 10 + minHDMG;
	if (ability->numOfAb == 3 && ability->statusDur > 0)
	{
		(*e)->hp -= (*res)->hVal;
		(*res)->hMiss = false;
	}
	else if (rand() % 100 + 1 > mcH)
	{
		if (ability->numOfAb == 2 && ability->statusDur > 0) (*res)->hVal *= 2;
		(*e)->hp -= (*res)->hVal;
		(*res)->hMiss = false;
	}
	else (*res)->hMiss = true;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Swordsman::Special(ROB** res)
{
	(*res)->hAct = 3;
	(*res)->hVal = spValue;
	if (ability->numOfAb == 2 && ability->statusDur > 0) (*res)->hVal *= 2;
	block += (*res)->hVal;
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
	ability->activate(h, en);
	(*res)->hAct = 4;
	(*res)->hVal = ability->abilityVal;
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
	(*res)->enAct = 1;
	(*res)->enVal = modAt * (rand() % 5 + minNDMG);
	if ((*h)->charType == 2 && (*h)->ability->numOfAb == 3 && (*h)->ability->statusDur > 0)
		(*res)->enVal = (short)((*res)->enVal / 2);
	if ((*h)->charType == 1 && (*h)->ability->numOfAb == 1 && modInMoves > 0)
	{
		modInMoves--;
		(*res)->enMiss = true;
	}
	else if ((*h)->charType == 3 && (*h)->ability->numOfAb == 1 && modInMoves > 0)
	{
		if (rand() % 100 + 1 > 65)
		{
			(*h)->block -= (*res)->enVal;
			if ((*h)->block < 0)
			{
				hp -= (short)(0.25 * (*h)->block);
				(*h)->hp += (*h)->block;
				(*h)->block = 0;
			}
		}
		else
		{
			hp -= (*res)->enVal;
			(*res)->enVal = -(*res)->enVal;
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
				(*h)->block -= (*res)->enVal;
				if ((*h)->block < 0)
				{
					(*h)->hp += (*h)->block;
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
		modInMoves--;
	}
}

void Zombie::HeavyAttack(ROB** res, Hero** h)
{
	(*res)->enAct = 2;
	(*res)->enVal = modAt * (rand() % 5 + minHDMG);
	if ((*h)->charType == 2 && (*h)->ability->numOfAb == 3 && (*h)->ability->statusDur > 0)
		(*res)->enVal = (short)((*res)->enVal / 2);
	if ((*h)->charType == 1 && (*h)->ability->numOfAb == 1 && modInMoves > 0)
	{
		modInMoves--;
		(*res)->enMiss = true;
	}
	else if ((*h)->charType == 3 && (*h)->ability->numOfAb == 1 && modInMoves > 0)
	{
		if (rand() % 100 + 1 > 65)
		{
			(*h)->block -= (*res)->enVal;
			if ((*h)->block < 0)
			{
				hp -= (short)(0.25 * (*h)->block);
				(*h)->hp += (*h)->block;
				(*h)->block = 0;
			}
		}
		else
		{
			hp -= (*res)->enVal;
			(*res)->enVal = -(*res)->enVal;
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
				(*h)->block -= (*res)->enVal;
				if ((*h)->block < 0)
				{
					hp -= (short)(0.25 * (*h)->block);
					(*h)->hp += (*h)->block;
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
		modInMoves--;
	}
}

void Zombie::Special(ROB** res)
{
	(*res)->enAct = 3;
	(*res)->enVal = spValue;
	if (modInMoves > 0) modInMoves--;
	if (rand() % 100 + 1 > 30)
	{
		hp += spValue;
		(*res)->enMiss = false;
	}
	else (*res)->enMiss = true;
	if (hp > maxHP) hp = maxHP;
	modAt = 1;
}

Archer::Archer()
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
}

void Archer::Attack(ROB** res, Enemy** e)
{
	static short shotCount;
	static int* i;
	static bool fl;
	shotCount = 3;
	fl = false;
	if (buffsN > 0) buffsN--;
	i = new int;
	(*res)->hAct = 1;
	(*res)->hVal = 0;
	if (ability->numOfAb == 2 && ability->statusDur > 0) shotCount *= 2;
	*i = 0;
	while (*i < shotCount)
	{
		if (rand() % 100 + 1 > mcN)
		{
			(*res)->hVal += rand() % 6 + minNDMG;
			fl = true;
		}
		(*i)++;
	}
	(*e)->hp -= (*res)->hVal;
	if(fl) (*res)->hMiss = false;
	else (*res)->hMiss = true;
	delete i;
	i = nullptr;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Archer::HeavyAttack(ROB** res, Enemy** e)
{
	if (buffsN > 0) buffsN--;
	(*res)->hAct = 2;
	(*res)->hVal = rand() % 4 + minHDMG;
	if (ability->numOfAb == 2 && ability->statusDur > 0) (*res)->hVal *= 2;
	(*e)->hp -= (*res)->hVal;
	(*res)->hMiss = false;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Archer::Special(ROB** res)
{
	(*res)->hAct = 3;
	if (buffsN > 0) buffsN--;
	if (ability->numOfAb == 2 && ability->statusDur > 0)
	{
		buffsN += spValue * 2;
		(*res)->hVal = spValue * 2;
	}
	else
	{
		buffsN += spValue;
		(*res)->hVal = spValue;
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
	ability->activate(h, en);
	(*res)->hAct = 4;
	(*res)->hVal = ability->abilityVal;
	(*res)->hMiss = false;
}

Paladin::Paladin()
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
}

void Paladin::Attack(ROB** res, Enemy** e)
{
	if (buffsN > 0) buffsN--;
	(*res)->hAct = 1;
	(*res)->hVal = rand() % 5 + minNDMG;
	if (ability->numOfAb == 2 && ability->statusDur > 0)
	{
		(*res)->hVal *= 2;
		(*e)->hp -= (*res)->hVal;
		(*res)->hMiss = false;
	}
	else if (rand() % 100 + 1 > mcN)
	{
		(*e)->hp -= (*res)->hVal;
		(*res)->hMiss = false;
	}
	else (*res)->hMiss = true;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Paladin::HeavyAttack(ROB** res, Enemy** e)
{
	if (buffsN > 0) buffsN--;
	(*res)->hAct = 2;
	(*res)->hVal = minHDMG;
	(*res)->hAdd = (short)(minHDMG * 0.3);
	if (ability->numOfAb == 2 && ability->statusDur > 0)
	{
		(*res)->hVal *= 2;
		(*e)->hp -= (*res)->hVal;
		(*res)->hAdd *= 2;
		(*res)->hMiss = false;
	}
	else if (rand() % 100 + 1 > mcH)
	{
		(*e)->hp -= (*res)->hVal;
		(*res)->hMiss = false;
	}
	else (*res)->hMiss = true;
	block += (*res)->hAdd;
	if (ability->statusDur > 0) ability->statusDur--;
}

void Paladin::Special(ROB** res)
{
	(*res)->hVal = rand() % (spValue + 1);
	if (ability->numOfAb == 2 && ability->statusDur > 0)
	{
		(*res)->hVal = spValue * 2;
	}
	hp += (*res)->hVal;
	if (hp > maxHP) hp = maxHP;
	(*res)->hAct = 3;
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
	ability->activate(h, en);
	(*res)->hAct = 4;
	(*res)->hVal = ability->abilityVal;
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

void SwAb1::activate(Hero** h, Enemy** en)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		(*en)->modInMoves = abilityVal;
		curDelay = maxDelay;
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

void ArAb1::activate(Hero** h, Enemy** en)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		(*en)->modInMoves = abilityVal;
		curDelay = maxDelay;
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

void PalAb1::activate(Hero** h, Enemy** en)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		(*en)->modInMoves = abilityVal;
		curDelay = maxDelay;
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

void SwAb2::activate(Hero** h, Enemy** en)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		statusDur = abilityVal;
		curDelay = maxDelay;
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

void SwAb3::activate(Hero** h, Enemy** en)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		statusDur = abilityVal;
		curDelay = maxDelay;
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

void ArAb2::activate(Hero** h, Enemy** en)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		statusDur = abilityVal;
		curDelay = maxDelay;
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

void ArAb3::activate(Hero** h, Enemy** en)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		(*en)->modInMoves = abilityVal;
		curDelay = maxDelay;
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

void PalAb2::activate(Hero** h, Enemy** en)
{
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		statusDur = abilityVal;
		curDelay = maxDelay;
	}
}

PalAb3::PalAb3()
{
	curDelay = 0;
	maxDelay = 8;
	abilityVal = 0;
	addAbilityVal = 0;
	numOfAb = 3;
	statusDur = 0;
	abTitle = new char* [8];
	*abTitle = (char*)"HP swap";
}

PalAb3::~PalAb3()
{
	delete[] abTitle;
	abTitle = nullptr;
}

void PalAb3::activate(Hero** h, Enemy** en)
{
	static short buf;
	if (curDelay < 0) curDelay = 0;
	if (curDelay > 0) curDelay--;
	else
	{
		buf = (*h)->hp;
		(*h)->hp = (*en)->hp;
		(*en)->hp = buf;
		if ((*h)->hp > (*h)->maxHP) (*h)->hp = (*h)->maxHP;
		if ((*en)->hp > (*en)->maxHP) (*en)->hp = (*en)->maxHP;
		curDelay = maxDelay;
	}
}
