#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <raylib.hpp>
#include <time.h>
using namespace std;

#include "characters.h"
#include "chooseRoom.h"

bool OpenInfo(Info**, Save**, double*, int);
void FillFile();
void EnterUsername(Info**, bool*);
int SelectionMenu(Info**, int*);
void GameProcess(Info**, int, bool*, bool (*)(Info**, Save**, double*, int), short (*)(short*, bool*));
short SelectHero(short*, bool*);

int main()
{
	srand((unsigned)time(NULL));
	int curSave = 0;
	int sel = 0;
	double st = -1;
	bool shouldExit = false;
	Info *inf;
	FILE* sv = fopen("info", "rb");
	if (sv == NULL)
	{
		FillFile();
		sv = fopen("info", "rb");
	}
	inf = new Info;
	fread(inf, sizeof(Info), 1, sv);
	fclose(sv);
	InitWindow(WIDTH, HEIGHT, "Game 4");
	if (inf->username[2] == '\0') EnterUsername(&inf, &shouldExit);
	while (!IsKeyPressed(KEY_ENTER) && !shouldExit)
	{
		BeginDrawing();
		DrawText("Press Enter to continue", WIDTH / 2 - 175, HEIGHT / 2 - 200, 30, BLACK);
		ClearBackground(WHITE);
		EndDrawing();
		if (WindowShouldClose()) shouldExit = true;
	}
	while (!WindowShouldClose() && !shouldExit)
	{
		switch (curSave)
		{
		case 0:
			curSave = SelectionMenu(&inf, &sel);
			break;
		case 1:
			GameProcess(&inf, 1, &shouldExit, OpenInfo, SelectHero);
			shouldExit = false;
			curSave = 0;
			sel = 0;
			break;
		case 2:
			GameProcess(&inf, 2, &shouldExit, OpenInfo, SelectHero);
			shouldExit = false;
			curSave = 0;
			sel = 0;
			break;
		case 3:
			GameProcess(&inf, 3, &shouldExit,OpenInfo, SelectHero);
			shouldExit = false;
			curSave = 0;
			sel = 0;
			break;
		}
	}
	CloseWindow();
	if (inf != NULL)
	{
		sv = fopen("info", "rb+");
		if (sv != NULL)
		{
			fseek(sv, 0, SEEK_SET);
			fwrite(inf, sizeof(Info), 1, sv);
			fclose(sv);
		}
	}
	delete inf;
	inf = nullptr;
	return 0;
}

bool OpenInfo(Info** i, Save** save, double *st, int sv)
{
	static bool fl;
	fl = true;
	while (!IsKeyPressed(KEY_X) )
	{
		BeginDrawing();
		DrawText(TextFormat("\t\t\t\t\t\t\t\t\t\t\t\t\tTime in game:\n%d day(s) %d hour(s) %d minute(s) %-4.2lf second(s)"
			, (*save)->days, (*save)->hours, (*save)->minutes, GetTime() - *st)
			, WIDTH / 2 - 320, HEIGHT / 2, 30, BLACK);
		DrawText(TextFormat("Save %d", (*save)->order), WIDTH / 2 - 50, HEIGHT / 2 - 100, 30, BLACK);
		DrawText(TextFormat("Username: %s", (*i)->username), WIDTH / 2 - 150, HEIGHT / 2 - 200, 30, BLACK);
		DrawFPS(0, 0);
		ClearBackground(WHITE);
		EndDrawing();
		if (WindowShouldClose())
		{
			fl = false;
			return true;
		}
	}
	return false;
}

void FillFile()
{
	int i;
	FILE* f;
	Info* inf;
	inf = new Info;
	f = fopen("info", "wb");
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
			ClearBackground(WHITE);
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
	static char* buf;
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
	DrawText("Choose save file", WIDTH / 2 - 130, HEIGHT / 2 - 320, 30, BLACK);

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
	ClearBackground(WHITE);
	EndDrawing();
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && *sel >= 1 && *sel <= 3) return *sel;
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && *sel >= 4 && *sel <= 6)
	{
		
		buf = new char[6];
		buf[0] = 's';
		buf[1] = 'a';
		buf[2] = 'v';
		buf[3] = 'e';
		buf[4] = (char)*sel - 3 + 48;
		buf[5] = '\0';
		f = fopen(buf, "rb");
		if (f != NULL)
		{
			f = fopen(buf, "wb");
			save = new Save;
			save->minutes = 0;
			save->hours = 0;
			save->days = 0;
			save->gold = 0;
			save->order = *sel - 3;
			save->charact = 0;
			save->stats.dmgN = 0;
			save->stats.dmgH = 0;
			save->stats.evasion = 0;
			save->stats.hp = 0;
			save->stats.maxHP = 100;
			save->stats.spValue = 0;
			save->roomNum = 0;
			fwrite(save, sizeof(Save), 1, f);
			delete save;
			save = NULL;
			fclose(f);
		}
		delete[] buf;
		buf = nullptr;
	}
	if (IsKeyPressed(KEY_ENTER)) return *sel;
	else return 0;
}

