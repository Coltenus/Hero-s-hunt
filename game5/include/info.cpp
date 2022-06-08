#include "info.h"
#include "raylib.hpp"

bool OpenInfo(Info* i, Save** sv, double* st)
{
	static bool fl;
	fl = true;
	while (!IsKeyPressed(KEY_X))
	{
		if (GetTime() - *st >= 60)
		{
			*st = GetTime();
			(*sv)->minutes++;
			if ((*sv)->minutes == 60) (*sv)->hours++;
			if ((*sv)->hours == 24) (*sv)->days++;
		}
		BeginDrawing();
		DrawText(TextFormat("\t\t\t\t\t\t\t\t\t\t\t\t\tTime in game:\n%d day(s) %d hour(s) %d minute(s) %-4.2lf second(s)"
			, (*sv)->days, (*sv)->hours, (*sv)->minutes, GetTime() - *st)
			, WIDTH / 2 - 320, HEIGHT / 2, 30, BLACK);
		DrawText(TextFormat("Save %d", (*sv)->order), WIDTH / 2 - 50, HEIGHT / 2 - 100, 30, BLACK);
		DrawText(TextFormat("Username: %s", i->username), WIDTH / 2 - 150, HEIGHT / 2 - 200, 30, BLACK);
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