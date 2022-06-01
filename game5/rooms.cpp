#include "rooms.h"
#include <iostream>
#include <raylib.hpp>
#include "info.h"

bool Battle(Hero** h, Enemy** en, Rewards** r, Save** sv, Info* inf, double* st, bool isBoss)
{
	static unsigned short action, sel;
	static bool confirmation;
	static Vector2 mPos;
	static bool shouldExit;
	shouldExit = false;
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
			if (IsKeyPressed(KEY_I)) shouldExit = OpenInfo(inf, sv, st);
			if (IsKeyPressed(KEY_DOWN) && sel < 3)
				sel++;
			if (IsKeyPressed(KEY_UP) && sel > 1)
				sel--;
			if (mPos.x >= 40 && mPos.x <= 220
				&& mPos.y >= HEIGHT / 2 + 20 && mPos.y <= HEIGHT / 2 + 80) sel = 1;
			if (mPos.x >= 40 && mPos.x <= 220
				&& mPos.y >= HEIGHT / 2 + 120 && mPos.y <= HEIGHT / 2 + 180) sel = 2;
			if (mPos.x >= 40 && mPos.x <= 220
				&& mPos.y >= HEIGHT / 2 + 220 && mPos.y <= HEIGHT / 2 + 280) sel = 3;
			switch (sel)
			{
			case 1:
				DrawRectangle(40, HEIGHT / 2 + 20, 180, 60, YELLOW);
				break;
			case 2:
				DrawRectangle(40, HEIGHT / 2 + 120, 180, 60, YELLOW);
				break;
			case 3:
				DrawRectangle(40, HEIGHT / 2 + 220, 180, 60, YELLOW);
				break;
			}
			DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, BLACK);

			DrawRectangleLines(40, HEIGHT / 2 + 20, 180, 60, BLACK);
			DrawText((*h)->nA, 45, HEIGHT / 2 + 38, 24, BLACK);

			DrawRectangleLines(40, HEIGHT / 2 + 120, 180, 60, BLACK);
			DrawText((*h)->hA, 45, HEIGHT / 2 + 138, 24, BLACK);

			DrawRectangleLines(40, HEIGHT / 2 + 220, 180, 60, BLACK);
			DrawText((*h)->sp, 45, HEIGHT / 2 + 238, 24, BLACK);

			DrawText(inf->username, 250, HEIGHT / 2 + 20, 24, BLACK);
			switch ((*sv)->charact)
			{
			case 1:
				DrawText("Warrior", 250, HEIGHT / 2 + 60, 24, BLACK);
				break;
			case 2:
				DrawText("Archer", 250, HEIGHT / 2 + 60, 24, BLACK);
				break;
			case 3:
				DrawText("Palladin", 250, HEIGHT / 2 + 60, 24, BLACK);
				break;
			}
			DrawText(TextFormat("HP: %d/%d", (*h)->hp, (*h)->maxHP), 250, HEIGHT / 2 + 100, 24, BLACK);
			DrawText(TextFormat("Block: %d", (*h)->block), 250, HEIGHT / 2 + 140, 24, BLACK);
			DrawText(TextFormat("Normal attack damage: %d", (*h)->minNDMG), 250, HEIGHT / 2 + 180, 24, BLACK);
			DrawText(TextFormat("Heavy attack damage: %d", (*h)->minHDMG), 250, HEIGHT / 2 + 220, 24, BLACK);
			DrawText(TextFormat("Special value: %d", (*h)->spValue), 250, HEIGHT / 2 + 260, 24, BLACK);
			DrawText(TextFormat("Evasion: %d%", (*h)->evasion), 250, HEIGHT / 2 + 300, 24, BLACK);
			DrawText(TextFormat("Buff duration: %d", (*h)->buffsN), 250, HEIGHT / 2 + 340, 24, BLACK);
			DrawText(TextFormat("Gold: %d", (*h)->gold), 250, HEIGHT / 2 + 380, 24, BLACK);

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
			if (WindowShouldClose()) shouldExit = true;
			if (shouldExit) break;
		}
		if (shouldExit) break;
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
			if ((*h)->evasion < 60) (*r)->evasion = rand() % 2;
			else (*r)->evasion = 0;
			if ((*sv)->charact == 1)(*r)->spValue = rand() % 4;
			else if ((*sv)->charact == 2) (*r)->spValue = 0;
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
			if (IsKeyPressed(KEY_I)) shouldExit = OpenInfo(inf, sv, st);
			BeginDrawing();
			DrawText("Press Space to continue", WIDTH / 2 - 150, HEIGHT / 2 - 200, 30, BLACK);
			ClearBackground(WHITE);
			EndDrawing();
		}
	}
	if (shouldExit) return true;
	else return false;
}

