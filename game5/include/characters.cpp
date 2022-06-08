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
}

Enemy::~Enemy()
{

}

Swordsman::Swordsman()
{

	minNDMG = 10;
	nA = new char*[13];
	*nA = (char*)"Sword attack";
	minHDMG = 30;
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
	if (rand() % 100 + 1 > 20)
	{
		(*e)->hp -= (*res)->hVal;
		(*res)->hMiss = false;
	}
	else (*res)->hMiss = true;
}

void Swordsman::HeavyAttack(ROB** res, Enemy** e)
{
	(*res)->hAct = 2;
	(*res)->hVal = rand() % 10 + minHDMG;
	if (rand() % 100 + 1 > 35)
	{
		(*e)->hp -= (*res)->hVal;
		(*res)->hMiss = false;
	}
	else (*res)->hMiss = true;
}

void Swordsman::Special(ROB** res)
{
	(*res)->hAct = 3;
	block += spValue;
	(*res)->hVal = spValue;
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
}

Zombie::~Zombie()
{

}

void Zombie::Attack(ROB** res, Hero** h)
{
	(*res)->enAct = 1;
	(*res)->enVal = modAt * (rand() % 5 + minNDMG);
	if ((*h)->buffsN < 0) (*h)->buffsN = 0;
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
	modAt = 1;
}

void Zombie::HeavyAttack(ROB** res, Hero** h)
{
	(*res)->enAct = 2;
	(*res)->enVal = modAt * (rand() % 5 + minHDMG);
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
	modAt = 1;
}

void Zombie::Special(ROB** res)
{
	(*res)->enAct = 3;
	(*res)->enVal = spValue;
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
	nA = new char*[12];
	*nA = (char*)"Triple shot";
	minHDMG = 20;
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
	static int* i;
	static bool fl;
	fl = false;
	if (buffsN > 0) buffsN--;
	i = new int;
	(*res)->hAct = 1;
	(*res)->hVal = 0;
	*i = 0;
	while (*i < 3)
	{
		if (rand() % 100 + 1 > 30)
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
}

void Archer::HeavyAttack(ROB** res, Enemy** e)
{
	if (buffsN > 0) buffsN--;
	(*res)->hAct = 2;
	(*res)->hVal = rand() % 4 + minHDMG;
	(*e)->hp -= (*res)->hVal;
	(*res)->hMiss = false;
}

void Archer::Special(ROB** res)
{
	(*res)->hAct = 3;
	if (buffsN > 0) buffsN--;
	buffsN += spValue;
	(*res)->hVal = spValue;
	(*res)->hMiss = false;
}

Paladin::Paladin()
{
	minNDMG = 20;
	nA = new char* [12];
	*nA = (char*)"Sword swing";
	minHDMG = 14;
	hA = new char* [14];
	*hA = (char*)"Shield attack";
	spValue = 15;
	sp = new char* [15];
	*sp = (char*)"God's blessing";
	maxHP = 100;
	hp = 100;
	gold = 0;
	evasion = 10;
	buffsN = 0;
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
	if (rand() % 100 + 1 > 25)
	{
		(*e)->hp -= (*res)->hVal;
		(*res)->hMiss = false;
	}
	else (*res)->hMiss = true;
}

void Paladin::HeavyAttack(ROB** res, Enemy** e)
{
	if (buffsN > 0) buffsN--;
	(*res)->hAct = 2;
	(*res)->hVal = minHDMG;
	if (rand() % 100 + 1 > 25)
	{
		(*e)->hp -= (*res)->hVal;
		(*res)->hMiss = false;
	}
	else (*res)->hMiss = true;
	(*res)->hAdd = (short)minHDMG * 0.3;
	block += (*res)->hAdd;
}

void Paladin::Special(ROB** res)
{
	(*res)->hVal = rand() % (spValue + 1);
	hp += (*res)->hVal;
	if (hp > maxHP) hp = maxHP;
	(*res)->hAct = 3;
	(*res)->hMiss = false;
	buffsN = 3;
}
