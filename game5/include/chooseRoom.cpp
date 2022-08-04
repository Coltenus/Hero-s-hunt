#include "chooseRoom.h"
#include <iostream>
#include <raylib.hpp>
#include "rooms.h"
#include "info.h"

bool NextRoom(Hero** h, Save** sv, double* st, bool* shouldExit, Info* inf, Audio* a2)
{
	static Rewards* r;
	static bool isNewRoom;
	static Texture2D enemyTexture, bg;
	static Rectangle frameRec;
	static Item* i1, *i2;
	static short itemLeft, sel;
	static Vector2 mPos;
	static bool confirm, isItemTaken;
	isItemTaken = false;
	isNewRoom = true;
	(*sv)->roomNum++;
	r = new Rewards;
	r->isActive = false;
	Enemy* en;
	en = NULL;
	if((*sv)->enemyStats.enType == 0) (*sv)->enemyStats.enType = rand() % 2 + 1;
	else
	{
		isNewRoom = false;
		switch ((*sv)->enemyStats.enType)
		{
		case 1:
			en = new Zombie(1);
			break;
		case 2:
			en = new Rogue(1);
			break;
		default:
			en = new Zombie(1);
			break;
		}
		en->hp = (*sv)->enemyStats.hp;
		en->maxHP = (*sv)->enemyStats.maxHP;
		en->minNDMG = (*sv)->enemyStats.dmgN;
		en->minHDMG = (*sv)->enemyStats.dmgH;
		en->modAt = (*sv)->enemyStats.modAt;
		en->rewGold = (*sv)->enemyStats.rewGold;
		en->spValue = (*sv)->enemyStats.spV;
		en->modInMoves = (*sv)->enemyStats.modIM;
	}
	if (isNewRoom && (*sv)->roomNum != 15)
	{
		switch ((*sv)->enemyStats.enType)
		{
		case 1:
			en = new Zombie((*sv)->roomNum);
			break;
		case 2:
			en = new Rogue((*sv)->roomNum);
			break;
		default:
			en = new Zombie((*sv)->roomNum);
			break;
		}
	}
	if (isNewRoom && (*sv)->roomType == 0) (*sv)->roomType = rand() % 100 + 1;
	while (!IsKeyPressed(KEY_SPACE) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !(*shouldExit))
	{
		if (GetTime() - *st >= 60)
		{
			*st = GetTime();
			(*sv)->minutes++;
			if ((*sv)->minutes == 60) (*sv)->hours++;
			if ((*sv)->hours == 24) (*sv)->days++;
		}
		if (IsKeyPressed(KEY_I)) *shouldExit = OpenInfo(inf, sv, st, a2);
		if (WindowShouldClose()) *shouldExit = true;
		BeginDrawing();
		DrawText(TextFormat("Room %hu", (*sv)->roomNum), WIDTH / 2 - 25, HEIGHT / 2 - 150, 30, BLACK);
		if((*sv)->roomNum == 15) DrawText("Boss", WIDTH / 2 - 15, HEIGHT / 2 - 50, 30, BLACK);
		else if ((*sv)->roomType >= 1 && (*sv)->roomType <= 60)
		{
			DrawText("Battle against", WIDTH / 2 - 75, HEIGHT / 2 - 50, 30, BLACK);
			switch ((*sv)->enemyStats.enType)
			{
			case 1:
				DrawText("Zombie", WIDTH / 2 - 20, HEIGHT / 2, 30, BLACK);
				break;
			case 2:
				DrawText("Rogue", WIDTH / 2 - 20, HEIGHT / 2, 30, BLACK);
				break;
			default:
				DrawText("Enemy", WIDTH / 2 - 20, HEIGHT / 2, 30, BLACK);
				break;
			}
		}
		else if((*sv)->roomType >= 61 && (*sv)->roomType <= 80) DrawText("Shop", WIDTH / 2 - 20, HEIGHT / 2 - 50, 30, BLACK);
		else DrawText("Rest room", WIDTH / 2 - 50, HEIGHT / 2 - 50, 30, BLACK);
		DrawText("Press Space to continue", WIDTH / 2 - 150, HEIGHT / 2 + 100, 30, BLACK);
		ClearBackground(DARKBLUE);
		EndDrawing();
		(*a2).update();
	}
	if((*sv)->roomNum == 15 && !(*shouldExit))
	{
	    if(isNewRoom) en = new Zombie((*sv)->roomNum*2);
	    *shouldExit = Battle(h, &en, &r, sv, inf, st, true, a2);
		if ((*h)->hp <= 0 || (*h)->hp > 0 && en->hp <= 0) return false;
		else *shouldExit = true;
	}
	if (*shouldExit) return false;
	if ((*sv)->roomType >= 1 && (*sv)->roomType <= 60 && !(*shouldExit)) *shouldExit = Battle(h, &en, &r, sv, inf, st, false, a2);
	else if((*sv)->roomType >= 61 && (*sv)->roomType <= 80 && !(*shouldExit)) *shouldExit = Shop(h, sv, st, inf, a2);
	else if((*sv)->roomType >= 81 && (*sv)->roomType <= 100 && !(*shouldExit)) *shouldExit = RestRoom(h, sv, st, inf, a2);
	if (en->enemType != 0)
	{
		switch ((*sv)->enemyStats.enType)
		{
		case 1:
			enemyTexture = LoadTexture("src/Zombie.png");
			break;
		case 2:
			enemyTexture = LoadTexture("src/Zombie.png");
			break;
		default:
			enemyTexture = LoadTexture("src/Zombie.png");
			break;
		}
		frameRec = { (float)enemyTexture.width / 4 * 3, 0, (float)enemyTexture.width / 4, (float)enemyTexture.height };
	}
	if (r->isActive)
	{
		confirm = false;
		itemLeft = 0;
		sel = 0;
		switch (r->item1)
		{
		case 1:
			i1 = new Healing((*sv)->roomNum);
			break;
		case 2:
			i1 = new Block((*sv)->roomNum);
			break;
		case 3:
			i1 = new DmgPotion((*sv)->roomNum);
			break;
		case 4:
			i1 = new UpMaxHP((*sv)->roomNum);
			break;
		}
		switch (r->item2)
		{
		case 1:
			i2 = new Healing((*sv)->roomNum);
			break;
		case 2:
			i2 = new Block((*sv)->roomNum);
			break;
		case 3:
			i2 = new DmgPotion((*sv)->roomNum);
			break;
		case 4:
			i2 = new UpMaxHP((*sv)->roomNum);
			break;
		}
	}
	while (r->isActive && !(*shouldExit))
	{
		bg = LoadTexture("src/bg.png");
		if (GetTime() - *st >= 60)
		{
			*st = GetTime();
			(*sv)->minutes++;
			if ((*sv)->minutes == 60) (*sv)->hours++;
			if ((*sv)->hours == 24) (*sv)->days++;
		}
		if (IsKeyPressed(KEY_I)) *shouldExit = OpenInfo(inf, sv, st, a2);
		if (IsKeyPressed(KEY_B) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) r->isActive = false;
		if (!confirm)
		{
			mPos = GetMousePosition();
			if (IsKeyPressed(KEY_DOWN) && sel < 3)
				sel++;
			if (IsKeyPressed(KEY_UP) && sel > 1)
				sel--;
			if (mPos.x >= WIDTH / 2 - 550 && mPos.x <= WIDTH / 2 - 350
				&& mPos.y >= HEIGHT / 2 - 400 && mPos.y <= HEIGHT / 2 - 300)
				sel = 1;
			if (mPos.x >= WIDTH / 2 - 100 && mPos.x <= WIDTH / 2 + 100
				&& mPos.y >= HEIGHT / 2 - 400 && mPos.y <= HEIGHT / 2 - 300)
				sel = 2;
			if (mPos.x >= WIDTH / 2 + 350 && mPos.x <= WIDTH / 2 + 550
				&& mPos.y >= HEIGHT / 2 - 400 && mPos.y <= HEIGHT / 2 - 300)
				sel = 3;
			if (IsKeyPressed(KEY_ENTER) && sel >= 1 && sel <= 3 || IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
				(mPos.x >= WIDTH / 2 - 550 && mPos.x <= WIDTH / 2 - 350
					&& mPos.y >= HEIGHT / 2 - 400 && mPos.y <= HEIGHT / 2 - 300
					|| mPos.x >= WIDTH / 2 - 100 && mPos.x <= WIDTH / 2 + 100
					&& mPos.y >= HEIGHT / 2 - 400 && mPos.y <= HEIGHT / 2 - 300
					|| mPos.x >= WIDTH / 2 + 350 && mPos.x <= WIDTH / 2 + 550
					&& mPos.y >= HEIGHT / 2 - 400 && mPos.y <= HEIGHT / 2 - 300))
				confirm = true;
		}
		
		if (WindowShouldClose()) *shouldExit = true;
		BeginDrawing();
		DrawTexture(bg, 0, 0, WHITE);
		if (!confirm)
		{
			switch (sel)
			{
			case 1:
				DrawRectangle(WIDTH / 2 - 550, HEIGHT / 2 - 400, 200, 100, YELLOW);
				break;
			case 2:
				DrawRectangle(WIDTH / 2 - 100, HEIGHT / 2 - 400, 200, 100, YELLOW);
				break;
			case 3:
				DrawRectangle(WIDTH / 2 + 350, HEIGHT / 2 - 400, 200, 100, YELLOW);
				break;
			}
		}
		else
		{
			if (!isItemTaken && (*h)->findFreeSlot() < (*h)->slotN)
			{
				switch (sel)
				{
				case 1:
					(*h)->setItem(i1);
					itemLeft = 2;
					break;
				case 2:
					(*h)->setItem(i2);
					itemLeft = 1;
					break;
				}
				isItemTaken = true;
			}
			DrawRectangle(WIDTH / 2 - 550, HEIGHT / 2 - 400, 200, 100, GRAY);
			DrawRectangle(WIDTH / 2 - 100, HEIGHT / 2 - 400, 200, 100, GRAY);
			DrawRectangle(WIDTH / 2 + 350, HEIGHT / 2 - 400, 200, 100, GRAY);
		}
		DrawRectangleLines(20, HEIGHT / 2, WIDTH - 40, HEIGHT / 2 - 20, WHITE);
		DrawTextureRec(enemyTexture, frameRec, { WIDTH / 2 - 75, HEIGHT / 2 - 450 }, WHITE);
		DrawText(TextFormat("Room %hu", (*sv)->roomNum), WIDTH / 2 - 25, HEIGHT / 2 + 50, 30, WHITE);
		DrawText(TextFormat("+%hu gold", r->gold), WIDTH / 2 - 25, HEIGHT / 2 + 200, 30, WHITE);
		DrawText(TextFormat("+%hu hp", r->hp), 100, HEIGHT / 2 + 300, 24, WHITE);
		DrawText(TextFormat("+%hu min normal DMG", r->minNDMG), 400, HEIGHT / 2 + 300, 24, WHITE);
		DrawText(TextFormat("+%hu min heavy DMG", r->minNDMG), 700, HEIGHT / 2 + 300, 24, WHITE);
		DrawText(TextFormat("+%hu special value", r->spValue), 1000, HEIGHT / 2 + 300, 24, WHITE);
		DrawText(TextFormat("+%hu evasion", r->evasion), 1300, HEIGHT / 2 + 300, 24, WHITE);

		DrawText("Choose your reward item", WIDTH / 2 - 180, HEIGHT / 2 - 440, 30, WHITE);

		DrawRectangleLines(WIDTH / 2 - 550, HEIGHT / 2 - 400, 200, 100, WHITE);
		DrawText(*(i1->getName()), WIDTH / 2 - 540, HEIGHT / 2 - 363, 26, WHITE);
		switch (i1->getNum())
		{
		case 1:
			DrawText(TextFormat("Heals by value of %d", i1->getVal()), WIDTH / 2 - 550,
				HEIGHT / 2 - 290, 26, WHITE);
			break;
		case 2:
			DrawText(TextFormat("Gives block by value of %d", i1->getVal()), WIDTH / 2 - 550,
				HEIGHT / 2 - 290, 26, WHITE);
			break;
		case 3:
			DrawText(TextFormat("Deal damage to the\nenemy by value of %d", i1->getVal()),
				WIDTH / 2 - 550, HEIGHT / 2 - 290, 26, WHITE);
			break;
		case 4:
			DrawText(TextFormat("Ups your maximum Hp\nby value of %d", i1->getVal()),
				WIDTH / 2 - 550, HEIGHT / 2 - 290, 26, WHITE);
			break;
		}

		DrawRectangleLines(WIDTH / 2 - 100, HEIGHT / 2 - 400, 200, 100, WHITE);
		DrawText(*(i2->getName()), WIDTH / 2 - 90, HEIGHT / 2 - 363, 26, WHITE);
		switch (i2->getNum())
		{
		case 1:
			DrawText(TextFormat("Heals by value of %d", i2->getVal()), WIDTH / 2 - 100,
				HEIGHT / 2 - 290, 26, WHITE);
			break;
		case 2:
			DrawText(TextFormat("Gives block by value of %d", i2->getVal()), WIDTH / 2 - 100,
				HEIGHT / 2 - 290, 26, WHITE);
			break;
		case 3:
			DrawText(TextFormat("Deal damage to the\nenemy by value of %d", i2->getVal()),
				WIDTH / 2 - 100, HEIGHT / 2 - 290, 26, WHITE);
			break;
		case 4:
			DrawText(TextFormat("Ups your maximum Hp\nby value of %d", i2->getVal()),
				WIDTH / 2 - 100, HEIGHT / 2 - 290, 26, WHITE);
			break;
		}

		DrawRectangleLines(WIDTH / 2 + 350, HEIGHT / 2 - 400, 200, 100, WHITE);
		DrawText("Decline", WIDTH / 2 + 360, HEIGHT / 2 - 363, 26, WHITE);

		ClearBackground(WHITE);
		EndDrawing();
		(*a2).update();
		UnloadTexture(bg);
	}
	if (itemLeft != -1)
	{
		switch (itemLeft)
		{
		case 0:
			delete i1;
			delete i2;
			i1 = nullptr;
			i2 = nullptr;
			break;
		case 1:
			delete i1;
			i1 = nullptr;
			break;
		case 2:
			delete i2;
			i2 = nullptr;
			break;
		}
		itemLeft = -1;
	}
	if (*shouldExit)
	{
		UnloadTexture(enemyTexture);
		if (en != NULL)
		{
			(*sv)->enemyStats.hp = en->hp;
			(*sv)->enemyStats.maxHP = en->maxHP;
			(*sv)->enemyStats.dmgN = en->minNDMG;
			(*sv)->enemyStats.dmgH = en->minHDMG;
			(*sv)->enemyStats.modAt = en->modAt;
			(*sv)->enemyStats.rewGold = en->rewGold;
			(*sv)->enemyStats.spV = en->spValue;
			(*sv)->enemyStats.modIM = en->modInMoves;
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
	UnloadTexture(enemyTexture);
	return true;
}