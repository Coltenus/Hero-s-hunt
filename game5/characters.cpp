#include "characters.h"
#include <string>
#include <iostream>
using namespace std;

string wa1 = "Sword attack";
string wa2 = "Sword swing";
string ws1 = "Block";

string aa1 = "Triple shot";
string aa2 = "Accurate shot";
string as1 = "Invisible";

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

Warrior::Warrior()
{
	static short* i;
	i = new short;
	minNDMG = 10;
	nA = new char[wa1.length()+1];
	*i = 0;
	while (*i <= wa1.length())
	{
		nA[*i] = wa1[*i];
		(*i)++;
	}
	minHDMG = 30;
	hA = new char[wa2.length()+1];
	*i = 0;
	while (*i <= wa2.length())
	{
		hA[*i] = wa2[*i];
		(*i)++;
	}
	spValue = 15;
	sp = new char[ws1.length()+1];
	*i = 0;
	while (*i <= ws1.length())
	{
		sp[*i] = ws1[*i];
		(*i)++;
	}
	maxHP = 100;
	hp = 100;
	gold = 0;
	evasion = 15;
	buffsN = 0;
	delete i;
	i = nullptr;
}

Warrior::~Warrior()
{
	delete[] nA;
	delete[] hA;
	delete[] sp;
	nA = nullptr;
	hA = nullptr;
	sp = nullptr;
}

void Warrior::Attack(Enemy** e)
{
	if (rand() % 100 + 1 > 20)
	{
		(*e)->hp -= rand() % 10 + minNDMG;
	}
}

void Warrior::HeavyAttack(Enemy** e)
{
	if (rand() % 100 + 1 > 35)
	{
		(*e)->hp -= rand() % 10 + minHDMG;
	}
}

void Warrior::Special()
{
	block += spValue;
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

void Zombie::Attack(Hero** h)
{
	if ((*h)->buffsN < 0) (*h)->buffsN = 0;
	if ((*h)->buffsN == 0)
	{
		if (rand() % 100 + 1 > (*h)->evasion)
		{
			(*h)->block -= modAt * (rand() % 5 + minNDMG);
			if ((*h)->block < 0)
			{
				(*h)->hp += (*h)->block;
				(*h)->block = 0;
			}
		}
	}
	modAt = 1;
}

void Zombie::HeavyAttack(Hero** h)
{
	if ((*h)->buffsN == 0)
	{
		if (rand() % 100 + 1 > 2 * (*h)->evasion)
		{
			(*h)->block -= modAt * (rand() % 5 + minHDMG);
			if ((*h)->block < 0)
			{
				hp -= (short)(0.25 * (*h)->block);
				(*h)->hp += (*h)->block;
				(*h)->block = 0;
			}
		}
	}
	modAt = 1;
}

void Zombie::Special()
{
	if (rand() % 100 + 1 > 30) hp += spValue;
	if (hp > maxHP) hp = maxHP;
	modAt = 1;
}

Archer::Archer()
{
	static short* i;
	i = new short;
	minNDMG = 5;
	nA = new char[aa1.length() + 1];
	*i = 0;
	while (*i <= aa1.length())
	{
		nA[*i] = aa1[*i];
		(*i)++;
	}
	minHDMG = 20;
	hA = new char[aa2.length() + 1];
	*i = 0;
	while (*i <= aa2.length())
	{
		hA[*i] = aa2[*i];
		(*i)++;
	}
	spValue = 1;
	sp = new char[as1.length() + 1];
	*i = 0;
	while (*i <= as1.length())
	{
		sp[*i] = as1[*i];
		(*i)++;
	}
	maxHP = 80;
	hp = 80;
	gold = 0;
	evasion = 25;
	buffsN = 0;
	delete i;
	i = nullptr;
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

void Archer::Attack(Enemy** e)
{
	static int* i;
	if (buffsN > 0) buffsN--;
	i = new int;
	*i = 0;
	while (*i < 3)
	{
		if (rand() % 100 + 1 > 30)
		{
			(*e)->hp -= rand() % 6 + minNDMG;
		}
		(*i)++;
	}
	delete i;
	i = nullptr;
}

void Archer::HeavyAttack(Enemy** e)
{
	if (buffsN > 0) buffsN--;
	(*e)->hp -= rand() % 4 + minHDMG;
}

void Archer::Special()
{
	if (buffsN > 0) buffsN--;
	buffsN += spValue;
}
