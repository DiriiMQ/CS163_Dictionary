//
// Created by dirii on 28/7/23.
//

#ifndef CS163_GROUP9_DICT_H
#define CS163_GROUP9_DICT_H

#include <vector>
#include "Word.h"
#include "Trie.h"

class Dict {
public:
    std::vector<Word> words;
    Trie<int> Map;
    vector<wstring> FavoriteList;
    vector<wstring> HistoryList;
    Trie<Trie<int>> WordsOfDef;
};


#endif //CS163_GROUP9_DICT_H