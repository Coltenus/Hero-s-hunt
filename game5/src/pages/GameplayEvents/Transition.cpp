//
// Created by colte on 31.12.2022.
//

#include "Transition.h"

Transition::Transition(Hero **h, short rc) : GameplayEvent(h, rc), active(true) {

}

void Transition::Update() {
    if(IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        active = false;
}

void Transition::Draw() {
    BeginDrawing();
    DrawTexture(background, 0, 0, GRAY);

    DrawText(TextFormat("Room %d", roomCount), WIDTH/2 - 60, HEIGHT/2 - 100, 40, textCol);

    ClearBackground(WHITE);
    EndDrawing();
}

bool Transition::IsDone() {
    return !active;
}


