#include "rooms.h"
#include <iostream>
#include <raylib.hpp>
#include "info.h"
#include "common.h"

bool Battle(Hero** h, Enemy** en, Rewards** r, Save** sv, Info* inf, double* st, bool isBoss, Audio* a2)
{
	static unsigned short action, sel;
	static bool confirmation;
	static Vector2 mPos;
	static bool shouldExit;
	static Texture2D enemyTexture, bg;
	static Rectangle frameRec;
	static int frameSpeed, frameCounter, currentFrame;
	static ROB* res;
	res = new ROB;
	frameCounter = 0;
	frameSpeed = 3;
	currentFrame = 0;
	if ((*en)->enemType == 1)
	{
		enemyTexture = LoadTexture("src/Zombie.png");
		frameRec = { 0, 0, (float)enemyTexture.width / 4, (float)enemyTexture.height };
	}
	bg = LoadTexture("src/bg.png");
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
			frameCounter++;
			if (frameCounter >= 60 / frameSpeed)
			{
				frameCounter = 0;
				currentFrame++;
				if (currentFrame > 2) currentFrame = 0;
				frameRec.x = (float)currentFrame * (float)enemyTexture.width / 4;
			}
			mPos = GetMousePosition();
			if (IsKeyPressed(KEY_ENTER) && sel >= 1 && sel <= 4
				|| IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
				&& (mPos.x >= 40 && mPos.x <= 280
					&& mPos.y >= HEIGHT / 2 + 20 && mPos.y <= HEIGHT / 2 + 80
					|| mPos.x >= 40 && mPos.x <= 280
					&& mPos.y >= HEIGHT / 2 + 120 && mPos.y <= HEIGHT / 2 + 180
					|| mPos.x >= 40 && mPos.x <= 280
					&& mPos.y >= HEIGHT / 2 + 220 && mPos.y <= HEIGHT / 2 + 280
					&& !((*sv)->charact == 3 && (*h)->buffsN != 0)
				    || mPos.x >= 40 && mPos.x <= 280
					&& mPos.y >= HEIGHT / 2 + 320 && mPos.y <= HEIGHT / 2 + 380
						&& (*h)->ability->curDelay == 0))
			{
				confirmation = true;
			}
			if (IsKeyPressed(KEY_I)) shouldExit = OpenInfo(inf, sv, st, a2);
			if (IsKeyPressed(KEY_DOWN) && sel < 4)
			{
				sel++;
				if ((*h)->ability->curDelay > 0 && sel == 4) sel--;
				if ((*sv)->charact == 3 && (*h)->buffsN != 0 && sel == 3 && (*h)->ability->curDelay == 0) sel++;
				else if ((*sv)->charact == 3 && (*h)->buffsN != 0 && sel == 3) sel--;
			}
			if (IsKeyPressed(KEY_UP) && sel > 1)
			{
				sel--;
				if ((*sv)->charact == 3 && (*h)->buffsN != 0 && sel == 3) sel--;
			}
			if (mPos.x >= 40 && mPos.x <= 280
				&& mPos.y >= HEIGHT / 2 + 20 && mPos.y <= HEIGHT / 2 + 80) sel = 1;
			if (mPos.x >= 40 && mPos.x <= 280
				&& mPos.y >= HEIGHT / 2 + 120 && mPos.y <= HEIGHT / 2 + 180) sel = 2;
			if (mPos.x >= 40 && mPos.x <= 280
				&& mPos.y >= HEIGHT / 2 + 220 && mPos.y <= HEIGHT / 2 + 280
				&& !((*sv)->charact == 3 && (*h)->buffsN != 0)) sel = 3;
			if (mPos.x >= 40 && mPos.x <= 280
				&& mPos.y >= HEIGHT / 2 + 320 && mPos.y <= HEIGHT / 2 + 380
				&& (*h)->ability->curDelay == 0) sel = 4;
			BeginDrawing();
			DrawTexture(bg, 0, 0, WHITE);
			switch (sel)
			{
			case 1:
				DrawRectangle(40, HEIGHT / 2 + 20, 240, 60, YELLOW);
				break;
			case 2:
				DrawRectangle(40, HEIGHT / 2 + 120, 240, 60, YELLOW);
				break;
			case 3:
				if(!((*sv)->charact == 3 && (*h)->buffsN != 0)) DrawRectangle(40, HEIGHT / 2 + 220, 240, 60, YELLOW);
				break;
			case 4:
				if((*h)->ability->curDelay == 0) DrawRectangle(40, HEIGHT / 2 + 320, 240, 60, YELLOW);
				break;
			}
			DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, WHITE);

			if ((*sv)->charact == 3 && (*h)->buffsN != 0) DrawRectangle(40, HEIGHT / 2 + 220, 240, 60, DARKGRAY);
			if ((*h)->ability->curDelay != 0) DrawRectangle(40, HEIGHT / 2 + 320, 240, 60, DARKGRAY);

			DrawRectangleLines(40, HEIGHT / 2 + 20, 240, 60, WHITE);
			DrawText(*((*h)->nA), 45, HEIGHT / 2 + 38, 24, WHITE);

			DrawRectangleLines(40, HEIGHT / 2 + 120, 240, 60, WHITE);
			DrawText(*((*h)->hA), 45, HEIGHT / 2 + 138, 24, WHITE);

			DrawRectangleLines(40, HEIGHT / 2 + 220, 240, 60, WHITE);
			DrawText(*((*h)->sp), 45, HEIGHT / 2 + 238, 24, WHITE);

			DrawRectangleLines(40, HEIGHT / 2 + 320, 240, 60, WHITE);
			DrawText(*((*h)->ability->abTitle), 45, HEIGHT / 2 + 338, 24, WHITE);

			DrawText(inf->username, 300, HEIGHT / 2 + 20, 24, WHITE);
			switch ((*sv)->charact)
			{
			case 1:
				DrawText("Swordsman", 300, HEIGHT / 2 + 60, 24, WHITE);
				break;
			case 2:
				DrawText("Archer", 300, HEIGHT / 2 + 60, 24, WHITE);
				break;
			case 3:
				DrawText("Palladin", 300, HEIGHT / 2 + 60, 24, WHITE);
				break;
			}
			DrawText(TextFormat("HP: %d/%d", (*h)->hp, (*h)->maxHP), 300, HEIGHT / 2 + 100, 24, WHITE);
			DrawText(TextFormat("Block: %d", (*h)->block), 300, HEIGHT / 2 + 140, 24, WHITE);
			DrawText(TextFormat("Normal attack damage: %d", (*h)->minNDMG), 300, HEIGHT / 2 + 180, 24, WHITE);
			DrawText(TextFormat("Heavy attack damage: %d", (*h)->minHDMG), 300, HEIGHT / 2 + 220, 24, WHITE);
			DrawText(TextFormat("Special value: %d", (*h)->spValue), 300, HEIGHT / 2 + 260, 24, WHITE);
			DrawText(TextFormat("Evasion: %d%", (*h)->evasion), 300, HEIGHT / 2 + 300, 24, WHITE);
			DrawText(TextFormat("Buff duration: %d", (*h)->buffsN), 300, HEIGHT / 2 + 340, 24, WHITE);
			DrawText(TextFormat("Gold: %d", (*h)->gold), 300, HEIGHT / 2 + 380, 24, WHITE);
			DrawText(TextFormat("Effect in moves: %d", (*h)->ability->abilityVal), 650, HEIGHT / 2 + 100, 24, WHITE);
			DrawText(TextFormat("Maximum delay: %d", (*h)->ability->maxDelay), 650, HEIGHT / 2 + 140, 24, WHITE);
			DrawText(TextFormat("Current delay: %d", (*h)->ability->curDelay), 650, HEIGHT / 2 + 180, 24, WHITE);
			DrawText(TextFormat("Status duration: %d", (*h)->ability->statusDur), 650, HEIGHT / 2 + 220, 24, WHITE);

			if(isBoss) DrawText("Boss", 1050, HEIGHT / 2 + 20, 24, WHITE);
			else DrawText("Enemy", 1050, HEIGHT / 2 + 20, 24, WHITE);
			DrawText(TextFormat("HP: %d/%d", (*en)->hp, (*en)->maxHP), 1050, HEIGHT / 2 + 60, 24, WHITE);
			DrawText(TextFormat("Normal attack damage: %d", (*en)->minNDMG), 1050, HEIGHT / 2 + 100, 24, WHITE);
			DrawText(TextFormat("Heavy attack damage: %d", (*en)->minHDMG), 1050, HEIGHT / 2 + 140, 24, WHITE);
			DrawText(TextFormat("Special value: %d", (*en)->spValue), 1050, HEIGHT / 2 + 180, 24, WHITE);
			DrawText(TextFormat("Gold reward: %d%", (*en)->rewGold), 1050, HEIGHT / 2 + 220, 24, WHITE);
			DrawText(TextFormat("Current debuff value: %d%", (*en)->modInMoves), 1050, HEIGHT / 2 + 260, 24, WHITE);

			DrawText(TextFormat("Room %d%", (*sv)->roomNum), 20, 20, 30, WHITE);

			if ((*en)->enemType == 1) DrawTextureRec(enemyTexture, frameRec, { WIDTH / 2 - 90, HEIGHT / 4 - 210 }, WHITE);

			ClearBackground(WHITE);
			EndDrawing();
			(*a2).update();
			if (WindowShouldClose()) shouldExit = true;
			if (shouldExit) break;
		}
		if (shouldExit) break;
		switch (sel)
		{
		case 1:
			if ((*h)->ability->curDelay > 0) (*h)->ability->curDelay--;
			(*h)->Attack(&res, en);
			break;
		case 2:
			if ((*h)->ability->curDelay > 0) (*h)->ability->curDelay--;
			(*h)->HeavyAttack(&res, en);
			break;
		case 3:
			if ((*h)->ability->curDelay > 0) (*h)->ability->curDelay--;
			(*h)->Special(&res);
			break;
		case 4:
			(*h)->useAbility(&res, h, en);
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
			else if ((*sv)->charact == 3) (*r)->spValue = rand() % 2;
			(*h)->gold += (*r)->gold;
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
		if (sel >= 1 && sel <= 40) (*en)->Attack(&res, h);
		else if (sel >= 41 && sel >= 80) (*en)->HeavyAttack(&res, h);
		else (*en)->Special(&res);
		while(!IsKeyPressed(KEY_SPACE) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (IsKeyPressed(KEY_I)) shouldExit = OpenInfo(inf, sv, st, a2);
			BeginDrawing();
			if(res->hMiss) DrawText("Hero missed with", WIDTH / 2 - 85, HEIGHT / 2 - 300, 30, WHITE);
			else DrawText("Hero has done", WIDTH / 2 - 80, HEIGHT / 2 - 300, 30, WHITE);
			switch (res->hAct)
			{
			case 1:
				DrawText(*((*h)->nA), WIDTH / 2 - 65, HEIGHT / 2 - 250, 30, WHITE);
				break;
			case 2:
				DrawText(*((*h)->hA), WIDTH / 2 - 65, HEIGHT / 2 - 250, 30, WHITE);
				break;
			case 3:
				DrawText(*((*h)->sp), WIDTH / 2 - 65, HEIGHT / 2 - 250, 30, WHITE);
				break;
			case 4:
				DrawText(*((*h)->ability->abTitle), WIDTH / 2 - 65, HEIGHT / 2 - 250, 30, WHITE);
				DrawText(TextFormat("for %d moves", res->hVal), WIDTH / 2 - 75, HEIGHT / 2 - 200, 30, WHITE);
				break;
			}
			if (!res->hMiss && res->hAct != 3 && res->hAct != 4) DrawText(TextFormat("and dealt %d damage", res->hVal)
				, WIDTH / 2 - 100, HEIGHT / 2 - 200, 30, WHITE);
			else if(!res->hMiss && res->hAct != 4) DrawText(TextFormat("and get %d buff of this hero", res->hVal)
				, WIDTH / 2 - 170, HEIGHT / 2 - 200, 30, WHITE);
			if ((*sv)->charact == 3 && res->hAct == 2)
				DrawText(TextFormat("and gained shield by value of %d", res->hAdd)
					, WIDTH / 2 - 200, HEIGHT / 2 - 150, 30, WHITE);
			DrawText("Enemy", WIDTH / 2 - 20, HEIGHT / 2 - 50, 30, WHITE);
			if (!res->enMiss && res->enAct != 3) DrawText(TextFormat("dealt %d damage", res->enVal)
				, WIDTH / 2 - 80, HEIGHT / 2, 30, WHITE);
			else if (!res->enMiss) DrawText(TextFormat("healed by value of %d", res->enVal)
				, WIDTH / 2 - 110, HEIGHT / 2, 30, WHITE);
			else if(res->enMiss && res->enAct != 3) DrawText("missed"
				, WIDTH / 2 - 25, HEIGHT / 2, 30, WHITE);
			else DrawText("couldn't heal" , WIDTH / 2 - 60, HEIGHT / 2, 30, WHITE);
			DrawText("Press Space to continue", WIDTH / 2 - 150, HEIGHT / 2 + 150, 30, WHITE);
			ClearBackground(DARKBLUE);
			EndDrawing();
			(*a2).update();
			if (WindowShouldClose()) shouldExit = true;
			if (shouldExit) break;
		}
		if (shouldExit) break;
	}
	UnloadTexture(enemyTexture);
	UnloadTexture(bg);
	if (res != nullptr)
	{
		delete res;
		res = nullptr;
	}
	if (shouldExit) return true;
	else return false;
}

