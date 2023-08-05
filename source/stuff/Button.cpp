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
}

void Button::draw() {

}

void Button::handleEvents() {

}

void Button::update() {

}

bool Button::isClicked() {
    return false;
}
