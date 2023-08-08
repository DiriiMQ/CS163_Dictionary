//
// Created by dirii on 28/7/23.
//

#ifndef CS163_GROUP9_WORD_H
#define CS163_GROUP9_WORD_H
#include <bits/stdc++.h>

#include <vector>
using namespace std;
class Word {
public:
    
};

struct Definition {
    wstring meaning;
    vector<wstring> examples;
};
struct Type {
    wstring type;
    vector<Definition> definition;
    wstring phrase;
};

struct WordAV {
    wstring word;
    wstring pronounce;
    vector<Type> worddef;
    vector<wstring> sideexplain;
    vector<wstring> engdef;
};
struct WordAA {
    wstring word;
    vector<wstring> definition;
};
struct WordVA {
    wstring word;
    wstring definition;
};
struct Word {
    vector<WordAV> Vdic;
    vector<WordAA> Edic;
    vector<WordVA> VEdic;
};
vector<WordAV> readAVdictionary(const string& filename);


#endif //CS163_GROUP9_WORD_H
