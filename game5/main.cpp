#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <iostream>
#include <raylib.hpp>
#include <time.h>
using namespace std;

#define DEBUG

#include "include/common.h"
#include "include/characters.h"
#include "include/chooseRoom.h"
#include "include/audio.h"


void FillFile();
void EnterUsername(Info**, bool*);
int SelectionMenu(Info**, int*);
void GameProcess(Info**, int, bool*, short (*)(short*, bool*), short (*)(short, bool*));
short SelectHero(short*, bool*);
short SelectAbility(short, bool*);
void CheckStartConditions(int, char**, bool*);
int StartMenu(Info**, int*);
int HelpMenu();

int main(int argc, char** argv)
{
	bool shouldExit = false;
#ifndef DEBUG
	CheckStartConditions(argc, argv, &shouldExit);
#endif
	if (!shouldExit)
	{
		InitAudioDevice();
		char** a = new char* [15];
		*a = (char*)"src/sound0.mp3";
		Audio a1(a);
		delete[] a;
		a = nullptr;
		srand((unsigned)time(NULL));
		int curSave = 0;
		int sel = 0;
		double st = -1;
		Info* inf;
		FILE* sv = fopen("saves/info", "rb");
		if (sv == NULL)
		{
			FillFile();
			sv = fopen("saves/info", "rb");
		}
		inf = new Info;
		fread(inf, sizeof(Info), 1, sv);
		fclose(sv);
		InitWindow(WIDTH, HEIGHT, "Game 5");
		SetTargetFPS(60);
		if (inf->username[2] == '\0') EnterUsername(&inf, &shouldExit);
		while (!IsKeyPressed(KEY_ENTER) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !shouldExit)
		{
			BeginDrawing();
			DrawText("Press Enter to continue", WIDTH / 2 - 160, HEIGHT / 2 - 200, 30, BLACK);
			ClearBackground(SKYBLUE);
			EndDrawing();
			if (WindowShouldClose()) shouldExit = true;
		}
		while (!WindowShouldClose() && !shouldExit)
		{
			a1.update();
			switch (curSave)
			{
			case 0:
				curSave = StartMenu(&inf, &sel);
				break;
			case 4:
				curSave = SelectionMenu(&inf, &sel);
				break;
			case 5:
				curSave = HelpMenu();
				break;
			case 6:
				shouldExit = true;
				break;
			case 1:
				a1.stop();
				GameProcess(&inf, 1, &shouldExit, SelectHero, SelectAbility);
				a1.start();
				shouldExit = false;
				curSave = 0;
				sel = 0;
				break;
			case 2:
				a1.stop();
				GameProcess(&inf, 2, &shouldExit, SelectHero, SelectAbility);
				a1.start();
				shouldExit = false;
				curSave = 0;
				sel = 0;
				break;
			case 3:
				a1.stop();
				GameProcess(&inf, 3, &shouldExit, SelectHero, SelectAbility);
				a1.start();
				shouldExit = false;
				curSave = 0;
				sel = 0;
				break;
			}
		}
		CloseWindow();
		if (inf != NULL)
		{
			sv = fopen("saves/info", "rb+");
			if (sv != NULL)
			{
				fseek(sv, 0, SEEK_SET);
				fwrite(inf, sizeof(Info), 1, sv);
				fclose(sv);
			}
		}
		delete inf;
		inf = nullptr;
		CloseAudioDevice();
	}
	return 0;
}

void FillFile()
{
	int i;
	FILE* f;
	Info* inf;
	inf = new Info;
	f = fopen("saves/info", "wb");
	i = 0;
	while (i < 20)
	{
		inf->username[i] = '\0';
		i++;
	}
	fwrite(inf, sizeof(Info), 1, f);
	fclose(f);
	delete inf;
	inf = NULL;
}

