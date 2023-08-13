//
// Created by dirii on 27/7/23.
//

#ifndef CS163_GROUP9_WINDOW_H
#define CS163_GROUP9_WINDOW_H

#include "raylib.h"
#include "raygui.h"
#include "stuff/Constants.h"
#include "stuff/Utils.h"
#include "stuff/Button.h"
#include "stuff/SearchBox.h"
#include "stuff/FrameBoard.h"

class Window {
private:
    static constexpr float CORNER_RADIUS = 0.1f;

    // FOR TESTING
//    std::string testLarge;
    std::vector<std::string> testLines;
    // END TESTING

    Font font;
    Texture background;
    Rectangle mainInfoBG;
    Button menuButtons[3],
            operationButtons[3],
            resetButton;
    int activeMenu, activeOperation;


    Button test;
    SearchBox searchBox;
    FrameBoard frameBoard;
    //Button_Coordinate
     //Box and Des
    Rectangle Star = { 792.1 ,276.6 ,47.5 ,45.2 };
    Rectangle Find = { 110,170.7,30.2,30.2 };
    Rectangle textBox = { 92.5, 155.3, 690.7, 66.1 };
    Rectangle Description = { 47,259,810,420 };
    //Option 
    Rectangle SwitchDataSet = { 920,160,150,40 };
    Rectangle Quiz = { 1110,160,130,50 };

    //update function
//    void updateTextbox();
    //draw function
//    void drawTextbox(Rectangle textBox);

public:
    Window();
    void init();

    // main
    void draw();
    void handleEvents();
    void update();

    void reset();

//    void menu();
    void run();
};

#endif //CS163_GROUP9_WINDOW_H