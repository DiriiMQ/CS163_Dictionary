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
    Rectangle textBox = { 100, 140, 700, 60 };
    Rectangle Find = { 100,140,50,50 };
    //Button_Coordinate
    Rectangle Description = { 100,250,700,400 };
    Rectangle Edit = { 650,600,100,40 };
    Rectangle SwitchDataSet = { 920,160,130,40 };
    Rectangle Quiz = { 1110,160,130,50 };
    Rectangle SearchWord = { 920,295,350,50 };
    Rectangle SearchDef = { 920,360,350,50 };
    Rectangle Favourite = { 920,425,350,50 };
    Rectangle RemoveWord = { 920,490,350,50 };
    Rectangle AddWord = { 920,565,350,50 };
    Rectangle ResetDict = { 1100,690,230,50 };
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