void GameProcess(Info** i, int sv, bool* shouldExit, bool (*OpInf)(Info**, Save**, double*, int), short (*selH)(short*, bool*))
{
	static double st;
	static bool isReady;
	static Save* save;
	static FILE* f;
	static Hero* h;
	static Enemy* en;
	static short chooseH, room;
	char* buf = new char[6];
	buf[0] = 's';
	buf[1] = 'a';
	buf[2] = 'v';
	buf[3] = 'e';
	buf[4] = (char)sv + 48;
	buf[5] = '\0';
	isReady = true;
	chooseH = 0;
	save = new Save;
	h = NULL;
	f = fopen(buf, "rb");
	if (f == NULL)
	{
		f = fopen(buf, "wb");
		save->minutes = 0;
		save->hours = 0;
		save->days = 0;
		save->gold = 0;
		save->order = sv;
		save->charact = 0;
		save->stats.dmgN = 0;
		save->stats.dmgH = 0;
		save->stats.evasion = 0;
		save->stats.hp = 0;
		save->stats.maxHP = 100;
		save->stats.spValue = 0;
		save->roomNum = 0;
		fwrite(save, sizeof(Save), 1, f);
		delete save;
		save = nullptr;
		fclose(f);
		save = new Save;
		f = fopen(buf, "rb");
	}
	fread(save, sizeof(Save), 1, f);
	while (save->charact == 0 && !(*shouldExit))
	{
		save->charact = selH(&chooseH, shouldExit);
	}
	switch (save->charact)
	{
	case 1:
		h = new Warrior;
		break;
	case 2:
		//h = new Archer;
		break;
	case 3:
		//h = new Palladin;
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
		h->gold = save->gold;
	}
	fclose(f);
	while (!IsKeyPressed(KEY_ENTER) && !(*shouldExit))
	{
		BeginDrawing();
		DrawText("Press Enter to start", WIDTH / 2 - 175, HEIGHT / 2 - 200, 30, BLACK);
		ClearBackground(WHITE);
		EndDrawing();
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
		if (IsKeyPressed(KEY_I)) *shouldExit = OpInf(i, &save, &st, sv);
		if (isReady) isReady = NextRoom(&h, &save, &st, shouldExit, *i);
		else if(!(*shouldExit))
		{
			BeginDrawing();
			if(h->hp > 0) DrawText("You've won!", WIDTH / 2 - 100, HEIGHT / 2 - 150, 30, BLUE);
			else DrawText("You're dead...", WIDTH / 2 - 100, HEIGHT / 2 - 150, 30, RED);
			if (h->hp > 0) ClearBackground(WHITE);
			else ClearBackground(BLACK);
			EndDrawing();
		}
		if (WindowShouldClose()) *shouldExit = true;
	}
	f = fopen(buf, "rb+");
	if (h->hp <= 0 || save->roomNum == 10 && h->hp > 0)
	{
		save->minutes = 0;
		save->hours = 0;
		save->days = 0;
		save->gold = 0;
		save->charact = 0;
		save->stats.dmgN = 0;
		save->stats.dmgH = 0;
		save->stats.evasion = 0;
		save->stats.hp = 0;
		save->stats.maxHP = 100;
		save->stats.spValue = 0;
		save->roomNum = 0;
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
		save->gold = h->gold;
		if (shouldExit) save->roomNum--;
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
	DrawText("Choose Hero", WIDTH / 2 - 110, HEIGHT / 2 - 320, 30, BLACK);

	DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 - 200, 300, 80, BLACK);
	DrawText("Warrior", WIDTH / 2 - 40, HEIGHT / 2 - 172, 24, BLACK);

	DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 - 20, 300, 80, BLACK);
	DrawText("Archer", WIDTH / 2 - 40, HEIGHT / 2 + 8, 24, BLACK);

	DrawRectangleLines(WIDTH / 2 - 150, HEIGHT / 2 + 160, 300, 80, BLACK);
	DrawText("Palladin", WIDTH / 2 - 40, HEIGHT / 2 + 188, 24, BLACK);

	ClearBackground(WHITE);
	EndDrawing();
	if (WindowShouldClose())
	{
		*shouldExit = true;
		return 0;
	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && *sel >= 1 && *sel <= 3) return *sel;
	if (IsKeyPressed(KEY_ENTER)) return *sel;
	else return 0;
}