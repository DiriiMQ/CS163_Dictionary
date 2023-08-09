//
// Created by dirii on 5/8/23.
//

#ifndef CS163_GROUP9_BUTTON_H
#define CS163_GROUP9_BUTTON_H

#include "raylib.h"
#include "raygui.h"
#include "Constants.h"

#include <string>
#include <iostream>

class Button {
private:
    static constexpr int DPI = 500;
    static constexpr float CORNER_RADIUS = 0.3;

    std::string text;
    Vector2 positionText;
    int fontSize;

    Color color, colorBG;
    Rectangle rectangle;

    bool isSuggest = false;
    bool pressing = false, clicked = false, isChosen = false;

public:
    Button() = default;
    Button(std::string text, int fontSize, Color color, Rectangle rectangle);

    void draw();
    void handleEvents();
    void update();

    [[nodiscard]] bool isClicked() const;
    [[nodiscard]] bool isPressing() const;

    void setChosen(bool isChosen);
    void setIsSuggest();
};


#endif //CS163_GROUP9_BUTTON_H
