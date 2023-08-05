//
// Created by dirii on 5/8/23.
//

#ifndef CS163_GROUP9_SEARCHBOX_H
#define CS163_GROUP9_SEARCHBOX_H

#include "raylib.h"
#include "raygui.h"
#include "Constants.h"
#include <string>

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
    bool mouseonText();
    bool isClicked();
    bool islessthan35();
    //List
    void List(int num);
    void UpdtList(int num);
   
};


#endif //CS163_GROUP9_SEARCHBOX_H
