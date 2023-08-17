//
// Created by dirii on 8/8/23.
//

#include "SuggestionLine.h"

SuggestionLine::SuggestionLine(std::string text, std::string def, Font *font, Rectangle rec) {
    this->text = std::move(text);
    this->definition = std::move(def);
    this->font = font;
    this->rectangle = rec;
    this->fontSize = 20;
    this->isActivated = false;
    this->textDraw = "";

    this->button = Button(
            "",
            1,
            WHITE,
            this->rectangle
            );
    this->button.setIsSuggest();
}

void SuggestionLine::draw() {
    this->button.draw();
    DrawTextEx(*this->font,
               this->textDraw.c_str(),
               {this->rectangle.x + 55, this->rectangle.y + 6},
               this->fontSize,
               1,
               BLACK);
}

void SuggestionLine::handleEvents() {
    this->isClicked = false;
    this->button.handleEvents();

    if (this->button.isPressing()) {
//        std::cout << "LOG: Clicked\n";
        this->isClicked = true;
    }
}

void SuggestionLine::update() {
    if (this->definition.length() > 0)
        this->textDraw = this->text + " || " + this->definition;
    else 
        this->textDraw = this->text;
    this->button.update();
}

void SuggestionLine::setText(std::string _text) {
    this->text = std::move(_text);
}

void SuggestionLine::setDefinition(std::string def) {
    this->definition = std::move(def);
}

bool SuggestionLine::getClicked() const {
    return this->isClicked;
}