bool Shop(Hero** h, Save** sv, double* st, Info* inf, Audio* a2)
{
	static bool shouldExit;
	static short sel;
	static Vector2 mPos;
	static int i;
	static Texture2D bg;
	bg = LoadTexture("src/bg.png");
	short* value = new short[5];
	short* price = new short[5];
	bool* isActive = new bool[5];
	i = 0;
	for (i = 0; i < 5; i++) isActive[i] = true;
	value[0] = rand() % 15 + 5;
	price[0] = value[0];
	value[1] = rand() % 6 + 4;
	price[1] = value[1] * 3;
	value[2] = rand() % 6 + 4;
	price[2] = value[2] * 3;
	value[3] = rand() % 4 + 1;
	price[3] = value[3] * 8;
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
	else if ((*sv)->charact == 3)
	{
		value[4] = rand() % 4 + 1;
		price[4] = value[4] * 10;
	}
	if ((*h)->evasion >= 60) isActive[3] = false;
	sel = 0;
	shouldExit = false;
	while (!IsKeyPressed(KEY_B) && !IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !shouldExit)
	{
		mPos = GetMousePosition();
		if (GetTime() - *st >= 60)
		{
			*st = GetTime();
			(*sv)->minutes++;
			if ((*sv)->minutes == 60) (*sv)->hours++;
			if ((*sv)->hours == 24) (*sv)->days++;
		}
		if (IsKeyPressed(KEY_I)) shouldExit = OpenInfo(inf, sv, st, a2);
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
		DrawTexture(bg, 0, 0, WHITE);
		DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, WHITE);

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

		DrawText("Shop", WIDTH / 2 - 20, HEIGHT / 2 + 20, 30, WHITE);

		DrawText(TextFormat("+%d maximum HP", value[0]), 100, HEIGHT / 4 * 3 - 12, 24, WHITE);
		DrawRectangleLines(110, HEIGHT / 4 * 3 + 40, 150, 40, WHITE);
		DrawText(TextFormat("%d G", price[0]), 170, HEIGHT / 4 * 3 + 48, 24, WHITE);

		DrawText(TextFormat("+%d minimum normal DMG", value[1]), 350, HEIGHT / 4 * 3 - 12, 24, WHITE);
		DrawRectangleLines(410, HEIGHT / 4 * 3 + 40, 150, 40, WHITE);
		DrawText(TextFormat("%d G", price[1]), 465, HEIGHT / 4 * 3 + 48, 24, WHITE);

		DrawText(TextFormat("+%d minimum heavy DMG", value[2]), 700, HEIGHT / 4 * 3 - 12, 24, WHITE);
		DrawRectangleLines(760, HEIGHT / 4 * 3 + 40, 150, 40, WHITE);
		DrawText(TextFormat("%d G", price[2]), 815, HEIGHT / 4 * 3 + 48, 24, WHITE);

		DrawText(TextFormat("+%d evasion", value[3]), 1075, HEIGHT / 4 * 3 - 12, 24, WHITE);
		DrawRectangleLines(1065, HEIGHT / 4 * 3 + 40, 150, 40, WHITE);
		DrawText(TextFormat("%d G", price[3]), 1120, HEIGHT / 4 * 3 + 48, 24, WHITE);

		DrawText(TextFormat("+%d special value", value[4]), 1300, HEIGHT / 4 * 3 - 12, 24, WHITE);
		DrawRectangleLines(1335, HEIGHT / 4 * 3 + 40, 150, 40, WHITE);
		DrawText(TextFormat("%d G", price[4]), 1390, HEIGHT / 4 * 3 + 48, 24, WHITE);

		DrawText(TextFormat("%d G", (*h)->gold), 70, HEIGHT / 2 + 20, 24, WHITE);

		DrawText(TextFormat("Room %d%", (*sv)->roomNum), 20, 20, 30, WHITE);

		ClearBackground(WHITE);
		EndDrawing();
		(*a2).update();
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
	UnloadTexture(bg);
	if (shouldExit) return true;
	else return false;
}

