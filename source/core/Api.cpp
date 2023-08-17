//
// Created by dirii on 27/7/23.
//

#include "Api.h"
#include "Dict.h"
#include "Word.h"
#include "CompareString.h"
void MakeDef(const Word &curWord, Dict& dicts, int del){
    for (int j=0; j<curWord.worddef.size(); j++){
            for (int k=0; k<curWord.worddef[j].definition.size(); k++){
                wistringstream ss(curWord.worddef[j].definition[k].meaning);
                wstring token;
                while (ss >> token){
                    if (!dicts.WordsOfDef.find(token)){
                        Trie<int> temp;
                        dicts.WordsOfDef[token] = move(temp);
                    }
                    Trie<int> *temp = &(dicts.WordsOfDef[token]);
                    if (del==1){
                        if (!(*temp).find(curWord.word)){
                            (*temp)[curWord.word] = 1;
                        }
                        else (*temp)[curWord.word] += 1;
                    } else {
                        if ((*temp)[curWord.word] == 1){
                            (*temp).remove(curWord.word);
                        }
                        else (*temp)[curWord.word] -= 1;
                    }
                    
                }
            }
        }
}
Dicts::Dicts() {
    string filename2 = "../assets/data/Anh_Anh.dat";
    string filename = "../assets/data/Anh_Viet.dat";
    string filename3 = "../assets/data/Viet_Anh.dat";
  

    readbinaryfile(dicts[0].words, filename);
    for (int i = 0; i < dicts[0].words.size(); i+=5) {
        dicts[0].Map[dicts[0].words[i].word] = i;
        MakeDef(dicts[0].words[i], dicts[0],1);
    }
    
    readbinaryfile(dicts[1].words, filename2);
    for (int i = 0; i < dicts[1].words.size(); i+=5) {
        dicts[1].Map[dicts[1].words[i].word] = i;
        MakeDef(dicts[1].words[i], dicts[1],1);

    }
    
   
    readbinaryfile(dicts[2].words, filename3);
    for (int i = 0; i < dicts[2].words.size(); i++) {
        dicts[2].Map[dicts[2].words[i].word] = i;
        MakeDef(dicts[2].words[i], dicts[2],1);
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
std::vector<wstring> ApiFavorite::getFavorite(Constants::TypeDict typeDict) {
    return MainDictionary.dicts[static_cast<int>(typeDict)].FavouriteList;
}

void ApiFavorite::resetFavorite(Constants::TypeDict typeDict) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    dictionary.FavouriteList.clear();
}
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
    MakeDef(dictionary.words.back(),dictionary,1);
}

bool ApiWord::removeWord(Constants::TypeDict typeDict, std::wstring word) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    if (dictionary.Map.find(word)) {
        int index = dictionary.Map[word];
        swap(dictionary.words[index], dictionary.words.back());
        MakeDef(dictionary.words.back(),dictionary,-1);
        dictionary.words.pop_back();
        dictionary.Map.remove(word);
        return true;
    }
    return false;
}
void ApiWord::editWord(Constants::TypeDict typeDict, Word& word, int index, Word& replace) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    MakeDef(dictionary.words[index],dictionary,-1);
    dictionary.words[index].worddef = replace.worddef;
    MakeDef(dictionary.words[index],dictionary,1);
    string filename;
    if (typeDict == Constants::TypeDict::VI_EN) {
        filename = "data\\Anh_Vietfix.dat";
    }
    else if (typeDict == Constants::TypeDict::En_En) {
        filename = "data\\Anh_Anhfix.dat";
    }
    else {
        filename = "data\\Viet_Anhfix.dat";

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
    std::cout << "LOG: Api: ApiSearch: size of AutoCompleteList: " << AutoCompleteList.size() << std::endl;
    return move(AutoCompleteList);
}
std::vector<wstring> ApiSearch::getAutoCompleteListForDefinition(Constants::TypeDict typeDict, std::wstring definition) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    wstringstream ss(definition);
    wstring token;
    vector<wstring> result;
    bool check=false;
    while (ss >> token){
        if (!dictionary.WordsOfDef.find(token)){
            result.clear();
            return result;
        }
        auto temp = dictionary.WordsOfDef[token].getAllConstRef();
        if (!check){
            for (int i=0; i<temp.size(); i++){
                result.push_back(temp[i].first);
            }
            check=true;
        } else {
            vector<wstring> temp2;
            for (int i=0; i<temp.size(); i++){
                if (find(result.begin(), result.end(), temp[i].first) != result.end()){
                    temp2.push_back(temp[i].first);
                }
            }
            result = temp2;
        }
        if (result.size()==0) return result;
    }
    return move(result);
}
//edit word -> string
std::vector<wstring> ApiSearch::getHistory(Constants::TypeDict typeDict) {
    return MainDictionary.dicts[static_cast<int>(typeDict)].HistoryList;
}

Quiz ApiQuiz::getQuiz(Constants::TypeDict typeDict, bool IsAskWordToDef) {
    srand(time(0));
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    const int MAX_LENGTH_OF_QUESTION = 50;
    const int MAX_LENGTH_OF_ANSWER = 20;
    quiz.options.clear();
    for (int i=0; i<4; i++){
        while (1){
            unsigned int temp = 0;
            for (int i = 0; i < 4; ++i){
                temp = (temp << 8) | (rand() % 256);
            }
            Word *cur = &dictionary.words[temp % dictionary.words.size()];
            int Min_Length_Of_Definition = 100000;
            for (int j=0; j<cur->worddef.size(); j++){
                for (int k=0; k<cur->worddef[j].definition.size(); k++){
                    if (Min_Length_Of_Definition > cur->worddef[j].definition[k].meaning.size()){
                        Min_Length_Of_Definition = cur->worddef[j].definition[k].meaning.size();
                    }
                }
            }
            if (IsAskWordToDef){
                if (cur->word.size()<MAX_LENGTH_OF_QUESTION && Min_Length_Of_Definition<MAX_LENGTH_OF_ANSWER){
                    quiz.options.push_back(cur);
                    break;
                }
            } else {
                if (cur->word.size()<MAX_LENGTH_OF_ANSWER && Min_Length_Of_Definition<MAX_LENGTH_OF_QUESTION){
                    quiz.options.push_back(cur);
                    break;
                }
            }
        }
    }    
    int temp = rand() % 4;
    quiz.word = quiz.options[temp];
    return quiz;
}
bool ApiQuiz::submitQuiz(Constants::TypeDict typeDict, QuizResponse response) {
    if (quiz.options[static_cast<int>(response)] == quiz.word) return true;
    return false;
}
//Sĩ
void Api::resetDict(Constants::TypeDict typeDict) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    
    string filename;
    if (typeDict == Constants::TypeDict::VI_EN) {
        filename = "data\\Anh_Viet.dat";
    }
    else if (typeDict == Constants::TypeDict::En_En) {
        filename = "data\\Anh_Anh.dat";
    }
    else {
        filename = "data\\Viet_Anh.dat";
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