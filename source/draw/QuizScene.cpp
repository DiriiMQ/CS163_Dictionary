//
// Created by dirii on 20/8/23.
//

#include "QuizScene.h"

QuizScene::QuizScene(Font *font, Api *api, Constants::TypeDict *_currentDict, int *_currentMenuBtn) {
    this->font = font;
    this->api = api;
    this->currentDict = _currentDict;
    this->currentMenuBtn = _currentMenuBtn;

    // { 47,259,810,420 }
    this->buttonSize = {390, 100};
    this->buttonRect[0] = {
        57,
        679 - (buttonSize.y + GAP) * 2, 
        buttonSize.x, 
        buttonSize.y
    };

    this->buttonRect[1] = {
        57 + buttonSize.x + GAP,
        679 - (buttonSize.y + GAP) * 2, 
        buttonSize.x, 
        buttonSize.y
    };

    this->buttonRect[2] = {
        57,
        679 - (buttonSize.y + GAP), 
        buttonSize.x, 
        buttonSize.y
    };

    this->buttonRect[3] = {
        57 + buttonSize.x + GAP,
        679 - (buttonSize.y + GAP), 
        buttonSize.x, 
        buttonSize.y
    };

    this->restart();
}

void QuizScene::draw() {
    if (
        *this->currentDict == Constants::TypeDict::EN_EMOJI || 
        *this->currentMenuBtn == (int)Constants::Screen::menuBtn::FAVOURITE ||
        *this->currentMenuBtn == (int)Constants::Screen::menuBtn::NONE
    )
        return;

    // std::cout << "LOG: QuizScene: draw: question: " << this->question << "\n";

    DrawTextEx(
        *this->font,
        this->question.c_str(),
        {
            47 + (810 - MeasureTextEx(*this->font, this->question.c_str(), 20, SPACING).x) / 2,
            259 + GAP
        },
        25,
        SPACING,
        BLACK
    );

    for (int i = 0; i < 4; ++i) {
        this->btnQuiz[i].draw();
    }
}

void QuizScene::handleEvents() {
    if (
        *this->currentDict == Constants::TypeDict::EN_EMOJI || 
        *this->currentMenuBtn == (int)Constants::Screen::menuBtn::FAVOURITE ||
        *this->currentMenuBtn == (int)Constants::Screen::menuBtn::NONE
    )
        return;

    for (int i = 0; i < 4; ++i) {
        this->btnQuiz[i].handleEvents();
    }
}

void QuizScene::update() {
    if (
        *this->currentDict == Constants::TypeDict::EN_EMOJI || 
        *this->currentMenuBtn == (int)Constants::Screen::menuBtn::FAVOURITE ||
        *this->currentMenuBtn == (int)Constants::Screen::menuBtn::NONE
    )
        return;

    for (int i = 0; i < 4; ++i) {
        this->btnQuiz[i].update();
        if (this->btnQuiz[i].isClicked()) {
            if (this->api->apiQuiz.submitQuiz(*this->currentDict, (QuizResponse)i)) {
                this->btnQuiz[i].setStatusAnswer(true);
            } else {
                this->btnQuiz[i].setStatusAnswer(false);
            }
        }
    }
}

void QuizScene::restart() {
    if (
        *this->currentDict == Constants::TypeDict::EN_EMOJI || 
        *this->currentMenuBtn == (int)Constants::Screen::menuBtn::FAVOURITE ||
        *this->currentMenuBtn == (int)Constants::Screen::menuBtn::NONE
    )
        return;

    if (*this->currentMenuBtn == (int)Constants::Screen::menuBtn::WORD){
        std::cout << "LOG: QuizScene: restart: start getQuiz\n";
        this->currentQuiz = this->api->apiQuiz.getQuiz(*this->currentDict, true); // ?
        this->question = Utils::WStringToUTF8(this->currentQuiz.word->word);
        for (int i = 0; i < 4; ++i){
            this->btnQuiz[i] = ButtonQuiz(
                this->font, 
                Utils::WStringToUTF8(this->currentQuiz.options[i]->worddef[0].definition[0].meaning), 
                25, 
                BLUE, 
                this->buttonRect[i]
            );
        }
        std::cout << "LOG: QuizScene: restart: question: " << this->question << "\n";
    }
    if (*this->currentMenuBtn == (int)Constants::Screen::menuBtn::DEFINITION){
        this->currentQuiz = this->api->apiQuiz.getQuiz(*this->currentDict, false); // ?
        this->question = Utils::WStringToUTF8(this->currentQuiz.word->worddef[0].definition[0].meaning);
        for (int i = 0; i < 4; ++i){
            this->btnQuiz[i] = ButtonQuiz(
                this->font, 
                Utils::WStringToUTF8(this->currentQuiz.options[i]->word), 
                20, 
                BLUE, 
                this->buttonRect[i]
            );
        }
    }
    if (this->question.size()) {
        std::vector<std::string> lines;
        Utils::formatString(this->font, SPACING, this->question, 810 - 2 * GAP, 20, lines);
        this->question = lines[0];
        for (int i = 1; i < lines.size(); i++)
            this->question += "\n" + lines[i];
    }
}
