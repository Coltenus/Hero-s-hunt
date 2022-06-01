#include "rooms.h"
#include <iostream>
#include <raylib.hpp>

bool Battle(Hero** h, Enemy** en, Rewards** r, Save** sv, Info* inf, double* st, bool isBoss)
{
	static unsigned short action, sel;
	static bool confirmation;
	static Vector2 mPos;
	sel = 0;
	action = 0;
	while ((*h)->hp > 0)
	{
		sel = 0;
		confirmation = false;
		while (!confirmation)
		{
			if (GetTime() - *st >= 60)
			{
				*st = GetTime();
				(*sv)->minutes++;
				if ((*sv)->minutes == 60) (*sv)->hours++;
				if ((*sv)->hours == 24) (*sv)->days++;
			}
			mPos = GetMousePosition();
			if (IsKeyPressed(KEY_ENTER))
			{
				confirmation = true;
			}
			BeginDrawing();
			if (IsKeyPressed(KEY_DOWN) && sel < 3)
				sel++;
			if (IsKeyPressed(KEY_UP) && sel > 1)
				sel--;
			if (mPos.x >= 40 && mPos.x <= 210
				&& mPos.y >= HEIGHT / 2 + 20 && mPos.y <= HEIGHT / 2 + 80) sel = 1;
			if (mPos.x >= 40 && mPos.x <= 210
				&& mPos.y >= HEIGHT / 2 + 120 && mPos.y <= HEIGHT / 2 + 180) sel = 2;
			if (mPos.x >= 40 && mPos.x <= 210
				&& mPos.y >= HEIGHT / 2 + 220 && mPos.y <= HEIGHT / 2 + 280) sel = 3;
			switch (sel)
			{
			case 1:
				DrawRectangle(40, HEIGHT / 2 + 20, 170, 60, YELLOW);
				break;
			case 2:
				DrawRectangle(40, HEIGHT / 2 + 120, 170, 60, YELLOW);
				break;
			case 3:
				DrawRectangle(40, HEIGHT / 2 + 220, 170, 60, YELLOW);
				break;
			}
			DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, BLACK);

			DrawRectangleLines(40, HEIGHT / 2 + 20, 170, 60, BLACK);
			DrawText((*h)->nA, 45, HEIGHT / 2 + 38, 24, BLACK);

			DrawRectangleLines(40, HEIGHT / 2 + 120, 170, 60, BLACK);
			DrawText((*h)->hA, 45, HEIGHT / 2 + 138, 24, BLACK);

			DrawRectangleLines(40, HEIGHT / 2 + 220, 170, 60, BLACK);
			DrawText((*h)->sp, 45, HEIGHT / 2 + 238, 24, BLACK);

			DrawText(inf->username, 250, HEIGHT / 2 + 20, 24, BLACK);
			DrawText(TextFormat("HP: %d/%d", (*h)->hp, (*h)->maxHP), 250, HEIGHT / 2 + 60, 24, BLACK);
			DrawText(TextFormat("Block: %d", (*h)->block), 250, HEIGHT / 2 + 100, 24, BLACK);
			DrawText(TextFormat("Normal attack damage: %d", (*h)->minNDMG), 250, HEIGHT / 2 + 140, 24, BLACK);
			DrawText(TextFormat("Heavy attack damage: %d", (*h)->minHDMG), 250, HEIGHT / 2 + 180, 24, BLACK);
			DrawText(TextFormat("Special value: %d", (*h)->spValue), 250, HEIGHT / 2 + 220, 24, BLACK);
			DrawText(TextFormat("Evasion: %d%", (*h)->evasion), 250, HEIGHT / 2 + 260, 24, BLACK);
			DrawText(TextFormat("Gold: %d", (*h)->gold), 250, HEIGHT / 2 + 300, 24, BLACK);

			if(isBoss) DrawText("Boss", 1000, HEIGHT / 2 + 20, 24, BLACK);
			else DrawText("Enemy", 1000, HEIGHT / 2 + 20, 24, BLACK);
			DrawText(TextFormat("HP: %d/%d", (*en)->hp, (*en)->maxHP), 1000, HEIGHT / 2 + 60, 24, BLACK);
			DrawText(TextFormat("Normal attack damage: %d", (*en)->minNDMG), 1000, HEIGHT / 2 + 100, 24, BLACK);
			DrawText(TextFormat("Heavy attack damage: %d", (*en)->minHDMG), 1000, HEIGHT / 2 + 140, 24, BLACK);
			DrawText(TextFormat("Special value: %d", (*en)->spValue), 1000, HEIGHT / 2 + 180, 24, BLACK);
			DrawText(TextFormat("Gold reward: %d%", (*en)->rewGold), 1000, HEIGHT / 2 + 220, 24, BLACK);

			DrawText(TextFormat("Room %d%", (*sv)->roomNum), 20, 20, 30, BLACK);

			DrawRectangle(WIDTH / 2 - 50, HEIGHT / 4 - 50, 100, 100, DARKGREEN);

			ClearBackground(WHITE);
			EndDrawing();
			if (WindowShouldClose()) return true;
		}
		switch (sel)
		{
		case 1:
			(*h)->Attack(en);
			break;
		case 2:
			(*h)->HeavyAttack(en);
			break;
		case 3:
			(*h)->Special();
			break;
		}
		if ((*en)->hp <= 0)
		{
			(*r)->gold = (*en)->rewGold + rand() % 4;
			(*r)->hp = rand() % 4;
			(*r)->minNDMG = rand() % 3;
			(*r)->minHDMG = rand() % 3;
			(*r)->evasion = rand() % 2;
			(*r)->spValue = rand() % 4;
			(*h)->gold = (*r)->gold;
			(*h)->hp += (*r)->hp;
			(*h)->maxHP += (*r)->hp;
			(*h)->minNDMG += (*r)->minNDMG;
			(*h)->minHDMG += (*r)->minHDMG;
			(*h)->evasion += (*r)->evasion;
			(*h)->spValue += (*r)->spValue;
			(*r)->isActive = true;
			break;
		}
		sel = rand() % 100 + 1;
		if (sel >= 1 && sel <= 40) (*en)->Attack(h);
		else if (sel >= 41 && sel >= 80) (*en)->HeavyAttack(h);
		else (*en)->Special();
		while(!IsKeyPressed(KEY_SPACE))
		{
			BeginDrawing();
			DrawText("Press Space to continue", WIDTH / 2 - 185, HEIGHT / 2 - 200, 30, BLACK);
			ClearBackground(WHITE);
			EndDrawing();
		}
	}
	return false;
}