bool RestRoom(Hero** h, Save** sv, double* st, Info* inf, Audio* a2)
{
	static short sel;
	static bool confirmation;
	static bool shouldExit;
	static Vector2 mPos;
	static Texture2D bg;
	bg = LoadTexture("src/bg.png");
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
		if (IsKeyPressed(KEY_I)) shouldExit = OpenInfo(inf, sv, st, a2);
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
		DrawTexture(bg, 0, 0, WHITE);
		DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, WHITE);

		DrawText("Rest Room", WIDTH / 2 - 80, HEIGHT / 2 + 20, 30, WHITE);

		switch (sel)
		{
		case 1:
			DrawRectangle(WIDTH / 2 - 100, HEIGHT / 2 + 120, 200, 60, YELLOW);
			break;
		case 2:
			DrawRectangle(WIDTH / 2 - 100, HEIGHT / 2 + 220, 200, 60, YELLOW);
			break;
		}

		DrawRectangleLines(WIDTH / 2 - 100, HEIGHT / 2 + 120, 200, 60, WHITE);
		DrawText("Rest", WIDTH / 2 - 25, HEIGHT / 2 + 138, 24, WHITE);

		DrawRectangleLines(WIDTH / 2 - 100, HEIGHT / 2 + 220, 200, 60, WHITE);
		DrawText("Random upgrade", WIDTH / 2 - 95, HEIGHT / 2 + 238, 24, WHITE);

		DrawText(TextFormat("Room %d%", (*sv)->roomNum), 20, 20, 30, WHITE);

		ClearBackground(WHITE);
		EndDrawing();
		(*a2).update();
		if (WindowShouldClose()) shouldExit = true;
	}
	if (shouldExit)
	{
		UnloadTexture(bg);
		return true;
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
			if((*h)->evasion < 60) (*h)->evasion += 1;
			break;
		case 5:
			if ((*sv)->charact == 1)(*h)->spValue += rand() % 3 + 1;
			else if ((*sv)->charact == 3) (*h)->spValue += 1;
			break;
		}
	}
	while (!IsKeyPressed(KEY_SPACE) && !IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		if (IsKeyPressed(KEY_I)) shouldExit = OpenInfo(inf, sv, st, a2);
		BeginDrawing();
		DrawText("Press Space to continue", WIDTH / 2 - 150, HEIGHT / 2 - 200, 30, BLACK);
		ClearBackground(DARKBLUE);
		EndDrawing();
		(*a2).update();
	}
	UnloadTexture(bg);
	return false;
}