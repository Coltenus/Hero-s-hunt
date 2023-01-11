//
// Created by colte on 11.01.2023.
//

#include "RadioButton.h"
#include "../common.h"
#include <cmath>

RadioButton::RadioButton(const char* t, Vector2 p, Vector2 s, short fontH, bool st)
: state(st), pos(p), size(s), fontHeight(fontH), text(t)
{
    radius = (size.y - 2*PADDING_RB_Y)/4;
}

RadioButton::RadioButton(std::string t, Vector2 p, Vector2 s, short fontH, bool st)
: state(st), pos(p), size(s), fontHeight(fontH), text(t)
{
    radius = (size.y - 2*PADDING_RB_Y)/4;
}

void RadioButton::Show() {
    DrawCircleV({pos.x + PADDING_RB_X + radius, pos.y + PADDING_RB_Y + radius},
                radius, WHITE);
    DrawText(text.c_str(), pos.x + PADDING_RB_X + 2*radius + PADDING_RB_BL,
             pos.y + PADDING_RB_Y + size.y*0.1f,
             fontHeight,TEXT_COLOR);
    if(state)
        DrawCircleV({pos.x + PADDING_RB_X + radius, pos.y + PADDING_RB_Y + radius},
                    radius/2, BLACK);
}

void RadioButton::Click(short& buffer) {
    static Vector2 mouse;
    mouse = GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
    && pow(mouse.x - (pos.x + PADDING_RB_X + radius), 2)
    + pow(mouse.y - (pos.y + PADDING_RB_Y + radius), 2) <= pow(radius, 2))
    {
        buffer = value;
    }
}

void RadioButton::SetValue(short val) {
    value = val;
}

void RadioButton::SetState(bool st) {
    state = st;
}
