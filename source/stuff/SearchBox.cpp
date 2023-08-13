//
// Created by dirii on 5/8/23.
//

#include "SearchBox.h"

SearchBox::SearchBox(int fontSize, Rectangle position, Font* font) {
    this->text = this->rawText = "";
    this->fontSize = fontSize;
    this->position = position;
    this->frameCount = 0;
    this->textureBlank = LoadTextureFromImage(LoadImage(Constants::Directories::DMQ::Blank));
    this->isActivated = this->isFlicked = false;
    this->font = font;

    this->rectangleSuggest = {
            this->position.x + 10,
            this->position.y + 65,
            static_cast<float>(this->textureBlank.width) - 20,
            static_cast<float>(textureBlank.height / 2.0)
    };
}

void SearchBox::draw() {
    DrawTextEx(*this->font,
               this->text.c_str(),
               {this->position.x + 55, this->position.y + 20},
               this->fontSize,
               1,
               BLACK);

    if (this->isActivated) {
//        this->test.draw();
        for (auto &i : this->suggestList) {
            i.draw();
        }
    }
}

void SearchBox::handleEvents() {
    if (this->isActivated) {
        if (GetMouseWheelMove() < 0) {
            if (this->currentId + 1 <= this->suggestListText.size() - MAX_SUGGESTIONS) {
                this->currentId++;
            }
        }
        if (GetMouseWheelMove() > 0) {
            if (this->currentId - 1 >= 0) {
                this->currentId--;
            }
        }

        for (auto &i : this->suggestList) {
            i.handleEvents();
        }

        for (int i = 0; i < this->suggestList.size(); i++) {
            if (this->suggestList[i].getClicked()) {
//                std::cout << "LOG: SearchBox: Option " << i + this->currentId <<  " is clicked\n";
                this->choseId = i + this->currentId;
                break;
            }
        }
    }

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
                int prevCodepointSize = 0;
                GetCodepointPrevious(this->rawText.c_str() + this->rawText.length(), &prevCodepointSize);

                while (prevCodepointSize--) {
                    this->rawText.pop_back();
                }
            }
        } else if (IsKeyPressed(KEY_ENTER)) {
            this->isActivated = false;
        } else {
            if (this->rawText.length() < MAX_LENGTH) {
                // NOTE: This handle is followed by instructions of Raygui
                int codepoint = GetCharPressed(), codepointSize = 0;
                if (codepoint != 0) {
                    const char *charEncoded = CodepointToUTF8(codepoint, &codepointSize);

                    for (int i = 0; i < codepointSize; i++) {
                        this->rawText += charEncoded[i];
                    }
                }
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

    if (this->isFlicked && this->isActivated) {
        this->text += '|';
    }

    if (this->isActivated) {
        for (int i = 0; i < this->suggestList.size(); ++i) {
            this->suggestList[i].setText(this->suggestListText[i + this->currentId].first);
            this->suggestList[i].setDefinition(this->suggestListText[i + this->currentId].second);
        }

        for (auto &i : this->suggestList) {
            i.update();
        }
    }
}

void SearchBox::reset() {
    this->text = this->rawText = "";
    this->isActivated = this->isFlicked = false;
    this->frameCount = 0;

    this->suggestListText.clear();
    this->suggestList.clear();
    this->currentId = 0;
    this->choseId = -1;
}

void SearchBox::updateText() {
    int codepointSize = 0, totalCodepointSize = 0, charCounter = 0, last = (int)this->rawText.length();
    const char *raw = this->rawText.c_str();
    for (; last && charCounter < MAX_VISIBLE; last -= codepointSize, totalCodepointSize += codepointSize, charCounter++) {
        codepointSize = 0;
        GetCodepointPrevious(raw + last, &codepointSize);
    }
    this->text = this->rawText.substr(last, totalCodepointSize);
}

void SearchBox::setList(std::vector<std::pair<std::string, std::string>> list) {
    this->suggestListText = std::move(list);
    int n = std::min(
            (int)this->suggestListText.size(),
            MAX_SUGGESTIONS
    );
    this->suggestList.clear();
    Rectangle rec = this->rectangleSuggest;
    for (int i = 0; i < n; i++) {
        this->suggestList.emplace_back(
                this->suggestListText[i].first,
                this->suggestListText[i].second,
                this->font,
                rec
        );
        rec.y += rec.height;
    }
    this->currentId = 0;
}

int SearchBox::getChoseId() {
    int temp = this->choseId;
    this->choseId = -1;
    return temp;
}
