//
// Created by dirii on 5/8/23.
//

#include "Button.h"

#include <utility>

Button::Button(std::string text, int fontSize, Color color, Rectangle rectangle) {
    this->text = std::move(text);
    this->fontSize = fontSize;
    this->color = color;
    this->rectangle = rectangle;
    this->colorBG = WHITE;

    // Calculate text width and height
    float textWidth = MeasureText(this->text.c_str(), fontSize);
    float textHeight = fontSize; // Assuming font size is 20, you can change this accordingly

    // Calculate the position to center the text in the rectangle
    float posX = rectangle.x + (rectangle.width - textWidth) / 2.0;
    float posY = rectangle.y + (rectangle.height - textHeight) / 2.0;

    this->positionText = {posX, posY};
}

void Button::draw() {
    DrawRectangleRoundedLines(
            {
                this->rectangle.x + 1,
                this->rectangle.y + 1,
                this->rectangle.width - 2,
                this->rectangle.height - 2
                },
            CORNER_RADIUS,
            DPI,
            3,
            this->color
            );

    DrawRectangleRounded(
            this->rectangle,
            CORNER_RADIUS,
            DPI,
            this->colorBG
            );

    DrawText(
            this->text.c_str(),
            this->positionText.x,
            this->positionText.y,
            this->fontSize,
            this->color
            );
}

void Button::handleEvents() {
    this->clicked = false;
    this->colorBG = TRANSPARENT;

    if (CheckCollisionPointRec(GetMousePosition(), this->rectangle)) {
        this->colorBG = LIGHTGRAY;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            this->pressing = true;
            this->colorBG = GRAY;
        } else if (this->pressing) {
            this->pressing = false;
            this->clicked = true;
        }
    } else {
        this->colorBG = TRANSPARENT;
    }
}

void Button::update() {
    if (this->isChosen)
        this->colorBG = GRAY;
}

bool Button::isClicked() const {
    return this->clicked;
}

void Button::setChosen(bool _isChosen) {
    this->isChosen = _isChosen;
}
