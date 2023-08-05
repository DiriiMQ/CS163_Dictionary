//
// Created by dirii on 5/8/23.
//

#ifndef CS163_GROUP9_BASESCENE_H
#define CS163_GROUP9_BASESCENE_H

#include "raylib.h"
#include "raygui.h"

class BaseScene {
public:
    virtual void drawHandleEvents() = 0;
    virtual void update() = 0;
};


#endif //CS163_GROUP9_BASESCENE_H
