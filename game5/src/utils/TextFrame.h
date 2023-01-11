//
// Created by colte on 11.01.2023.
//

#ifndef GAME5_TEXTFRAME_H
#define GAME5_TEXTFRAME_H

#include <string>
#include <vector>
#include <raylib.h>
#define PADDING_X 5
#define PADDING_Y 5

class TextFrame {
private:
    std::vector<std::string> text;
    Vector2 pos, size;
    short fontHeight, maxLength, maxRowCount, fElement, rowCount;
    bool lineNeeded;

public:
    TextFrame(const char*, Vector2, Vector2, short, bool);
    TextFrame(std::string, Vector2, Vector2, short, bool);
    ~TextFrame() = default;
    void Show();
    void Update();
};


#endif //GAME5_TEXTFRAME_H
