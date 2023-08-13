//
// Created by dirii on 13/8/23.
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
class Favourite {
private:
    static constexpr int MAX_LENGTH = 810;
    static constexpr int MAX_SUGGESTIONS = 9;
    std::vector <bool> index_un;
    Rectangle position;
    int currentMouse, currentClick;
    int fontSize, frameCount;
     Font* font;
     // Change by struct Favourite
    int mouse;
    int size;
    /*  std::vector<SuggestionLine> suggestList;
      std::vector<std::pair<std::string, std::string>> suggestListText;*/

    ButtonImage Starr[20];

public:

  Favourite(Font* font);
    // Favourite(Font* font);
    void draw();
    void handleEvents();
    void update();

    void reset();
    int getClicked();
};


#endif //CS163_GROUP9_FAVORITE_H
