//
// Created by dirii on 27/7/23.
//

#include "Api.h"
#include "Dict.h"
#include "Word.h"
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
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
     string filename1 = "../assets/data/Anh_Viet.dat";
    string filename1_favorite = "../assets/data/Anh_Viet_favorite.dat";
    string filename1_history = "../assets/data/Anh_Viet_history.dat";
    string filename2 = "../assets/data/Viet_Anh.dat";
    string filename2_favorite = "../assets/data/Viet_Anh_favorite.dat";
    string filename2_history = "../assets/data/Viet_Anh_history.dat";
    string filename3 = "../assets/data/Anh_Anh.dat";
    string filename3_favorite = "../assets/data/Anh_Anh_favorite.dat";
    string filename3_history = "../assets/data/Anh_Anh_history.dat";
    string filename4 = "../assets/data/emoji.dat";
    string filename4_favorite = "../assets/data/emoji_favorite.dat";
    string filename4_history = "../assets/data/emoji_history.dat";
    ifstream wfin;

    readbinaryfile(dicts[0].words, filename1);
    wfin.open(filename1_favorite, ios::binary | ios::in);
    if (!wfin) {
        cout << "Can't open file Favorite" << endl;
        wcout << "Can't open file Favorite" << endl;
        return;
    }
    readStringVectorFromFile(dicts[0].FavoriteList, wfin);
    wfin.close();
    wfin.open(filename1_history, ios::binary | ios::in);
    if (!wfin) {
        cout << "Can't open file Favorite" << endl;
        wcout << "Can't open file Favorite" << endl;
        return;
    }
    readStringVectorFromFile(dicts[0].HistoryList, wfin);
    wfin.close();
    for (int i = 0; i < dicts[0].words.size(); i++) {
        dicts[0].Map[dicts[0].words[i].word] = i;
        MakeDef(dicts[0].words[i],dicts[0],1);
    }
   
    
    readbinaryfile(dicts[1].words, filename2);
    wfin.open(filename2_favorite, ios::binary | ios::in);
    if (!wfin) {
        cout << "Can't open file Favorite" << endl;
        wcout << "Can't open file Favorite" << endl;
        return;
    }
    readStringVectorFromFile(dicts[1].FavoriteList, wfin);
    wfin.close();
    wfin.open(filename2_history, ios::binary | ios::in);
    if (!wfin) {
        cout << "Can't open file Favorite" << endl;
        wcout << "Can't open file Favorite" << endl;
        return;
    }
    readStringVectorFromFile(dicts[1].HistoryList, wfin);
    wfin.close();

    for (int i = 0; i < dicts[1].words.size(); i++) {
        dicts[1].Map[dicts[1].words[i].word] = i;
        MakeDef(dicts[1].words[i],dicts[1],1);
    }
    
   
    readbinaryfile(dicts[2].words, filename3);
    wfin.open(filename3_favorite, ios::binary | ios::in);
    if (!wfin) {
        cout << "Can't open file Favorite" << endl;
        wcout << "Can't open file Favorite" << endl;
        return;
    }
    readStringVectorFromFile(dicts[2].FavoriteList, wfin);
    wfin.close();
    wfin.open(filename3_history, ios::binary | ios::in);
    if (!wfin) {
        cout << "Can't open file Favorite" << endl;
        wcout << "Can't open file Favorite" << endl;
        return;
    }
    readStringVectorFromFile(dicts[2].HistoryList, wfin);
    wfin.close();
    for (int i = 0; i < dicts[2].words.size(); i++) {
        dicts[2].Map[dicts[2].words[i].word] = i;
        MakeDef(dicts[2].words[i],dicts[2],1);
    }
    wfin.open(filename4_favorite, ios::binary | ios::in);
    if (!wfin) {
        cout << "Can't open file Favorite" << endl;
        wcout << "Can't open file Favorite" << endl;
        return;
    }
    readStringVectorFromFile(dicts[3].FavoriteList, wfin);
    wfin.close();
    wfin.open(filename4_history, ios::binary | ios::in);
    if (!wfin) {
        cout << "Can't open file Favorite" << endl;
        wcout << "Can't open file Favorite" << endl;
        return;
    }
    readStringVectorFromFile(dicts[3].HistoryList, wfin);
    wfin.close();
    readbinaryfile(dicts[3].words,filename4);
    for (int i = 0; i < dicts[3].words.size(); i++) {
        dicts[3].Map[dicts[3].words[i].word] = i;
        MakeDef(dicts[3].words[i],dicts[3],1);
    }
}
Dicts::~Dicts(){
    string filename1 = "../assets/data/Anh_Viet.dat";
    string filename1_favorite = "../assets/data/Anh_Viet_favorite.dat";
    string filename1_history = "../assets/data/Anh_Viet_history.dat";
    string filename2 = "../assets/data/Viet_Anh.dat";
    string filename2_favorite = "../assets/data/Viet_Anh_favorite.dat";
    string filename2_history = "../assets/data/Viet_Anh_history.dat";
    string filename3 = "../assets/data/Anh_Anh.dat";
    string filename3_favorite = "../assets/data/Anh_Anh_favorite.dat";
    string filename3_history = "../assets/data/Anh_Anh_history.dat";
    string filename4 = "../assets/data/emoji.dat";
    string filename4_favorite = "../assets/data/emoji_favorite.dat";
    string filename4_history = "../assets/data/emoji_history.dat";
    writetobinaryfile(dicts[0].words, filename1);
    writetobinaryfile(dicts[1].words, filename2);
    writetobinaryfile(dicts[2].words, filename3);
    writetobinaryfile(dicts[3].words,filename4);
    ofstream wfout;
    //Save favorite
    wfout.open(filename1_favorite, ios::binary | ios::out);
    writeStringVectorToFile(dicts[0].FavoriteList, wfout);
    wfout.close();
    wfout.open(filename2_favorite, ios::binary | ios::out);
    writeStringVectorToFile(dicts[1].FavoriteList, wfout);
    wfout.close();
    wfout.open(filename3_favorite, ios::binary | ios::out);
    writeStringVectorToFile(dicts[2].FavoriteList, wfout);
    wfout.close();
    wfout.open(filename4_favorite, ios::binary | ios::out);
    writeStringVectorToFile(dicts[3].FavoriteList, wfout);
    wfout.close();
    //Save history
    wfout.open(filename1_history, ios::binary | ios::out);
    writeStringVectorToFile(dicts[0].HistoryList, wfout);
    wfout.close();
    wfout.open(filename2_history, ios::binary | ios::out);
    writeStringVectorToFile(dicts[1].HistoryList, wfout);
    wfout.close();
    wfout.open(filename3_history, ios::binary | ios::out);
    writeStringVectorToFile(dicts[2].HistoryList, wfout);
    wfout.close();
    wfout.open(filename4_history, ios::binary | ios::out);
    writeStringVectorToFile(dicts[3].HistoryList, wfout);
    wfout.close();
    wcout << "Done in " << 1.0*clock()/CLOCKS_PER_SEC << endl;
}
void ApiFavorite::addFavorite(Constants::TypeDict typeDict, std::wstring word) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    dictionary.FavoriteList.push_back(word);
}

