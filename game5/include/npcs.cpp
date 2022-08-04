#include "characters.h"
#include <iostream>

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
	buffSp = 0;
}

Zombie::Zombie(unsigned short r)
{
	minNDMG = (short)(10 * (1 + 0.1 * (r - 1)));
	minHDMG = (short)(18 * (1 + 0.1 * (r - 1)));
	spValue = (short)(5 * (1 + 0.1 * (r - 1)));
	maxHP = (short)(100 * (1 + 0.1 * (r - 1)));
	hp = maxHP;
	rewGold = 5 + rand() % 3;
	modAt = 1;
	enemType = 1;
	modInMoves = 0;
	buffSp = 0;
}

void Zombie::Attack(ROB** res, Hero** h)
{
	static short dmg;
	dmg = modAt * (rand() % 5 + minNDMG);
	if ((*h)->charType == 2 && (*h)->ability->numOfAb == 3 && (*h)->ability->statusDur > 0)
	{
		dmg /= 2;
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
			(*res)->block -= dmg;
			if ((*h)->block < 0)
			{
				(*res)->block -= (*h)->block;
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
				(*res)->block -= dmg;
				if ((*h)->block < 0)
				{
					(*res)->block -= (*h)->block;
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
			(*res)->block -= dmg;
			if ((*h)->block < 0)
			{
				(*res)->block -= (*h)->block;
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
			if (rand() % 100 + 1 > 2 * (*h)->evasion + 10)
			{
				(*h)->block -= dmg;
				(*res)->block -= dmg;
				if ((*h)->block < 0)
				{
					(*res)->block -= (*h)->block;
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
		(*res)->enHP += (short)(0.1 * maxHP);
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

Rogue::Rogue(unsigned short r)
{
	minNDMG = (short)(20 * (1 + 0.1 * (r - 1)));
	minHDMG = (short)(12 * (1 + 0.1 * (r - 1)));
	spValue = (short)(5 * (1 + 0.1 * (r - 1)));
	maxHP = (short)(75 * (1 + 0.1 * (r - 1)));
	hp = maxHP;
	rewGold = 8 + rand() % 5;
	modAt = 1;
	enemType = 2;
	modInMoves = 0;
	buffSp = 0;
}

void Rogue::Attack(ROB** res, Hero** h)
{
	static short dmg;
	dmg = modAt * (rand() % 5 + minNDMG);
	if ((*h)->charType == 2 && (*h)->ability->numOfAb == 3 && (*h)->ability->statusDur > 0)
	{
		dmg /= 2;
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
			(*res)->block -= dmg;
			if ((*h)->block < 0)
			{
				(*res)->block -= (*h)->block;
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
			if (rand() % 100 + 1 > (*h)->evasion + 5)
			{
				(*h)->block -= dmg;
				(*res)->block -= dmg;
				if ((*h)->block < 0)
				{
					(*res)->block -= (*h)->block;
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
	if (enemType == 2 && buffSp > 0)
	{
		(*h)->hp -= spValue;
		(*res)->hp += spValue;
		buffSp--;
	}
}

void Rogue::HeavyAttack(ROB** res, Hero** h)
{
	static short dmg;
	dmg = modAt * (rand() % 5 + minHDMG);
	if ((*h)->charType == 2 && (*h)->ability->numOfAb == 3 && (*h)->ability->statusDur > 0)
	{
		dmg /= 2;
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
			(*res)->block -= dmg;
			if ((*h)->block < 0)
			{
				(*res)->block -= (*h)->block;
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
			if (rand() % 100 + 1 > 2 * (*h)->evasion - 8)
			{
				(*h)->block -= dmg;
				(*res)->block -= dmg;
				if ((*h)->block < 0)
				{
					(*res)->block -= (*h)->block;
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
	if (enemType == 2 && buffSp > 0)
	{
		(*h)->hp -= spValue;
		(*res)->hp += spValue;
		buffSp--;
	}
}

void Rogue::Special(ROB** res)
{
	if (modInMoves > 0) modInMoves--;
	if (buffSp > 0)
	{
		buffSp--;
		hp += spValue;
		if (hp > maxHP) hp = maxHP;
		(*res)->enHP -= spValue;
	}
	buffSp++;
	(*res)->enMiss = false;
	modAt = 1;
}