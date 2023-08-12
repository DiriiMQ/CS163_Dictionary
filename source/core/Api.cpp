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

void ApiWord::editWord(Constants::TypeDict typeDict, Word& word, int index, Word& replace) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    dictionary.words[index].worddef = replace.worddef;
    string filename;
    if (typeDict == Constants::TypeDict::VI_EN) {
        filename = "G:\\year1\\Semester 2\\Cs162\\Group project\\CS163_Group9\\assets\\data\\Anh_Vietfix.dat";
    }
    else if (typeDict == Constants::TypeDict::En_En) {
        filename = "G:\\year1\\Semester 2\\Cs162\\Group project\\CS163_Group9\\assets\\data\\Anh_Anhfix.dat";
    }
    else {
        filename = "G:\\year1\\Semester 2\\Cs162\\Group project\\CS163_Group9\\assets\\data\\Viet_Anhfix.dat";

    }
    writetobinaryfile(dictionary.words, filename);
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
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    
    string filename;
    if (typeDict == Constants::TypeDict::VI_EN) {
        filename = "G:\\year1\\Semester 2\\Cs162\\Group project\\CS163_Group9\\assets\\data\\Anh_Viet.dat";
    }
    else if (typeDict == Constants::TypeDict::En_En) {
        filename = "G:\\year1\\Semester 2\\Cs162\\Group project\\CS163_Group9\\assets\\data\\Anh_Anh.dat";
    }
    else {
        filename = "G:\\year1\\Semester 2\\Cs162\\Group project\\CS163_Group9\\assets\\data\\Viet_Anh.dat";
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
}
