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
    static const int MAX_LENGTH = 256;

    std::string text, rawText;
    int fontSize;
    std::string imgPath;
    Rectangle rectangle;
    int framecount;

public:
    SearchBox() = default;
    SearchBox( int fontSize, Rectangle rectangle);

    void draw();
    void handleEvents();
    void update();
    bool mouseonText();
    bool isClicked();
    bool islessthan35();
   // int isCluck();
};


#endif //CS163_GROUP9_SEARCHBOX_H