bool ApiFavorite::removeFavorite(Constants::TypeDict typeDict, std::wstring word) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    for (int i = 0; i < dictionary.FavoriteList.size(); i++) {
        if (dictionary.FavoriteList[i] == word) {
            swap(dictionary.FavoriteList[i], dictionary.FavoriteList.back());
            dictionary.FavoriteList.pop_back();
            return true;
        }
    }
    return false;
}
std::vector<wstring> ApiFavorite::getFavorite(Constants::TypeDict typeDict) {
    if (MainDictionary.dicts[static_cast<int>(typeDict)].FavoriteList.size()==1) return vector<wstring>();
    return MainDictionary.dicts[static_cast<int>(typeDict)].FavoriteList;
}

void ApiFavorite::resetFavorite(Constants::TypeDict typeDict) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    dictionary.FavoriteList.clear();
    dictionary.FavoriteList.push_back(L"Null");
}
bool ApiWord::isFavorite(Constants::TypeDict typeDict, std::wstring word){
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    for (int i = 0; i < dictionary.FavoriteList.size(); i++) {
        if (dictionary.FavoriteList[i] == word) {
            return true;
        }
    }
    return false;
}
Word ApiWord::getWord(Constants::TypeDict typeDict, std::wstring word) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    dictionary.HistoryList.push_back(word);
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
        for (int i = 0; i < dictionary.FavoriteList.size(); i++)
            if (dictionary.FavoriteList[i] == word) {
                swap(dictionary.FavoriteList[i], dictionary.FavoriteList.back());
                dictionary.FavoriteList.pop_back();
            }
        return true;
    }
    return false;
}
void ApiWord::editWord(Constants::TypeDict typeDict, Word& replace) {
    Dict& dictionary = MainDictionary.dicts[static_cast<int>(typeDict)];
    int index = dictionary.Map[replace.word];
    MakeDef(dictionary.words[index],dictionary,-1);
    dictionary.words[index].worddef = replace.worddef;
    MakeDef(dictionary.words[index],dictionary,1);
}

