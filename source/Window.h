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
    char text[256] = "";
    //button parameter
    //text box 
    char name[256 + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;
    int MAX_INPUT_CHARS = 256;
    bool mouseOnText = false;
    int framesCounter = 0;
    bool tmp = 0;
    char ot[35 + 1];                // Text box only print 35 chars
    int currentclick = -1;
    //Button_Coordinate
     //Box and Des
    Rectangle Star = { 721.3 ,278.4 ,47.5 ,45.2 };
    Rectangle Find = { 110,170.7,30.2,30.2 };
    Rectangle textBox = { 92.5, 155.3, 690.7, 66.1 };
    Rectangle Description = { 92.5,259,690.7,399.3 };
    //Option 
    Rectangle SwitchDataSet = { 920,160,150,40 };
    Rectangle Quiz = { 1110,160,130,50 };
    // Search Group
    Rectangle SearchWord = { 926,345.3,337.5,54.4 };
    Rectangle SearchDef = { 926,431.9,337.5,54.4 };
    Rectangle Favourite = { 926,517.5,337.5,54.4 };
    //Change Struct
    Rectangle Edit = { 636.3,591.2,113.7,44.3 };
    Rectangle RemoveWord = { 343.3,591.2,135.6,44.3 };
    Rectangle AddWord = { 512.7,591.2,89.8,44.3 };
    Rectangle ResetDict = { 1096.9,678.5,230.4,63.3 };
    //update function
    void handleEvents();
    void update();
    void updateTextbox();
    //draw function
    void draw(int& currentclick);
    void drawTextbox(Rectangle textBox);
    void drawline();
    void drawBackGround();
    //unload function
   

public:
    Window();
    void menu();
    void run();
    
};

#endif //CS163_GROUP9_WINDOW_H