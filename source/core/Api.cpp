//
// Created by dirii on 27/7/23.
//

#include "Api.h"

Dicts::Dicts() {

}

void ApiFavorite::addFavorite(Constants::TypeDict typeDict, std::string word) {

}

bool ApiFavorite::removeFavorite(Constants::TypeDict typeDict, std::string word) {
    return false;
}

std::vector<Dict> ApiFavorite::getFavorite(Constants::TypeDict typeDict) {
    return std::vector<Dict>();
}

void ApiFavorite::resetFavorite(Constants::TypeDict typeDict) {

}

Word ApiWord::getWord(Constants::TypeDict typeDict, std::string word) {
    return Word();
}

void ApiWord::addWord(Constants::TypeDict typeDict, Word word) {

}

bool ApiWord::removeWord(Constants::TypeDict typeDict, std::string word) {
    return false;
}

void ApiWord::editWord(Constants::TypeDict typeDict, std::string word, std::string newDefinition) {

}

Word ApiWord::getRandomWord(Constants::TypeDict typeDict) {
    return Word();
}

std::vector<Word> ApiSearch::getAutoCompleteListForWord(Constants::TypeDict typeDict, std::string word) {
    return std::vector<Word>();
}

std::vector<Word> ApiSearch::getAutoCompleteListForDefinition(Constants::TypeDict typeDict, std::string definition) {
    return std::vector<Word>();
}

std::vector<Word> ApiSearch::getHistory(Constants::TypeDict typeDict) {
    return std::vector<Word>();
}

Quiz ApiQuiz::getQuiz(Constants::TypeDict typeDict) {
    return Quiz();
}

bool ApiQuiz::submitQuiz(Constants::TypeDict typeDict, QuizResponse response) {
    return false;
}

void Api::resetDict(Constants::TypeDict typeDict) {

}