void EnterUsername(Info** inf, bool* shouldExit)
{
	int key;
	char *buf = new char[20];
	int i = 0;
	while (i < 20)
	{
		buf[i] = '\0';
		i++;
	}
	while (buf[2] == '\0' && !(*shouldExit))
	{
		i = 0;
		while (i < 20)
		{
			buf[i] = '\0';
			i++;
		}
		i = 0;
		while (!(*shouldExit))
		{
			key = GetCharPressed();
			if ((key >= 97 && key <= 122 || key >= 65 && key <= 90 || key >= 48 && key <= 57 || key == 45 || key == 95 || key == 39) && i < 19)
			{
				buf[i] = (char)key;
				i++;
			}
			else key = 0;
			if (IsKeyPressed(KEY_BACKSPACE) && i > 0)
			{
				i--;
				buf[i] = '\0';
			}
			BeginDrawing();
			DrawText("\t\t\t\tChoose your username\n (must be three symbols minimum)", WIDTH / 2 - 250, HEIGHT / 2 - 130, 30, BLACK);
			DrawRectangleLines(WIDTH / 2 - 130, HEIGHT / 2 - 20, 260, 40, BLACK);
			DrawText(buf, WIDTH / 2 - 125, HEIGHT / 2 - 12, 24, BLACK);
			DrawFPS(0, 0);
			ClearBackground(SKYBLUE);
			EndDrawing();
			if (IsKeyPressed(KEY_ENTER)) break;
			if (WindowShouldClose()) *shouldExit = true;
		}
	}
	if (buf[2] != '\0' && !(*shouldExit))
	{
		i = 0;
		while (i < 20)
		{
			(*inf)->username[i] = buf[i];
			i++;
		}
	}
	delete[] buf;
}

