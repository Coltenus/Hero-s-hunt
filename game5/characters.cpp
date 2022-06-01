#include "characters.h"
#include <string>
#include <iostream>
using namespace std;

string wa1 = "Sword attack";
string wa2 = "Sword swing";
string ws1 = "Block";


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
	if (rand() % 100 + 1 > 15)
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
}

Zombie::~Zombie()
{

}

void Zombie::Attack(Hero** h)
{
	if (rand() % 100 + 1 > (*h)->evasion)
	{
		(*h)->block -= rand() % 5 + minNDMG;
		if ((*h)->block < 0)
		{
			(*h)->hp += (*h)->block;
			(*h)->block = 0;
		}
	}
}

void Zombie::HeavyAttack(Hero** h)
{
	if (rand() % 100 + 1 > 2 * (*h)->evasion)
	{
		(*h)->block -= rand() % 5 + minHDMG;
		if ((*h)->block < 0)
		{
			hp -= (short)(0.25 * (*h)->block);
			(*h)->hp += (*h)->block;
			(*h)->block = 0;
		}
	}
}

void Zombie::Special()
{
	if (rand() % 100 + 1 > 30) hp += spValue;
	if (hp > maxHP) hp = maxHP;
}

