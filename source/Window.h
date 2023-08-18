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
#include "core/Api.h"
#include <draw/Favorite.h>

class Window {
private:
    static constexpr float CORNER_RADIUS = 0.1f;
    string REMOVE_NOTICE = "This word has been removed!";

    // FOR TESTING
//    std::string testLarge;
    std::vector<std::string> testLines;
    // END TESTING

    Api *api;
    Font font;
    Texture background;
    Rectangle mainInfoBG;
    Button menuButtons[3],
            operationButtons[3],
            saveButton,
            resetButton;
    int activeMenu, activeOperation;

    // For Quiz & Type of Dict
    bool isQuizActived = false;
    Constants::TypeDict currentDict = Constants::TypeDict::EN_VI;
    ButtonImage DataSwitchButton, QuizButton;


    // For Add
    std::string wordAdd, definitionAdd;

    // For Search and Edit
    bool isShowingWord = false;
    Word currentWord;
    std::vector<std::pair<std::string, bool>> lines;
    SearchBox searchBox;
    std::string currentSearch;
    std::vector<std::wstring> _wordList;
    std::vector<std::pair<std::string, std::string>> suggestListText;
    FrameBoard frameBoard;

    // For Favourite
    Favourite favourite;

    //Button_Coordinate
     //Box and Des
    Rectangle Star = { 792.1 ,276.6 ,47.5 ,45.2 };
    Rectangle Find = { 110,170.7,30.2,30.2 };
    Rectangle textBox = { 92.5, 155.3, 690.7, 66.1 };
    Rectangle Description = { 47,259,810,420 };
    //Option 
    Rectangle SwitchDataSet = { 920,160,150,40 };
    Rectangle Quiz = { 1114.1,160,240.4,56 };

public:
    Window(Api *api);
    void init();

    // main
    void draw();
    void handleEvents();
    void update();

    void updateOperationButtons();
    void updateModeNonFavorite();

    void createLines();

    void saveFrameBoard();

    void reset();

    void run();
};

#endif //CS163_GROUP9_WINDOW_H