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

class SearchBox {
private:
    static const int MAX_LENGTH = 256;

    std::string text, rawText;
    int fontSize;
    std::string imgPath;
    Rectangle rectangle;
    int framecount;
    Image blank;
    Texture texture;
    int mouse;
    int currentClick;
    int currentMouse;
public:
    SearchBox() = default;
    SearchBox( int fontSize, Rectangle rectangle);

    void draw();
    void handleEvents();
    void update();
    bool mouseOnText();
    bool isClicked();
    bool isLessThan35();
    //List
    void list(int num);
    void updateList(int num);
   
};


#endif //CS163_GROUP9_SEARCHBOX_H