Word ApiWord::getRandomWord(Constants::TypeDict typeDict) {
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
std::vector<wstring> ApiSearch::getHistory(Constants::TypeDict typeDict) {
    vector<wstring> result = MainDictionary.dicts[static_cast<int>(typeDict)].HistoryList;
    reverse(result.begin(), result.end());
    result.pop_back();
    return result;
}

Quiz ApiQuiz::getQuiz(Constants::TypeDict typeDict, bool IsAskWordToDef) {
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
            if (cur->worddef.empty() || cur->worddef[0].definition.empty()) continue;
            int Min_Length_Of_Definition = cur->worddef[0].definition[0].meaning.size();
            if (IsAskWordToDef){
                if (cur->word.size() < MAX_LENGTH_OF_QUESTION && Min_Length_Of_Definition < MAX_LENGTH_OF_ANSWER){
                    quiz.options.push_back(cur);
                    break;
                }
            } else {
                if (cur->word.size() < MAX_LENGTH_OF_ANSWER && Min_Length_Of_Definition < MAX_LENGTH_OF_QUESTION){
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
   if (typeDict == Constants::TypeDict::EN_VI) {
        filename = "../assets/data/Anh_Viet_Original.dat";
    }
    else if (typeDict == Constants::TypeDict::EN_EN) {
        filename = "..\\assets\\data\\Anh_Anh_Original.dat";
    }
    else if (typeDict == Constants::TypeDict::VI_EN) {
        filename = "../assets/data/Viet_Anh_Original.dat";
    } else {
        filename = "../assets/data/emoji_Original.dat";
    }
    vector<Word> ddictionary;
    readbinaryfile(ddictionary, filename);
    string newfilename;
    if (typeDict == Constants::TypeDict::EN_VI) {
        newfilename = "../assets/data/Anh_Viet.dat";
    }
    else if (typeDict == Constants::TypeDict::EN_EN) {
        newfilename = "..\\assets\\data\\Anh_Anh.dat";
    }
    else if (typeDict == Constants::TypeDict::VI_EN) {
        newfilename = "../assets/data/Viet_Anh.dat";
    } else {
        newfilename = "../assets/data/emoji.dat";
    }
    writetobinaryfile(ddictionary, newfilename);
    
    dictionary.words.clear();
    dictionary.Map.clear();
    dictionary.FavoriteList.clear();
    dictionary.HistoryList.clear();
    dictionary.WordsOfDef.clear();
    for (int i = 0; i < ddictionary.size(); i++) {
        dictionary.Map[ddictionary[i].word] = i;
        MakeDef(ddictionary[i],dictionary,1);
    }
    
    dictionary.FavoriteList.push_back(L"Null");
    dictionary.HistoryList.push_back(L"Null");
    dictionary.words = move(ddictionary);
}