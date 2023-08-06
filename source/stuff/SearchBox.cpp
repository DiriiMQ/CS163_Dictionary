//
// Created by dirii on 5/8/23.
//

#include "SearchBox.h"

SearchBox::SearchBox(int fontSize, Rectangle position) {
    this->text = this->rawText = "";
    this->fontSize = fontSize;
    this->position = position;
    this->frameCount = 0;
    this->textureBlank = LoadTextureFromImage(LoadImage(Constants::Directories::DMQ::Blank));
    this->isActivated = this->isFlicked = false;

    this->font = LoadFont(Constants::Screen::FONT);
}

void SearchBox::draw() {
//    DrawTexture(this->textureBlank, this->position.x, this->position.y, WHITE);
    std::cout << "LOG: Text: " << this->text << '\n';
    DrawTextEx(this->font,
               this->text.c_str(),
               {this->position.x + 55, this->position.y + 20},
               this->fontSize,
               0,
               BLACK);
}

void SearchBox::handleEvents() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), this->position)) {
            this->isActivated = true;
        } else {
            this->isActivated = false;
        }
    }

    if (this->isActivated) {
        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (this->rawText.length() > 0) {
                this->rawText.pop_back();
            }
        } else if (IsKeyPressed(KEY_ENTER)) {
            this->isActivated = false;
        } else {
            if (this->rawText.length() < MAX_LENGTH) {
                auto c = (char)GetCharPressed();
                if (c != '\0')
                    this->rawText += c;
            }
        }
    }
}

void SearchBox::update() {
    this->updateText();

    if (++frameCount >= Constants::Screen::FRAMES_PER_SECOND / 2) {
        frameCount = 0;
        if (this->isActivated)
            this->isFlicked = !this->isFlicked;
    }

    if (this->isFlicked) {
        this->text += '|';
    }
}

void SearchBox::reset() {
    this->text = this->rawText = "";
    this->isActivated = this->isFlicked = false;
    this->frameCount = 0;
}

void SearchBox::updateText() {
    this->text = this->rawText.substr(std::max((int)this->rawText.length() - MAX_VISIBLE, 0), MAX_VISIBLE);
}
