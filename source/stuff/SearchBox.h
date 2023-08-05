//
// Created by dirii on 5/8/23.
//

#ifndef CS163_GROUP9_SEARCHBOX_H
#define CS163_GROUP9_SEARCHBOX_H

#include "raylib.h"
#include "raygui.h"

#include <string>

class SearchBox {
private:
    std::string text, rawText;
    int fontSize;

    std::string imgPath;
    Rectangle rectangle;

public:
    SearchBox() = default;
    SearchBox(std::string text, int fontSize, std::string imgPath, Rectangle rectangle);

    void draw();
    void handleEvents();
    void update();
};


#endif //CS163_GROUP9_SEARCHBOX_H
