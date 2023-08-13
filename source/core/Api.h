//
// Created by dirii on 27/7/23.
//

#ifndef CS163_GROUP9_API_H
#define CS163_GROUP9_API_H

#include <string>
#include <vector>
#include "Word.h"
#include "Dict.h"
#include "Quiz.h"
#include "stuff/Constants.h"

class Dicts {
public:
    Dict dicts[3]; // use Constants::TypeDict to index
    Dicts(); // load Dicts
};

class ApiFavorite : public Dicts {
public:
    void addFavorite(Constants::TypeDict typeDict, std::string word);
    bool removeFavorite(Constants::TypeDict typeDict, std::string word); // return true if success, false if not found
    std::vector<Dict> getFavorite(Constants::TypeDict typeDict);
    void resetFavorite(Constants::TypeDict typeDict);
};

class ApiWord : public Dicts {
public:
    Word getWord(Constants::TypeDict typeDict, std::string word);
    void addWord(Constants::TypeDict typeDict, Word word);
    bool removeWord(Constants::TypeDict typeDict, std::string word); // return true if success, false if not found
    void editWord(Constants::TypeDict typeDict, std::string word, std::string newDefinition);
    Word getRandomWord(Constants::TypeDict typeDict);
};

class ApiSearch : public Dicts {
public:
    std::vector<Word> getAutoCompleteListForWord(Constants::TypeDict typeDict, std::string word);
    std::vector<Word> getAutoCompleteListForDefinition(Constants::TypeDict typeDict, std::string definition);

    std::vector<Word> getHistory(Constants::TypeDict typeDict);
};

class ApiQuiz : public Dicts {
private:
    Quiz quiz;
public:
    Quiz getQuiz(Constants::TypeDict typeDict); // random word, then recreate quiz from that word and return it
    bool submitQuiz(Constants::TypeDict typeDict, QuizResponse response); // return true if correct, false if not
};

class Api : public ApiFavorite, public ApiWord, public ApiSearch, public ApiQuiz {
public:
    void resetDict(Constants::TypeDict typeDict);
};


#endif //CS163_GROUP9_API_H