int SelectionMenu(Info** i, int *sel)
{
	static Vector2 mPos;
	static char** buf;
	static Save* save;
	static FILE* f;
	mPos = GetMousePosition();
	BeginDrawing();
	if (IsKeyPressed(KEY_DOWN) && *sel < 6)
		(*sel)++;
	if (IsKeyPressed(KEY_UP) && *sel > 1)
		(*sel)--;
	if (mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
		&& mPos.y >= HEIGHT / 2 - 200 && mPos.y <= HEIGHT / 2 - 120) *sel = 1;
	if (mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
		&& mPos.y >= HEIGHT / 2 - 20 && mPos.y <= HEIGHT / 2 + 60) *sel = 2;
	if (mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
		&& mPos.y >= HEIGHT / 2 + 160 && mPos.y <= HEIGHT / 2 + 240) *sel = 3;
	if (mPos.x >= WIDTH / 2 + 170 && mPos.x <= WIDTH / 2 + 250
		&& mPos.y >= HEIGHT / 2 - 200 && mPos.y <= HEIGHT / 2 - 120) *sel = 4;
	if (mPos.x >= WIDTH / 2 + 170 && mPos.x <= WIDTH / 2 + 250
		&& mPos.y >= HEIGHT / 2 - 20 && mPos.y <= HEIGHT / 2 + 60) *sel = 5;
	if (mPos.x >= WIDTH / 2 + 170 && mPos.x <= WIDTH / 2 + 250
		&& mPos.y >= HEIGHT / 2 + 160 && mPos.y <= HEIGHT / 2 + 240) *sel = 6;
	switch (*sel)
	{
	case 1:
		DrawRectangle(WIDTH / 2 - 150, HEIGHT / 2 - 200, 300, 80, YELLOW);
		break;
	case 2:
		DrawRectangle(WIDTH / 2 - 150, HEIGHT / 2 - 20, 300, 80, YELLOW);
		break;
	case 3:
		DrawRectangle(WIDTH / 2 - 150, HEIGHT / 2 + 160, 300, 80, YELLOW);
		break;
	case 4:
		DrawRectangle(WIDTH / 2 + 170, HEIGHT / 2 - 200, 80, 80, YELLOW);
		break;
	case 5:
		DrawRectangle(WIDTH / 2 + 170, HEIGHT / 2 - 20, 80, 80, YELLOW);
		break;
	case 6:
		DrawRectangle(WIDTH / 2 + 170, HEIGHT / 2 + 160, 80, 80, YELLOW);
		break;
	}
	DrawText("Choose save file", WIDTH / 2 - 120, HEIGHT / 2 - 320, 30, BLACK);

	DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 - 200, 300, 80, BLACK);
	DrawText(TextFormat("%d", 1), WIDTH / 2 - 6, HEIGHT / 2 - 172, 24, BLACK);
	DrawRectangleLines(WIDTH / 2 + 170, HEIGHT / 2 - 200, 80, 80, BLACK);
	DrawText("Clear", WIDTH / 2 + 185, HEIGHT / 2 - 170, 20, BLACK);

	DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 - 20, 300, 80, BLACK);
	DrawText(TextFormat("%d", 2), WIDTH / 2 - 6, HEIGHT / 2 + 8, 24, BLACK);
	DrawRectangleLines(WIDTH / 2 + 170, HEIGHT / 2 - 20, 80, 80, BLACK);
	DrawText("Clear", WIDTH / 2 + 185, HEIGHT / 2 + 10, 20, BLACK);

	DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 + 160, 300, 80, BLACK);
	DrawText(TextFormat("%d", 3), WIDTH / 2 - 6, HEIGHT / 2 + 188, 24, BLACK);
	DrawRectangleLines(WIDTH / 2 + 170, HEIGHT / 2 + 160, 80, 80, BLACK);
	DrawText("Clear", WIDTH / 2 + 185, HEIGHT / 2 + 190, 20, BLACK);

	DrawText(TextFormat("Username: %s", (*i)->username), 50, 50, 30, BLACK);

	ClearBackground(SKYBLUE);
	EndDrawing();
	if ((IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && *sel >= 1 && *sel <= 3) return *sel;
	else if ((IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && *sel >= 4 && *sel <= 6)
	{

		buf = new char* [12];
		*buf = (char*)"";
		switch (*sel)
		{
		case 4:
			*buf = (char*)"saves/save1";
			break;
		case 5:
			*buf = (char*)"saves/save2";
			break;
		case 6:
			*buf = (char*)"saves/save3";
			break;
		}
		f = fopen(*buf, "rb");
		if (f != NULL)
		{
			f = fopen(*buf, "wb");
			save = new Save;
			save->minutes = 0;
			save->hours = 0;
			save->days = 0;
			save->gold = 0;
			save->order = *sel - 3;
			save->charact = 0;
			save->ability = 0;
			save->stats.dmgN = 0;
			save->stats.dmgH = 0;
			save->stats.evasion = 0;
			save->stats.hp = 0;
			save->stats.maxHP = 100;
			save->stats.spValue = 0;
			save->stats.block = 0;
			save->stats.buffN = 0;
			save->stats.curDelay = 0;
			save->enemyStats.modIM = 0;
			save->roomNum = 0;
			save->roomType = 0;
			save->enemyStats.enType = 0;
			save->enemyStats.dmgN = 0;
			save->enemyStats.dmgH = 0;
			save->enemyStats.hp = 0;
			save->enemyStats.maxHP = 0;
			save->enemyStats.modAt = 0;
			save->enemyStats.rewGold = 0;
			save->enemyStats.spV = 0;
			fwrite(save, sizeof(Save), 1, f);
			delete save;
			save = NULL;
			fclose(f);
		}
		delete[] buf;
		buf = nullptr;
		return 4;
	}
	else if (IsKeyPressed(KEY_X)) return 0;
	else return 4;
}

void GameProcess(Info** i, int sv, bool* shouldExit, short (*selH)(short*, bool*), short (*selAb)(short, bool*))
{
	static double st;
	static bool isReady;
	static Save* save;
	static FILE* f;
	static Hero* h;
	static Enemy* en;
	static short chooseH, room;
	static Audio a2;
	char** buf = new char* [15];
	*buf = (char*)"src/sound1.mp3";
	a2.setParameters(buf);
	delete[] buf;
	buf = new char* [12];
	*buf = (char*)"";
	switch (sv)
	{
	case 1:
		*buf = (char*)"saves/save1";
		break;
	case 2:
		*buf = (char*)"saves/save2";
		break;
	case 3:
		*buf = (char*)"saves/save3";
		break;
	}
	isReady = true;
	chooseH = 0;
	save = new Save;
	h = NULL;
	f = fopen(*buf, "rb");
	if (f == NULL)
	{
		f = fopen(*buf, "wb");
		save->minutes = 0;
		save->hours = 0;
		save->days = 0;
		save->gold = 0;
		save->order = sv;
		save->charact = 0;
		save->ability = 0;
		save->stats.dmgN = 0;
		save->stats.dmgH = 0;
		save->stats.evasion = 0;
		save->stats.hp = 0;
		save->stats.maxHP = 100;
		save->stats.spValue = 0;
		save->stats.block = 0;
		save->stats.buffN = 0;
		save->stats.curDelay = 0;
		save->enemyStats.modIM = 0;
		save->roomNum = 0;
		save->roomType = 0;
		save->enemyStats.enType = 0;
		save->enemyStats.dmgN = 0;
		save->enemyStats.dmgH = 0;
		save->enemyStats.hp = 0;
		save->enemyStats.maxHP = 0;
		save->enemyStats.modAt = 0;
		save->enemyStats.rewGold = 0;
		save->enemyStats.spV = 0;
		fwrite(save, sizeof(Save), 1, f);
		fclose(f);
		f = fopen(*buf, "rb");
	}
	fread(save, sizeof(Save), 1, f);
	while (save->charact == 0 && !(*shouldExit))
	{
		save->charact = selH(&chooseH, shouldExit);
	}
	if(save->ability == 0 && !(*shouldExit)) save->ability = selAb(save->charact, shouldExit);
	switch (save->charact)
	{
	case 1:
		h = new Swordsman;
		switch (save->ability)
		{
		case 1:
			h->setAbility(new SwAb1);
			break;
		}
		break;
	case 2:
		h = new Archer;
		switch (save->ability)
		{
		case 1:
			h->setAbility(new ArAb1);
			break;
		}
		break;
	case 3:
		h = new Paladin;
		switch (save->ability)
		{
		case 1:
			h->setAbility(new PalAb1);
			break;
		}
		break;
	}
	if (save->stats.hp != 0)
	{
		h->hp = save->stats.hp;
		h->maxHP = save->stats.maxHP;
		h->minNDMG = save->stats.dmgN;
		h->minHDMG = save->stats.dmgH;
		h->spValue = save->stats.spValue;
		h->evasion = save->stats.evasion;
		h->block = save->stats.block;
		h->buffsN = save->stats.buffN;
		h->ability->curDelay = save->stats.curDelay;
		h->gold = save->gold;
	}
	fclose(f);
	while (!IsKeyPressed(KEY_ENTER) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !(*shouldExit))
	{
		BeginDrawing();
		DrawText("Press Enter to start", WIDTH / 2 - 175, HEIGHT / 2 - 200, 30, BLACK);
		ClearBackground(SKYBLUE);
		EndDrawing();
		a2.update();
		if (WindowShouldClose()) *shouldExit = true;
	}
	st = GetTime();
	while (!IsKeyPressed(KEY_X) && !(*shouldExit))
	{
		if (GetTime() - st >= 60)
		{
			st = GetTime();
			save->minutes++;
			if (save->minutes == 60) save->hours++;
			if (save->hours == 24) save->days++;
		}
		if (isReady) isReady = NextRoom(&h, &save, &st, shouldExit, *i, &a2);
		else if(!(*shouldExit))
		{
			BeginDrawing();
			if(h->hp > 0) DrawText("You've won!", WIDTH / 2 - 90, HEIGHT / 2 - 150, 30, BLUE);
			else DrawText("You're dead...", WIDTH / 2 - 100, HEIGHT / 2 - 150, 30, RED);
			DrawText("Press X to exit", WIDTH / 2 - 100, HEIGHT / 2 + 150, 30, DARKBROWN);
			if (h->hp > 0) ClearBackground(SKYBLUE);
			else ClearBackground(BLACK);
			EndDrawing();
			a2.update();
		}
		if (WindowShouldClose()) *shouldExit = true;
	}
	f = fopen(*buf, "rb+");
	if (h != nullptr && (h->hp <= 0 || save->roomNum == 10 && h->hp > 0))
	{
		save->minutes = 0;
		save->hours = 0;
		save->days = 0;
		save->gold = 0;
		save->charact = 0;
		save->ability = 0;
		save->stats.dmgN = 0;
		save->stats.dmgH = 0;
		save->stats.evasion = 0;
		save->stats.hp = 0;
		save->stats.maxHP = 100;
		save->stats.spValue = 0;
		save->stats.block = 0;
		save->stats.buffN = 0;
		save->stats.curDelay = 0;
		save->enemyStats.modIM = 0;
		save->roomNum = 0;
		save->enemyStats.enType = 0;
		save->enemyStats.dmgN = 0;
		save->enemyStats.dmgH = 0;
		save->enemyStats.hp = 0;
		save->enemyStats.maxHP = 0;
		save->enemyStats.modAt = 0;
		save->enemyStats.rewGold = 0;
		save->enemyStats.spV = 0;
		fwrite(save, sizeof(Save), 1, f);
	}
	else if (save != NULL && h != NULL)
	{
		save->stats.hp = h->hp;
		save->stats.maxHP = h->maxHP;
		save->stats.dmgN = h->minNDMG;
		save->stats.dmgH = h->minHDMG;
		save->stats.spValue = h->spValue;
		save->stats.evasion = h->evasion;
		save->stats.block = h->block;
		save->stats.buffN = h->buffsN;
		if (h->ability != nullptr) save->stats.curDelay = h->ability->curDelay;
		else save->stats.curDelay = 0;
		save->gold = h->gold;
		if (shouldExit && save->roomNum > 0) save->roomNum--;
		fwrite(save, sizeof(Save), 1, f);
	}
	fclose(f);
	if (save != NULL)
	{
		delete save;
		save = nullptr;
	}
	if (buf != NULL)
	{
		delete[] buf;
		buf = nullptr;
	}
	if (h != NULL)
	{
		delete h;
		h = nullptr;
	}
	if (en != NULL)
	{
		delete en;
		en = nullptr;
	}
}

short SelectHero(short* sel, bool* shouldExit)
{
	static Vector2 mPos;
	static Hero* h;
	mPos = GetMousePosition();
	if (IsKeyPressed(KEY_DOWN) && *sel < 3)
		(*sel)++;
	if (IsKeyPressed(KEY_UP) && *sel > 1)
		(*sel)--;
	if (mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
		&& mPos.y >= HEIGHT / 2 - 200 && mPos.y <= HEIGHT / 2 - 120) *sel = 1;
	if (mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
		&& mPos.y >= HEIGHT / 2 - 20 && mPos.y <= HEIGHT / 2 + 60) *sel = 2;
	if (mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
		&& mPos.y >= HEIGHT / 2 + 160 && mPos.y <= HEIGHT / 2 + 240) *sel = 3;
	BeginDrawing();
	switch (*sel)
	{
	case 1:
		h = new Swordsman;
		DrawRectangle(WIDTH / 2 - 150, HEIGHT / 2 - 200, 300, 80, YELLOW);
		break;
	case 2:
		h = new Archer;
		DrawRectangle(WIDTH / 2 - 150, HEIGHT / 2 - 20, 300, 80, YELLOW);
		break;
	case 3:
		h = new Paladin;
		DrawRectangle(WIDTH / 2 - 150, HEIGHT / 2 + 160, 300, 80, YELLOW);
		break;
	}
	DrawText("Choose Hero", WIDTH / 2 - 110, HEIGHT / 2 - 320, 30, WHITE);

	DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 - 200, 300, 80, WHITE);
	DrawText("Swordsman", WIDTH / 2 - 65, HEIGHT / 2 - 172, 24, WHITE);

	DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 - 20, 300, 80, WHITE);
	DrawText("Archer", WIDTH / 2 - 40, HEIGHT / 2 + 8, 24, WHITE);

	DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 + 160, 300, 80, WHITE);
	DrawText("Paladin", WIDTH / 2 - 40, HEIGHT / 2 + 188, 24, WHITE);

	if (h != nullptr)
	{
		DrawText(*(h->nA), WIDTH / 2 + 200, HEIGHT / 2 - 260, 30, WHITE);
		DrawText(TextFormat("Minimal DMG: %d", h->minNDMG), WIDTH / 2 + 200, HEIGHT / 2 - 220, 30, WHITE);
		DrawText(TextFormat("Miss chance: %d%%", h->mcN), WIDTH / 2 + 200, HEIGHT / 2 - 180, 30, WHITE);

		DrawText(*(h->hA), WIDTH / 2 + 200, HEIGHT / 2 - 60, 30, WHITE);
		DrawText(TextFormat("Minimal DMG: %d", h->minHDMG), WIDTH / 2 + 200, HEIGHT / 2 - 20, 30, WHITE);
		DrawText(TextFormat("Miss chance: %d%%", h->mcH), WIDTH / 2 + 200, HEIGHT / 2 + 20, 30, WHITE);
		if(*sel == 2)DrawText("Do three independent attacks", WIDTH / 2 + 200, HEIGHT / 2 + 60, 30, WHITE);
		else if(*sel == 3) DrawText("As block gain 30% of\nminimal DMG value", WIDTH / 2 + 200, HEIGHT / 2 + 60, 30, WHITE);

		DrawText(*(h->sp), WIDTH / 2 + 200, HEIGHT / 2 + 220, 30, WHITE);
		DrawText(TextFormat("Special value: %d", h->spValue), WIDTH / 2 + 200, HEIGHT / 2 + 260, 30, WHITE);
		if(*sel == 3) DrawText("Randomly heal by a value\nfrom 1 to special value", WIDTH / 2 + 200, HEIGHT / 2 + 300, 30, WHITE);

		delete h;
		h = nullptr;
	}

	ClearBackground(DARKBLUE);
	EndDrawing();
	if (WindowShouldClose())
	{
		*shouldExit = true;
		return 0;
	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && *sel >= 1 && *sel <= 3) return *sel;
	if (IsKeyPressed(KEY_ENTER) && *sel >= 1 && *sel <= 3) return *sel;
	else return 0;
}