bool Shop(Hero** h, Save** sv, double* st)
{
	while (!IsKeyPressed(KEY_B))
	{
		if (GetTime() - *st >= 60)
		{
			*st = GetTime();
			(*sv)->minutes++;
			if ((*sv)->minutes == 60) (*sv)->hours++;
			if ((*sv)->hours == 24) (*sv)->days++;
		}
		BeginDrawing();
		DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, BLACK);

		DrawText("Shop", WIDTH / 2 - 10, HEIGHT / 2 + 20, 30, BLACK);
		ClearBackground(WHITE);
		EndDrawing();
		if (WindowShouldClose())
		{
			return true;
		}
	}
	return false;
}

bool RestRoom(Hero** h, Save** sv, double* st)
{
	static short sel;
	static bool confirmation;
	static Vector2 mPos;
	confirmation = false;
	sel = 0;
	while (!IsKeyPressed(KEY_B))
	{
		if (GetTime() - *st >= 60)
		{
			*st = GetTime();
			(*sv)->minutes++;
			if ((*sv)->minutes == 60) (*sv)->hours++;
			if ((*sv)->hours == 24) (*sv)->days++;
		}
		mPos = GetMousePosition();
		if (IsKeyPressed(KEY_ENTER)
			|| IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
			&& (mPos.x >= WIDTH / 2 - 100 && mPos.x <= WIDTH / 2 + 100
				&& mPos.y >= HEIGHT / 2 + 120 && mPos.y <= HEIGHT / 2 + 180
				|| mPos.x >= WIDTH / 2 - 100 && mPos.x <= WIDTH / 2 + 100
				&& mPos.y >= HEIGHT / 2 + 220 && mPos.y <= HEIGHT / 2 + 280))
		{
			break;
		}
		if (IsKeyPressed(KEY_DOWN) && sel < 2)
			sel++;
		if (IsKeyPressed(KEY_UP) && sel > 1)
			sel--;
		if (mPos.x >= WIDTH / 2 - 100 && mPos.x <= WIDTH / 2 + 100
			&& mPos.y >= HEIGHT / 2 + 120 && mPos.y <= HEIGHT / 2 + 180) sel = 1;
		if (mPos.x >= WIDTH / 2 - 100 && mPos.x <= WIDTH / 2 + 100
			&& mPos.y >= HEIGHT / 2 + 220 && mPos.y <= HEIGHT / 2 + 280) sel = 2;
		BeginDrawing();
		DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, BLACK);

		DrawText("Rest Room", WIDTH / 2 - 80, HEIGHT / 2 + 20, 30, BLACK);

		switch (sel)
		{
		case 1:
			DrawRectangle(WIDTH / 2 - 100, HEIGHT / 2 + 120, 200, 60, YELLOW);
			break;
		case 2:
			DrawRectangle(WIDTH / 2 - 100, HEIGHT / 2 + 220, 200, 60, YELLOW);
			break;
		}

		DrawRectangleLines(WIDTH / 2 - 100, HEIGHT / 2 + 120, 200, 60, BLACK);
		DrawText("Rest", WIDTH / 2 - 25, HEIGHT / 2 + 138, 24, BLACK);

		DrawRectangleLines(WIDTH / 2 - 100, HEIGHT / 2 + 220, 200, 60, BLACK);
		DrawText("Random upgrade", WIDTH / 2 - 95, HEIGHT / 2 + 238, 24, BLACK);

		ClearBackground(WHITE);
		EndDrawing();
		if (WindowShouldClose()) return true;
	}
	switch (sel)
	{
	case 1:
		(*h)->hp += (short)((*h)->maxHP * 0.35);
		if ((*h)->hp > (*h)->maxHP) (*h)->hp = (*h)->maxHP;
		break;
	case 2:
		sel = rand() % 5 + 1;
		switch (sel)
		{
		case 1:
			(*h)->maxHP += rand() % 3 + 1;
			break;
		case 2:
			(*h)->minNDMG += rand() % 3 + 1;
			break;
		case 3:
			(*h)->minHDMG += rand() % 3 + 1;
			break;
		case 4:
			(*h)->evasion += 1;
			break;
		case 5:
			(*h)->spValue += rand() % 4 + 1;
			break;
		}
	}
	return false;
}