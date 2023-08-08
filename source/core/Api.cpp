//
// Created by dirii on 27/7/23.
//

#include "Api.h"
#include "Dict.h"
#include "Word.h"

Dicts::Dicts() {

}

void ApiFavorite::addFavorite(Constants::TypeDict typeDict, std::wstring word) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    dictionary.FavouriteList.push_back(word);
}

bool ApiFavorite::removeFavorite(Constants::TypeDict typeDict, std::wstring word) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    for (int i = 0; i < dictionary.FavouriteList.size(); i++) {
        if (dictionary.FavouriteList[i] == word) {
            swap(dictionary.FavouriteList[i], dictionary.FavouriteList.back());
            dictionary.FavouriteList.pop_back();
            return true;
        }
    }
    return false;
}
//?
std::vector<Dict> ApiFavorite::getFavorite(Constants::TypeDict typeDict) {
    return std::vector<Dict>();
}

void ApiFavorite::resetFavorite(Constants::TypeDict typeDict) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    dictionary.FavouriteList.clear();
}
//if that word is not exist?
Word ApiWord::getWord(Constants::TypeDict typeDict, std::wstring word) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    if (dictionary.Map.find(word)) {
        int index = dictionary.Map[word];
        return dictionary.words[index];
    }
    return Word();
}

void ApiWord::addWord(Constants::TypeDict typeDict, Word word) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    dictionary.words.push_back(word);
    dictionary.Map[word.word] = dictionary.words.size()-1;
}

bool ApiWord::removeWord(Constants::TypeDict typeDict, std::wstring word) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    if (dictionary.Map.find(word)) {
        int index = dictionary.Map[word];
        swap(dictionary.words[index], dictionary.words.back());
        dictionary.words.pop_back();
        dictionary.Map.remove(word);
        return true;
    }
    return false;
}

void ApiWord::editWord(Constants::TypeDict typeDict, Word &word, int index, std::wstring newDefinition) {

}

Word ApiWord::getRandomWord(Constants::TypeDict typeDict) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    pair<wstring,int> WordRand = dictionary.Map.getRandom();
    return dictionary.words[WordRand.second];
}

std::vector<Word> ApiSearch::getAutoCompleteListForWord(Constants::TypeDict typeDict, std::wstring word) {
    return std::vector<Word>();
}

std::vector<Word> ApiSearch::getAutoCompleteListForDefinition(Constants::TypeDict typeDict, std::wstring definition) {
    return std::vector<Word>();
}
//edit word -> string
std::vector<wstring> ApiSearch::getHistory(Constants::TypeDict typeDict) {
    return MainDictionary.dicts[static_cast<int>(typeDict)].HistoryList;
}

Quiz ApiQuiz::getQuiz(Constants::TypeDict typeDict) {
    return Quiz();
}

bool ApiQuiz::submitQuiz(Constants::TypeDict typeDict, QuizResponse response) {
    return false;
}

void Api::resetDict(Constants::TypeDict typeDict) {

}