short SelectAbility(short h, bool* shouldExit)
{
	static Vector2 mPos;
	static Ability* ab1, *ab2, *ab3, *ab;
	static short sel;
	static bool confirm;
	ab = nullptr;
	confirm = false;
	sel = 0;
	switch (h)
	{
	case 1:
		ab1 = new SwAb1;
		ab2 = new SwAb1;
		ab3 = new SwAb1;
		break;
	case 2:
		ab1 = new ArAb1;
		ab2 = new ArAb1;
		ab3 = new ArAb1;
		break;
	case 3:
		ab1 = new PalAb1;
		ab2 = new PalAb1;
		ab3 = new PalAb1;
		break;
	}
	while (!confirm && !*(shouldExit))
	{
		mPos = GetMousePosition();
		if (IsKeyPressed(KEY_DOWN) && sel < 3)
			sel++;
		if (IsKeyPressed(KEY_UP) && sel > 1)
			sel--;
		if (mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
			&& mPos.y >= HEIGHT / 2 - 100 && mPos.y <= HEIGHT / 2 - 20) sel = 1;
		if (mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
			&& mPos.y >= HEIGHT / 2 + 80 && mPos.y <= HEIGHT / 2 + 140) sel = 2;
		if (mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
			&& mPos.y >= HEIGHT / 2 + 260 && mPos.y <= HEIGHT / 2 + 340) sel = 3;
		if (IsKeyPressed(KEY_ENTER) && sel >= 1 && sel <= 3 || IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
			(mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
				&& mPos.y >= HEIGHT / 2 - 100 && mPos.y <= HEIGHT / 2 - 20))
				//|| mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
				//&& mPos.y >= HEIGHT / 2 + 80 && mPos.y <= HEIGHT / 2 + 140
				//|| mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
				//&& mPos.y >= HEIGHT / 2 + 260 && mPos.y <= HEIGHT / 2 + 340)) 
				confirm = true;
		BeginDrawing();
		switch (sel)
		{
		case 1:
			ab = ab1;
			DrawRectangle(WIDTH / 2 - 150, HEIGHT / 2 - 100, 300, 80, YELLOW);
			break;
		case 2:
			//ab = ab2;
			DrawRectangle(WIDTH / 2 - 150, HEIGHT / 2 + 80, 300, 80, YELLOW);
			break;
		case 3:
			//ab = ab3;
			DrawRectangle(WIDTH / 2 - 150, HEIGHT / 2 + 260, 300, 80, YELLOW);
			break;
		}
		DrawText("Choose Ability", WIDTH / 2 - 120, HEIGHT / 2 - 220, 30, WHITE);

		DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 - 100, 300, 80, WHITE);
		DrawText(*(ab1->abTitle), WIDTH / 2 - 75, HEIGHT / 2 - 72, 24, WHITE);

		DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 + 80, 300, 80, WHITE);
		DrawText("Not working", WIDTH / 2 - 75, HEIGHT / 2 + 108, 24, WHITE);

		DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 + 260, 300, 80, WHITE);
		DrawText("Not working", WIDTH / 2 - 75, HEIGHT / 2 + 288, 24, WHITE);

		if (ab != nullptr)
		{
			DrawText(*(ab->abTitle), WIDTH / 2 + 200, HEIGHT / 2 - 100, 30, WHITE);
			DrawText(TextFormat("Effect time in moves: %d", ab->abilityVal), WIDTH / 2 + 200, HEIGHT / 2 - 60, 30, WHITE);
			DrawText(TextFormat("Cooldown in moves: %d", ab->maxDelay), WIDTH / 2 + 200, HEIGHT / 2 - 20, 30, WHITE);
			switch (sel)
			{
			case 1:
				switch (h)
				{
				case 1:
					DrawText("Disarms the enemy", WIDTH / 2 + 200, HEIGHT / 2 + 20, 30, WHITE);
					break;
				case 2:
					DrawText("Enemy loses 10% of\nhis maximum HP", WIDTH / 2 + 200, HEIGHT / 2 + 20, 30, WHITE);
					break;
				case 3:
					DrawText("Enemy deals damage to\nhimself with a 65% chance", WIDTH / 2 + 200, HEIGHT / 2 + 20, 30, WHITE);
					break;
				}
				break;
			case 2:
				switch (h)
				{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				}
				break;
			case 3:
				switch (h)
				{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				}
				break;
			}
		}

		ClearBackground(DARKBLUE);
		EndDrawing();
		if (WindowShouldClose())
		{
			*shouldExit = true;
		}
	}


	delete ab1;
	delete ab2;
	delete ab3;
	ab1 = nullptr;
	ab2 = nullptr;
	ab3 = nullptr;
	ab = nullptr;

	if (*shouldExit) return 0;
	if (confirm && sel >= 1 && sel <= 3) return 1;//sel;
	else return 0;
}

