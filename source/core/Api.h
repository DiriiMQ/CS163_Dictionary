//
// Created by dirii on 27/7/23.
//

#ifndef CS163_GROUP9_API_H
#define CS163_GROUP9_API_H

#include <string>
#include <vector>

#include "Dict.h"
#include "Quiz.h"
#include "stuff/Constants.h"

class Dicts {
public:
    Dict dicts[3]; // use Constants::TypeDict to index
    Dicts(); // load Dicts
};
//dicts -> MainDictionary
class BaseApi {
protected:
    Dicts& MainDictionary;


public:
    explicit BaseApi(Dicts& dicts) : MainDictionary(dicts) {};

};

class ApiFavorite : public BaseApi {
public:
    explicit ApiFavorite(Dicts& dicts) : BaseApi(dicts) {};


    void addFavorite(Constants::TypeDict typeDict, std::wstring word);
    bool removeFavorite(Constants::TypeDict typeDict, std::wstring word); // return true if success, false if not found
    std::vector<wstring> getFavorite(Constants::TypeDict typeDict);

    void resetFavorite(Constants::TypeDict typeDict);
};

class ApiWord : public BaseApi {
public:
    explicit ApiWord(Dicts& dicts) : BaseApi(dicts) {};


    Word getWord(Constants::TypeDict typeDict, std::wstring word);
    void addWord(Constants::TypeDict typeDict, Word word);
    bool removeWord(Constants::TypeDict typeDict, std::wstring word); // return true if success, false if not found
    void editWord(Constants::TypeDict typeDict, Word& word, int index, Word& replace);
    Word getRandomWord(Constants::TypeDict typeDict);
};

class ApiSearch : public BaseApi {
public:
    explicit ApiSearch(Dicts& dicts) : BaseApi(dicts) {};


    std::vector<wstring> getAutoCompleteListForWord(Constants::TypeDict typeDict, std::wstring word);
    std::vector<wstring> getAutoCompleteListForDefinition(Constants::TypeDict typeDict, std::wstring definition);

    std::vector<wstring> getHistory(Constants::TypeDict typeDict);
};

class ApiQuiz :  public BaseApi {
private:
    Quiz quiz;
public:
    explicit ApiQuiz(Dicts& dicts) : BaseApi(dicts) {};

    Quiz getQuiz(Constants::TypeDict typeDict, bool IsAskWordToDef);  // random word, then recreate quiz from that word and return it
    bool submitQuiz(Constants::TypeDict typeDict, QuizResponse response); // return true if correct, false if not
};

class Api : public BaseApi {
public:
    ApiFavorite apiFavorite;
    ApiWord apiWord;
    ApiSearch apiSearch;
    ApiQuiz apiQuiz;

    explicit Api(Dicts& dicts) : BaseApi(dicts), apiFavorite(dicts), apiWord(dicts), apiSearch(dicts), apiQuiz(dicts) {};

    void resetDict(Constants::TypeDict typeDict);
};


#endif //CS163_GROUP9_API_H