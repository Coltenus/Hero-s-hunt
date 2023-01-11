//
// Created by Coltenus on 23.11.2022.
//

#ifndef GAME5_BUTTON_H
#define GAME5_BUTTON_H

#include <raylib.h>
#include <vector>
#include <string>
#include "../common.h"

class Button {
private:
    Vector2 pos;
    Vector2 size;
    std::string text;
    int height;
    Color col, textCol;
    bool isLines;
    short value;
    bool active, pressOnce;

public:
    Button(Vector2, Vector2, const char*, int, Color, bool);
    Button(Vector2, Vector2, const char*, int, Color, bool, Color);
    ~Button();
    void Show();
    void SetText(const char*);
    void SetText(std::string&);
    void SetValue(short);
    short operator()();
    void Click(short&);
    void SetStatus(bool);
    void SetOnceStatus(bool);
    void SetTextColor(Color);
};

#endif //GAME5_BUTTON_H