void CheckStartConditions(int argc, char** argv, bool* shouldExit)
{
	char** check = new char*[6];
	int* i = new int;
	*i = 0;
	*check = (char*)"start";
	if (argc > 1)
	{
		while (*i < 5)
		{
			if (argv[1][*i] != *check[*i]) (*i)++;
			else break;
		}
	}
	delete[] check;
	check = nullptr;
	if (*i != 5) *shouldExit = true;
	delete i;
	i = nullptr;
}

int StartMenu(Info** i, int* sel)
{
	static Vector2 mPos;
	mPos = GetMousePosition();
	BeginDrawing();
	if (IsKeyPressed(KEY_DOWN) && *sel < 3)
		(*sel)++;
	if (IsKeyPressed(KEY_UP) && *sel > 1)
		(*sel)--;
	if (mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
		&& mPos.y >= HEIGHT / 2 - 200 && mPos.y <= HEIGHT / 2 - 120) *sel = 1;
	if (mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
		&& mPos.y >= HEIGHT / 2 - 20 && mPos.y <= HEIGHT / 2 + 60) *sel = 2;
	if (mPos.x >= WIDTH / 2 - 150 && mPos.x <= WIDTH / 2 + 150
		&& mPos.y >= HEIGHT / 2 + 160 && mPos.y <= HEIGHT / 2 + 240) *sel = 3;
	switch (*sel)
	{
	case 1:
		DrawRectangle(WIDTH / 2 - 150, HEIGHT / 2 - 200, 300, 80, YELLOW);
		break;
	case 2:
		DrawRectangle(WIDTH / 2 - 150, HEIGHT / 2 - 20, 300, 80, YELLOW);
		break;
	case 3:
		DrawRectangle(WIDTH / 2 - 150, HEIGHT / 2 + 160, 300, 80, YELLOW);
		break;
	}

	DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 - 200, 300, 80, BLACK);
	DrawText("Start", WIDTH / 2 - 35, HEIGHT / 2 - 172, 24, BLACK);

	DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 - 20, 300, 80, BLACK);
	DrawText("Help", WIDTH / 2 - 20, HEIGHT / 2 + 8, 24, BLACK);

	DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 + 160, 300, 80, BLACK);
	DrawText("Exit", WIDTH / 2 - 20, HEIGHT / 2 + 188, 24, BLACK);

	DrawText(TextFormat("Username: %s", (*i)->username), 50, 50, 30, BLACK);

	DrawText("Made by Coltenus", WIDTH - 310, HEIGHT - 36, 34, BLACK);
	ClearBackground(SKYBLUE);
	EndDrawing();
	if ((IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && *sel == 1) return 4;
	else if ((IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && *sel == 2) return 5;
	else if ((IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && *sel == 3) return 6;
	else return 0;
}

int HelpMenu()
{
	BeginDrawing();
	DrawText("At first you have to choose one of there different characters.", WIDTH / 2 - 500, HEIGHT / 2 - 200, 30, BLACK);
	DrawText("Then each next room generate randomly.", WIDTH / 2 - 500, HEIGHT / 2 - 160, 30, BLACK);
	DrawText("Each enemy has two different attacks and one special action.", WIDTH / 2 - 500, HEIGHT / 2 - 120, 30, BLACK);
	DrawText("Strength of enemy depends on number of room you reached", WIDTH / 2 - 500, HEIGHT / 2 - 80, 30, BLACK);
	DrawText("Every boss located at each 15th room. At the first boss is the last.", WIDTH / 2 - 500, HEIGHT / 2 - 40, 30, BLACK);
	DrawText("You have to beat him to finish the game.", WIDTH / 2 - 500, HEIGHT / 2, 30, BLACK);
	DrawText("Press X to return", WIDTH / 2 - 120, HEIGHT / 2 + 150, 30, RED);
	ClearBackground(GREEN);
	EndDrawing();
	if (IsKeyPressed(KEY_X)) return 0;
	else if (WindowShouldClose()) return 6;
	else return 5;
}
