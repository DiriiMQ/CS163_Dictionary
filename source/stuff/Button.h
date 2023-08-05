//
// Created by dirii on 5/8/23.
//

#ifndef CS163_GROUP9_BUTTON_H
#define CS163_GROUP9_BUTTON_H

#include "raylib.h"
#include "raygui.h"

#include <string>

class Button {
private:
    std::string text;
    int fontSize;

    Color color, colorBG;
    Rectangle rectangle;

public:
    Button() = default;
    Button(std::string text, int fontSize, Color color, Rectangle rectangle);

    void draw();
    void handleEvents();
    void update();

    bool isClicked();
};


#endif //CS163_GROUP9_BUTTON_H
