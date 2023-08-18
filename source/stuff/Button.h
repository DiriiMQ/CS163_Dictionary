//
// Created by dirii on 5/8/23.
//

#ifndef CS163_GROUP9_BUTTON_H
#define CS163_GROUP9_BUTTON_H

#include "raylib.h"
#include "raygui.h"
#include "Constants.h"
#include <vector>
#include <string>
#include <iostream>
#include <vector>

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

class ButtonImage
{
private:
    static constexpr int DPI = 500;
    static constexpr float CORNER_RADIUS = 0.3;

    std::vector <std::string> path;
    std::vector <std::string> pathPress;

    int numpath;
    int tmpPath;

    Rectangle rectangle;
    Color color;

    bool isSuggest = false;
    bool pressing = false, clicked = false;

    std::vector <Texture> texture;
    std::vector <Texture> texturePress;

public:
    ButtonImage(std::vector <std::string> path, std::vector <std::string> pathPress, Rectangle rectangle);
    ButtonImage() = default;
    void draw();
    void handleEvents();
    void update();
    void changeIndex(int newindex);
    void changePosition(Rectangle change);
    [[nodiscard]] bool isClicked() const;
    [[nodiscard]] bool isPressing() const;
    int getClicked();
};



#endif //CS163_GROUP9_BUTTON_H
