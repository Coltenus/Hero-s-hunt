//
// Created by colte on 02.01.2023.
//

#include "DeadScreen.h"

DeadScreen::DeadScreen(Hero **h, short rc) : GameplayEvent(h, rc), active(true) {

}

void DeadScreen::Update() {
    if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        active = false;
}

void DeadScreen::Draw() {
    BeginDrawing();

    DrawText("You're dead!", WIDTH/2 - 80, HEIGHT/2 - 100, 40, RED);
    DrawText(TextFormat("You have passed %d rooms", roomCount), WIDTH/2 - 150, HEIGHT/2, 30, LIGHTGRAY);

    ClearBackground(BLACK);
    EndDrawing();
}

bool DeadScreen::IsDone() {
    return !active;
}