bool Shop(Hero** h, Save** sv, double* st, Info* inf)
{
	static bool shouldExit;
	static short sel;
	static Vector2 mPos;
	static int i;
	short* value = new short[5];
	short* price = new short[5];
	bool* isActive = new bool[5];
	i = 0;
	for (i = 0; i < 5; i++) isActive[i] = true;
	value[0] = rand() % 15 + 5;
	price[0] = value[0];
	value[1] = rand() % 8 + 4;
	price[1] = value[1] * 3;
	value[2] = rand() % 8 + 4;
	price[2] = value[2] * 3;
	value[3] = rand() % 4 + 1;
	price[3] = value[3] * 10;
	if ((*sv)->charact == 1)
	{
		value[4] = rand() % 5 + 5;
		price[4] = value[4] * 5;
	}
	else if ((*sv)->charact == 2)
	{
		value[4] = 1;
		price[4] = value[4] * 40;
	}
	if ((*h)->evasion >= 60) isActive[3] = false;
	sel = 0;
	shouldExit = false;
	while (!IsKeyPressed(KEY_B) && !shouldExit)
	{
		mPos = GetMousePosition();
		if (GetTime() - *st >= 60)
		{
			*st = GetTime();
			(*sv)->minutes++;
			if ((*sv)->minutes == 60) (*sv)->hours++;
			if ((*sv)->hours == 24) (*sv)->days++;
		}
		if (IsKeyPressed(KEY_I)) shouldExit = OpenInfo(inf, sv, st);
		if (IsKeyPressed(KEY_RIGHT) && sel < 5)
			sel++;
		if (IsKeyPressed(KEY_LEFT) && sel > 1)
			sel--;
		if (mPos.x >= 110 && mPos.x <= 260
			&& mPos.y >= HEIGHT / 4 * 3 + 40 && mPos.y <= HEIGHT / 4 * 3 + 80) sel = 1;
		if (mPos.x >= 410 && mPos.x <= 560
			&& mPos.y >= HEIGHT / 4 * 3 + 40 && mPos.y <= HEIGHT / 4 * 3 + 80) sel = 2;
		if (mPos.x >= 760 && mPos.x <= 910
			&& mPos.y >= HEIGHT / 4 * 3 + 40 && mPos.y <= HEIGHT / 4 * 3 + 80) sel = 3;
		if (mPos.x >= 1065 && mPos.x <= 1215
			&& mPos.y >= HEIGHT / 4 * 3 + 40 && mPos.y <= HEIGHT / 4 * 3 + 80) sel = 4;
		if (mPos.x >= 1335 && mPos.x <= 1485
			&& mPos.y >= HEIGHT / 4 * 3 + 40 && mPos.y <= HEIGHT / 4 * 3 + 80) sel = 5;
		BeginDrawing();
		DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, BLACK);

		switch (sel)
		{
		case 1:
			if(isActive[sel - 1]) DrawRectangle(110, HEIGHT / 4 * 3 + 40, 150, 40, YELLOW);
			break;
		case 2:
			if (isActive[sel - 1]) DrawRectangle(410, HEIGHT / 4 * 3 + 40, 150, 40, YELLOW);
			break;
		case 3:
			if (isActive[sel - 1]) DrawRectangle(760, HEIGHT / 4 * 3 + 40, 150, 40, YELLOW);
			break;
		case 4:
			if (isActive[sel - 1]) DrawRectangle(1065, HEIGHT / 4 * 3 + 40, 150, 40, YELLOW);
			break;
		case 5:
			if (isActive[sel - 1]) DrawRectangle(1335, HEIGHT / 4 * 3 + 40, 150, 40, YELLOW);
			break;
		}
		if (!isActive[0]) DrawRectangle(110, HEIGHT / 4 * 3 + 40, 150, 40, GRAY);
		if (!isActive[1]) DrawRectangle(410, HEIGHT / 4 * 3 + 40, 150, 40, GRAY);
		if (!isActive[2]) DrawRectangle(760, HEIGHT / 4 * 3 + 40, 150, 40, GRAY);
		if (!isActive[3]) DrawRectangle(1065, HEIGHT / 4 * 3 + 40, 150, 40, GRAY);
		if (!isActive[4]) DrawRectangle(1335, HEIGHT / 4 * 3 + 40, 150, 40, GRAY);

		DrawText("Shop", WIDTH / 2 - 20, HEIGHT / 2 + 20, 30, BLACK);

		DrawText(TextFormat("+%d maximum HP", value[0]), 100, HEIGHT / 4 * 3 - 12, 24, BLACK);
		DrawRectangleLines(110, HEIGHT / 4 * 3 + 40, 150, 40, BLACK);
		DrawText(TextFormat("%d G", price[0]), 170, HEIGHT / 4 * 3 + 48, 24, BLACK);

		DrawText(TextFormat("+%d minimum normal DMG", value[1]), 350, HEIGHT / 4 * 3 - 12, 24, BLACK);
		DrawRectangleLines(410, HEIGHT / 4 * 3 + 40, 150, 40, BLACK);
		DrawText(TextFormat("%d G", price[1]), 465, HEIGHT / 4 * 3 + 48, 24, BLACK);

		DrawText(TextFormat("+%d minimum heavy DMG", value[2]), 700, HEIGHT / 4 * 3 - 12, 24, BLACK);
		DrawRectangleLines(760, HEIGHT / 4 * 3 + 40, 150, 40, BLACK);
		DrawText(TextFormat("%d G", price[2]), 815, HEIGHT / 4 * 3 + 48, 24, BLACK);

		DrawText(TextFormat("+%d evasion", value[3]), 1075, HEIGHT / 4 * 3 - 12, 24, BLACK);
		DrawRectangleLines(1065, HEIGHT / 4 * 3 + 40, 150, 40, BLACK);
		DrawText(TextFormat("%d G", price[3]), 1120, HEIGHT / 4 * 3 + 48, 24, BLACK);

		DrawText(TextFormat("+%d special value", value[4]), 1300, HEIGHT / 4 * 3 - 12, 24, BLACK);
		DrawRectangleLines(1335, HEIGHT / 4 * 3 + 40, 150, 40, BLACK);
		DrawText(TextFormat("%d G", price[4]), 1390, HEIGHT / 4 * 3 + 48, 24, BLACK);

		DrawText(TextFormat("%d G", (*h)->gold), 70, HEIGHT / 2 + 20, 24, BLACK);

		ClearBackground(WHITE);
		EndDrawing();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER))
		{
			switch (sel)
			{
			case 1:
				if (isActive[sel - 1] && (*h)->gold >= price[sel - 1])
				{
					(*h)->gold -= price[sel - 1];
					(*h)->hp += value[sel - 1];
					(*h)->maxHP += value[sel - 1];
					isActive[sel - 1] = false;
				}
				break;
			case 2:
				if (isActive[sel - 1] && (*h)->gold >= price[sel - 1])
				{
					(*h)->gold -= price[sel - 1];
					(*h)->minNDMG += value[sel - 1];
					isActive[sel - 1] = false;
				}
				break;
			case 3:
				if (isActive[sel - 1] && (*h)->gold >= price[sel - 1])
				{
					(*h)->gold -= price[sel - 1];
					(*h)->minHDMG += value[sel - 1];
					isActive[sel - 1] = false;
				}
				break;
			case 4:
				if (isActive[sel - 1] && (*h)->gold >= price[sel - 1])
				{
					(*h)->gold -= price[sel - 1];
					(*h)->evasion += value[sel - 1];
					isActive[sel - 1] = false;
				}
				break;
			case 5:
				if (isActive[sel - 1] && (*h)->gold >= price[sel - 1])
				{
					(*h)->gold -= price[sel - 1];
					(*h)->spValue += value[sel - 1];
					isActive[sel - 1] = false;
				}
				break;
			}
		}
		if (WindowShouldClose())
		{
			shouldExit = true;
		}
	}
	delete[] value;
	delete[] price;
	delete[] isActive;
	value = nullptr;
	price = nullptr;
	isActive = nullptr;
	if (shouldExit) return true;
	else return false;
}

bool RestRoom(Hero** h, Save** sv, double* st, Info* inf)
{
	static short sel;
	static bool confirmation;
	static bool shouldExit;
	static Vector2 mPos;
	shouldExit = false;
	confirmation = false;
	sel = 0;
	while (!IsKeyPressed(KEY_B) && !shouldExit)
	{
		if (GetTime() - *st >= 60)
		{
			*st = GetTime();
			(*sv)->minutes++;
			if ((*sv)->minutes == 60) (*sv)->hours++;
			if ((*sv)->hours == 24) (*sv)->days++;
		}
		mPos = GetMousePosition();
		if (IsKeyPressed(KEY_I)) shouldExit = OpenInfo(inf, sv, st);
		if (shouldExit) break;
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
		if (WindowShouldClose()) shouldExit = true;
	}
	if (shouldExit) return true;
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
			if((*h)->evasion < 60) (*h)->evasion += 1;
			break;
		case 5:
			if((*sv)->charact != 2)(*h)->spValue += rand() % 4 + 1;
			break;
		}
	}
	return false;
}