//
// Created by dirii on 28/7/23.
//

#ifndef CS163_GROUP9_WORD_H
#define CS163_GROUP9_WORD_H
//#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//class Word {
//public:
//    
//};

struct Definition {
    wstring meaning;
    vector<wstring> examples;
    Definition() : meaning(), examples() {
        
    }
};
struct Type {
    wstring type;
    vector<Definition> definition;
    wstring phrase;
    Type() : type(), definition(), phrase() {
       
    }
};

struct Word {
    wstring word;
    wstring pronounce;
    vector<Type> worddef;
    int dicttype=0;
    // 1 for AV
    // 2 for AA
    // 3 for VA

    // with AA: only concentrate on wstring word and definition meaning
    // same with VA
    

};


#endif //CS163_GROUP9_WORD_H