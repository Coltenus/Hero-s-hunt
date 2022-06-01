#include "chooseRoom.h"
#include <iostream>
#include <raylib.hpp>
#include "rooms.h"

bool NextRoom(Hero** h, Save** sv, double* st, bool* shouldExit, Info* inf)
{
	static short chooseEn, chooseR;
	static Rewards* r;
	(*sv)->roomNum++;
	r = new Rewards;
	r->isActive = false;
	Enemy* en;
	chooseEn = rand() % 100 + 1;
	if (chooseEn >= 1 && chooseEn <= 100 && (*sv)->roomNum != 10) en = new Zombie((*sv)->roomNum);
	chooseR = rand() % 100 + 1;
	while (!IsKeyPressed(KEY_SPACE) && !(*shouldExit))
	{
		if (GetTime() - *st >= 60)
		{
			*st = GetTime();
			(*sv)->minutes++;
			if ((*sv)->minutes == 60) (*sv)->hours++;
			if ((*sv)->hours == 24) (*sv)->days++;
		}
		if (WindowShouldClose()) *shouldExit = true;
		BeginDrawing();
		DrawText(TextFormat("Room %hu", (*sv)->roomNum), WIDTH / 2 - 25, HEIGHT / 2 - 150, 30, BLACK);
		if((*sv)->roomNum == 10) DrawText("Boss", WIDTH / 2 - 15, HEIGHT / 2 - 50, 30, BLACK);
		else if (chooseR >= 1 && chooseR <= 60)
		{
			DrawText("Battle against", WIDTH / 2 - 75, HEIGHT / 2 - 50, 30, BLACK);
			if(chooseEn >= 1 && chooseEn <= 100) DrawText("Zombie", WIDTH / 2 - 20, HEIGHT / 2, 30, BLACK);
		}
		else if(chooseR >= 61 && chooseR <= 80) DrawText("Shop", WIDTH / 2 - 20, HEIGHT / 2 - 50, 30, BLACK);
		else DrawText("Rest room", WIDTH / 2 - 50, HEIGHT / 2 - 50, 30, BLACK);
		ClearBackground(WHITE);
		EndDrawing();
	}
	if((*sv)->roomNum == 10 && !(*shouldExit))
	{
	    en = new Zombie((*sv)->roomNum*3);
	    *shouldExit = Battle(h, &en, &r, sv, inf, st, true);
	    return false;
	}
	if (chooseR >= 1 && chooseR <= 60 && !(*shouldExit)) *shouldExit = Battle(h, &en, &r, sv, inf, st, false);
	else if(chooseR >= 61 && chooseR <= 80 && !(*shouldExit)) *shouldExit = Shop(h, sv, st);
	else if(chooseR >= 81 && chooseR <= 100 && !(*shouldExit)) *shouldExit = RestRoom(h, sv, st);
	while (r->isActive && !(*shouldExit))
	{
		if (GetTime() - *st >= 60)
		{
			*st = GetTime();
			(*sv)->minutes++;
			if ((*sv)->minutes == 60) (*sv)->hours++;
			if ((*sv)->hours == 24) (*sv)->days++;
		}
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
	if (*shouldExit) return false;
	if ((*h)->hp <= 0) return false;
	delete r;
	r = nullptr;
	return true;
}