#include <iostream>
#include "core/Api.h"
// #include "_raygui.h"
using namespace std;

int main() {
    // Window  window;
    // window.run();

    Dicts dicts;
    Api api(dicts);
    wcout<<dicts.dicts[0].words.size()<<endl;
    wcout<<dicts.dicts[1].words.size()<<endl;
    wcout<<dicts.dicts[2].words.size()<<endl;
   // wcout<<dicts.dicts[0].words[1].word;
    Word cur;
    cur.word= L"Si";
    Type type;
    Definition def;
    def.meaning=L"Dep Trai";
    type.definition.push_back(def);
    cur.worddef.push_back(type);
    api.apiWord.addWord(Constants::TypeDict::EN_VI,cur);
    wcout<<dicts.dicts[0].words.size()<<endl;
    wcout<<dicts.dicts[1].words.size()<<endl;
    wcout<<dicts.dicts[2].words.size()<<endl;
    return 0;
}
