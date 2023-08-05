//
// Created by dirii on 27/7/23.
//

#ifndef CS163_GROUP9_WINDOW_H
#define CS163_GROUP9_WINDOW_H

#include "raylib.h"
#include "raygui.h"
#include "stuff/Constants.h"
#include "stuff/Utils.h"

class Window {
private:
//    Font font;
    char text[256] = "";

    void drawHandleEvents();
    void update();

public:
    Window();

    void run();
};

#endif //CS163_GROUP9_WINDOW_H
