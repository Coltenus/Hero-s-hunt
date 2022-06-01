#include "chooseRoom.h"
#include <iostream>
#include <raylib.hpp>
#include "rooms.h"
#include "info.h"

bool NextRoom(Hero** h, Save** sv, double* st, bool* shouldExit, Info* inf)
{
	static Rewards* r;
	static bool isNewRoom;
	isNewRoom = true;
	(*sv)->roomNum++;
	r = new Rewards;
	r->isActive = false;
	Enemy* en;
	en = NULL;
	if((*sv)->enemyStats.enType == 0) (*sv)->enemyStats.enType = rand() % 100 + 1;
	else
	{
		isNewRoom = false;
		en = new Zombie(1);
		en->hp = (*sv)->enemyStats.hp;
		en->maxHP = (*sv)->enemyStats.maxHP;
		en->minNDMG = (*sv)->enemyStats.dmgN;
		en->minHDMG = (*sv)->enemyStats.dmgH;
		en->modAt = (*sv)->enemyStats.modAt;
		en->rewGold = (*sv)->enemyStats.rewGold;
		en->spValue = (*sv)->enemyStats.spV;
	}
	if (isNewRoom && (*sv)->enemyStats.enType >= 1 && (*sv)->enemyStats.enType <= 100 && (*sv)->roomNum != 10) en = new Zombie((*sv)->roomNum);
	if (isNewRoom && (*sv)->roomType == 0) (*sv)->roomType = rand() % 100 + 1;
	while (!IsKeyPressed(KEY_SPACE) && !(*shouldExit))
	{
		if (GetTime() - *st >= 60)
		{
			*st = GetTime();
			(*sv)->minutes++;
			if ((*sv)->minutes == 60) (*sv)->hours++;
			if ((*sv)->hours == 24) (*sv)->days++;
		}
		if (IsKeyPressed(KEY_I)) *shouldExit = OpenInfo(inf, sv, st);
		if (WindowShouldClose()) *shouldExit = true;
		BeginDrawing();
		DrawText(TextFormat("Room %hu", (*sv)->roomNum), WIDTH / 2 - 25, HEIGHT / 2 - 150, 30, BLACK);
		if((*sv)->roomNum == 10) DrawText("Boss", WIDTH / 2 - 15, HEIGHT / 2 - 50, 30, BLACK);
		else if ((*sv)->roomType >= 1 && (*sv)->roomType <= 60)
		{
			DrawText("Battle against", WIDTH / 2 - 75, HEIGHT / 2 - 50, 30, BLACK);
			if((*sv)->enemyStats.enType >= 1 && (*sv)->enemyStats.enType <= 100) DrawText("Zombie", WIDTH / 2 - 20, HEIGHT / 2, 30, BLACK);
		}
		else if((*sv)->roomType >= 61 && (*sv)->roomType <= 80) DrawText("Shop", WIDTH / 2 - 20, HEIGHT / 2 - 50, 30, BLACK);
		else DrawText("Rest room", WIDTH / 2 - 50, HEIGHT / 2 - 50, 30, BLACK);
		ClearBackground(WHITE);
		EndDrawing();
	}
	if((*sv)->roomNum == 10 && !(*shouldExit))
	{
	    if(isNewRoom) en = new Zombie((*sv)->roomNum*3);
	    *shouldExit = Battle(h, &en, &r, sv, inf, st, true);
		if ((*h)->hp <= 0 || (*h)->hp > 0 && en->hp <= 0) return false;
		else *shouldExit = true;
	}
	if (*shouldExit) return false;
	if ((*sv)->roomType >= 1 && (*sv)->roomType <= 60 && !(*shouldExit)) *shouldExit = Battle(h, &en, &r, sv, inf, st, false);
	else if((*sv)->roomType >= 61 && (*sv)->roomType <= 80 && !(*shouldExit)) *shouldExit = Shop(h, sv, st, inf);
	else if((*sv)->roomType >= 81 && (*sv)->roomType <= 100 && !(*shouldExit)) *shouldExit = RestRoom(h, sv, st, inf);
	while (r->isActive && !(*shouldExit))
	{
		if (GetTime() - *st >= 60)
		{
			*st = GetTime();
			(*sv)->minutes++;
			if ((*sv)->minutes == 60) (*sv)->hours++;
			if ((*sv)->hours == 24) (*sv)->days++;
		}
		if (IsKeyPressed(KEY_I)) *shouldExit = OpenInfo(inf, sv, st);
		if (IsKeyPressed(KEY_ENTER)) r->isActive = false;
		if (WindowShouldClose()) *shouldExit = true;
		BeginDrawing();
		DrawText(TextFormat("Room %hu", (*sv)->roomNum), WIDTH / 2 - 25, HEIGHT / 2 - 150, 30, BLACK);
		DrawText(TextFormat("+%hu gold", r->gold), WIDTH / 2 - 25, HEIGHT / 2, 30, BLACK);
		DrawText(TextFormat("+%hu hp", r->hp), 100, HEIGHT / 2 + 100, 24, BLACK);
		DrawText(TextFormat("+%hu min normal DMG", r->minNDMG), 400, HEIGHT / 2 + 100, 24, BLACK);
		DrawText(TextFormat("+%hu min heavy DMG", r->minNDMG), 700, HEIGHT / 2 + 100, 24, BLACK);
		DrawText(TextFormat("+%hu special value", r->spValue), 1000, HEIGHT / 2 + 100, 24, BLACK);
		DrawText(TextFormat("+%hu evasion", r->evasion), 1300, HEIGHT / 2 + 100, 24, BLACK);
		ClearBackground(WHITE);
		EndDrawing();
	}
	if (*shouldExit)
	{
		if (en != NULL)
		{
			(*sv)->enemyStats.hp = en->hp;
			(*sv)->enemyStats.maxHP = en->maxHP;
			(*sv)->enemyStats.dmgN = en->minNDMG;
			(*sv)->enemyStats.dmgH = en->minHDMG;
			(*sv)->enemyStats.modAt = en->modAt;
			(*sv)->enemyStats.rewGold = en->rewGold;
			(*sv)->enemyStats.spV = en->spValue;
		}
		return false;
	}
	else
	{
		(*sv)->roomType = 0;
		if(en != NULL) (*sv)->enemyStats.enType = 0;
	}
	if ((*h)->hp <= 0) return false;
	delete r;
	r = nullptr;
	return true;
}