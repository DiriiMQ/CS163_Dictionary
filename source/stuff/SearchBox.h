//
// Created by dirii on 5/8/23.
//

#ifndef CS163_GROUP9_SEARCHBOX_H
#define CS163_GROUP9_SEARCHBOX_H

#include "raylib.h"
#include "raygui.h"
#include "SuggestionLine.h"
#include "Constants.h"

#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

class SearchBox {
private:
    static constexpr int MAX_LENGTH = 256;
    static constexpr int MAX_VISIBLE = 36;
    static constexpr int MAX_SUGGESTIONS = 10;

    Texture textureBlank;
    Rectangle position;

    int fontSize, frameCount;
    Font* font;
    std::string text, rawText;

    SuggestionLine test;

    // original suggest rectangle
    Rectangle rectangleSuggest;
    int currentId = 0;
    std::vector<SuggestionLine> suggestList;
    std::vector<std::pair<std::string, std::string>> suggestListText;

    bool isActivated, isFlicked;

public:
    SearchBox() = default;
    SearchBox(int fontSize, Rectangle position, Font* font);

    void draw();
    void handleEvents();
    void update();

    void updateText();

    void setList(std::vector<std::pair<std::string, std::string>> list);

    void reset();
};


#endif //CS163_GROUP9_SEARCHBOX_H
