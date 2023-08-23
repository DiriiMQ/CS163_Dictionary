//
// Created by dirii on 28/7/23.
//

#ifndef CS163_GROUP9_WORD_H
#define CS163_GROUP9_WORD_H
#include <string>
#include <fstream>
#include <vector>
using namespace std;
struct Definition {
    wstring meaning;
    vector<wstring> examples;
    bool Isexample;
    Definition() {
        meaning = L"Null";
        Isexample = false;
    }
};
struct Type {
    wstring type;
    vector<Definition> definition;
    wstring phrase;
    bool Isdefinition;
    Type() {
        type = L"Null";
        phrase = L"Null";
        Isdefinition = false;
    }
};

struct Word {
    wstring word;
    wstring pronounce;
    string imagePath;
    vector<Type> worddef;
    bool IsType;
    Word() {
        pronounce = L"Null";
        imagePath = "Null";
        IsType = false;
    }
    void setData(std::wstring word, std::wstring definition, std::wstring example, std::wstring phrase,std::wstring type);

};

void writeStringVectorToFile(const std::vector<std::wstring>& strings, ofstream& outputFile);
void readStringVectorFromFile(vector<wstring>& strings, ifstream& inputFile);
void writetobinaryfile(vector<Word> &Vdictionary, const string &filename);
void readbinaryfile(vector<Word>& Vdictionary, const string &filename);
vector<wstring> loadimagepath(vector<Word> dic);
#endif //CS163_GROUP9_WORD_H