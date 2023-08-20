//
// Created by dirii on 20/8/23.
//

#ifndef CS163_GROUP9_QUIZSCENE_H
#define CS163_GROUP9_QUIZSCENE_H

#include "stuff/Button.h"
#include "stuff/Constants.h"
#include "core/Api.h"

class QuizScene {
private:
    Api *api;
    Constants::TypeDict *currentDict;
    int *currentMenuBtn;
    Font *font;

    Vector2 buttonSize;
    Rectangle buttonRect[4];

    ButtonQuiz btnQuiz[4];
    std::string question;
    bool isShowingQuiz = false;

    Quiz currentQuiz;

public:
    static constexpr int GAP = 10,
                        SPACING = 1;

    QuizScene() = default;
    QuizScene(Font *font, Api *api, Constants::TypeDict *currentDict, int *currentMenuBtn);

    void draw();
    void handleEvents();
    void update();

    void restart();
};

#endif //CS163_GROUP9_QUIZSCENE_H