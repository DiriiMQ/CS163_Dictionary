//
// Created by dirii on 28/7/23.
//

#ifndef CS163_GROUP9_QUIZ_H
#define CS163_GROUP9_QUIZ_H

#include <vector>
#include "Word.h"

enum class QuizResponse {
    A, B, C, D
};

class Quiz {
public:
    Word *word;
    std::vector<Word*> options; // 4 options
};


#endif //CS163_GROUP9_QUIZ_H
