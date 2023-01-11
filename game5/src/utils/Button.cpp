//
// Created by Coltenus on 23.11.2022.
//

#include "Button.h"
#include <thread>

Button::Button(Vector2 p, Vector2 s, const char * t, int h, Color c, bool il) : pos(p),
size(s), text(t), height(h), col(c), textCol(WHITE), isLines(il), value(0), active(true), pressOnce(false) {}

Button::Button(Vector2 p, Vector2 s, const char * t, int h, Color c, bool il, Color tc) : pos(p),
size(s), text(t), height(h), col(c), textCol(tc), isLines(il), value(0), active(true), pressOnce(false) {}

Button::~Button() {
}

void Button::Show() {
    static Vector2 mouse;
    mouse = GetMousePosition();
    if(isLines)
    {
        if(!active) DrawRectangleV(pos, size, DARKGRAY);
        else if(active && mouse.x >= pos.x && mouse.x <= pos.x + size.x
                && mouse.y >= pos.y && mouse.y <= pos.y + size.y)
            DrawRectangleV(pos, size, col);
        DrawRectangleLines(pos.x, pos.y, size.x, size.y, col);
    }
    else if(active) DrawRectangleV(pos, size, col);
    else DrawRectangleV(pos, size, DARKGRAY);
    DrawText(text.c_str(), pos.x + size.x/16, pos.y + size.y/2 - height/2, height, textCol);
}

void Button::SetText(const char *t) {
    text = t;
}

void Button::SetText(std::string &t) {
    text = t;
}

void Button::SetValue(short v) {
    value = v;
}

short Button::operator()() {
    return value;
}

void Button::Click(short &buffer) {
    static Vector2 mouse;
    mouse = GetMousePosition();
    if(active && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
    && mouse.x >= pos.x && mouse.x <= pos.x + size.x
       && mouse.y >= pos.y && mouse.y <= pos.y + size.y)
    {
        buffer = value;
        if(pressOnce) active = false;
    }
}

void Button::SetStatus(bool st) {
    active = st;
}

void Button::SetOnceStatus(bool st) {
    pressOnce = st;
    if(!pressOnce) {
        active = true;
    }
}

void Button::SetTextColor(Color c) {
    textCol = c;
}
