//
// Created by dirii on 27/7/23.
//

#include "Api.h"
#include "Dict.h"
#include "Word.h"
#include "CompareString.h"
//Add data to each dicts[index], vector and Trie - Sĩ
Dicts::Dicts() {
    string filename2 = "assets\\data\\Anh-Anh.dat";
    string filename = "asset\\data\\Anh_Viet.dat";
    string filename3 = "assets\\data\\Viet_Anh.dat";
  

    readbinaryfile(dicts[0].words, filename);
 
    for (int i = 0; i < dicts[0].words.size(); i++) {
        dicts[0].Map[dicts[0].words[i].word] = i;
    }
   
    
    readbinaryfile(dicts[1].words, filename2);
    for (int i = 0; i < dicts[1].words.size(); i++) {
        dicts[1].Map[dicts[1].words[i].word] = i;
    }
    
   
    readbinaryfile(dicts[2].words, filename3);
    for (int i = 0; i < dicts[2].words.size(); i++) {
        dicts[2].Map[dicts[2].words[i].word] = i;
    }
    
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
// why vector<Dict>?// Dict->wstring
std::vector<wstring> ApiFavorite::getFavorite(Constants::TypeDict typeDict) {
    return MainDictionary.dicts[static_cast<int>(typeDict)].FavouriteList;
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
// how to edit, Sĩ
void ApiWord::editWord(Constants::TypeDict typeDict, Word& word, int index, Word& replace) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    dictionary.words[index].worddef = replace.worddef;
    string filename;
    if (typeDict == Constants::TypeDict::VI_EN) {
        filename = "assets\\data\\Anh_Vietfix.dat";
    }
    else if (typeDict == Constants::TypeDict::En_En) {
        filename = "assets\\data\\Anh_Anhfix.dat";
    }
    else {
        filename = "assets\\data\\Viet_Anhfix.dat";

    }
    writetobinaryfile(dictionary.words, filename);
}

Word ApiWord::getRandomWord(Constants::TypeDict typeDict) {
    srand(time(0));
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    pair<wstring,int> WordRand = dictionary.Map.getRandom();
    return dictionary.words[WordRand.second];
}

std::vector<wstring> ApiSearch::getAutoCompleteListForWord(Constants::TypeDict typeDict, std::wstring word) {
    vector<wstring> AutoCompleteList;
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    dictionary.Map.getAutoComplete(word, AutoCompleteList);
    return move(AutoCompleteList);
}
//What is definition?
std::vector<Word> ApiSearch::getAutoCompleteListForDefinition(Constants::TypeDict typeDict, std::wstring definition) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    return std::vector<Word>();
}
//edit word -> string
std::vector<wstring> ApiSearch::getHistory(Constants::TypeDict typeDict) {
    return MainDictionary.dicts[static_cast<int>(typeDict)].HistoryList;
}

Quiz ApiQuiz::getQuiz(Constants::TypeDict typeDict) {
    srand(time(0));
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    quiz.options.clear();
    for (int i=0; i<4; i++){
        unsigned int temp = 0;
        for (int i = 0; i < 4; ++i){
            temp = (temp << 8) | (rand() % 256);
        }
        quiz.options.push_back(&dictionary.words[temp % dictionary.words.size()]);
    }    
    int temp = rand() % 4;
    quiz.word = quiz.options[temp];
    return quiz;
}
//Is it the right way to use "response"?
bool ApiQuiz::submitQuiz(Constants::TypeDict typeDict, QuizResponse response) {
    if (quiz.options[static_cast<int>(response)] == quiz.word) return true;
    return false;
}
//Sĩ
void Api::resetDict(Constants::TypeDict typeDict) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    
    string filename;
    if (typeDict == Constants::TypeDict::VI_EN) {
        filename = "assets\\data\\Anh_Viet.dat";
    }
    else if (typeDict == Constants::TypeDict::En_En) {
        filename = "assets\\data\\Anh_Anh.dat";
    }
    else {
        filename = "assets\\data\\Viet_Anh.dat";
    }
    vector<Word> ddictionary;
    readbinaryfile(ddictionary, filename);
    string newfilename;
    size_t lastSlashPos = filename.find_last_of("\\");
    if (lastSlashPos != std::string::npos) {

        string path = filename.substr(0, lastSlashPos + 1);
        string newFilename = "Anh_Vietfix.dat";

       newfilename = path + newFilename;
    }

    writetobinaryfile(ddictionary, newfilename);
    dictionary.words.clear();
    dictionary.Map.clear();
    dictionary.FavouriteList.clear();
    dictionary.HistoryList.clear();
    for (size_t i = 0; i < ddictionary.size(); i++) {
        dictionary.Map[ddictionary[i].word] = i;
    }
    dictionary.words = move(ddictionary);
}