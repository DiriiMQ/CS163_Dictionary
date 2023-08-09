//
// Created by dirii on 8/8/23.
//

#ifndef CS163_GROUP9_SUGGESTIONLINE_H
#define CS163_GROUP9_SUGGESTIONLINE_H

#include "raylib.h"
#include "raygui.h"
#include "Button.h"

#include <string>

class SuggestionLine {
private:
    static const int MAX_LENGTH = 256;
//    Vector2 position;
    Rectangle rectangle;
    Button button;

    int fontSize;
    Font* font;
    std::string text, definition, textDraw;

    bool isActivated, isClicked = false;

public:
    SuggestionLine() = default;
    SuggestionLine(std::string text, std::string def, Font* font, Rectangle rec);

    void draw();
    void handleEvents();
    void update();

    void setText(std::string text);
    void setDefinition(std::string def);

    [[nodiscard]] bool getClicked() const;
};


#endif //CS163_GROUP9_SUGGESTIONLINE_H
