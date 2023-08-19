//
// Created by dirii on 15/8/23.
//

#ifndef CS163_GROUP9_FAVORITE_H
#define CS163_GROUP9_FAVORITE_H
#include "raylib.h"
#include "raygui.h"
#include "stuff/Constants.h"
#include "stuff/Utils.h"
#include "stuff/Button.h"
#include <vector>
#include "stuff/Constants.h"
#include "core/Api.h"
#include "stuff/Utils.h"

class Favourite {
private:
    static constexpr int MAX_LENGTH = 810;
    int MAX_SUGGESTIONS = 9;
    std::vector <bool> index_unFavourite;
    Rectangle position;
    int currentMouse, currentClick;
    int fontSize, frameCount;
    Font* font;
    // Change by struct Favourite
    int mouse;
    int size;
    static constexpr int SPACING = 1;
    std::vector<std::wstring> FavouriteList;
    int tmpmode;
    vector <ButtonImage> Starr;
    Api* api;
    ButtonImage form;

public:
    Favourite() = default;
    Favourite(Font* font, int tmpmode, Api* api); //add api* api parameter
    void draw();
    void handleEvents();
    void update();

    void removeWhenSave();
    void reset();
    int getClicked();
};

#endif //CS163_GROUP9_FAVORITE_H
