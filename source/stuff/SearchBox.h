//
// Created by dirii on 5/8/23.
//

#ifndef CS163_GROUP9_SEARCHBOX_H
#define CS163_GROUP9_SEARCHBOX_H

#include "raylib.h"
#include "raygui.h"
#include "Constants.h"

#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>

class SearchBox {
private:
    static const int MAX_LENGTH = 256;
    static const int MAX_VISIBLE = 36;

    Texture textureBlank;
    Rectangle position;

    int fontSize, frameCount;
    Font font;
    std::string text, rawText;

    bool isActivated, isFlicked;

public:
    SearchBox() = default;
    SearchBox(int fontSize, Rectangle position);

    void draw();
    void handleEvents();
    void update();

    void updateText();

    void reset();
};


#endif //CS163_GROUP9_SEARCHBOX_H
