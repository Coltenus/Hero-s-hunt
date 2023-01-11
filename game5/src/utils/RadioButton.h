//
// Created by colte on 11.01.2023.
//

#ifndef GAME5_RADIOBUTTON_H
#define GAME5_RADIOBUTTON_H

#include <raylib.h>
#include <string>

#define PADDING_RB_X 2
#define PADDING_RB_Y 2
#define PADDING_RB_BL 20
#define PADDING_RB_BB 10

class RadioButton {
private:
    bool state;
    short value;
    Vector2 pos, size;
    short fontHeight, radius;
    std::string text;

public:
    RadioButton(const char*, Vector2, Vector2, short, bool);
    RadioButton(std::string, Vector2, Vector2, short, bool);
    void Show();
    void Click(short&);
    void SetValue(short);
    void SetState(bool);
};


#endif //GAME5_RADIOBUTTON_H
