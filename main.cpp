#include <iostream>
#include "core/Api.h"
// #include "_raygui.h"
#include "io.h"
#include "core/Dict.h"
#include "fcntl.h"
using namespace std;

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    // Window  window;
    // window.run();

       Dicts dicts;
       
    //    vector<wstring> a= loadimagepath(dicts.dicts[3].words);
    //    wcout<<a[0]<<endl;
//     Api api(dicts);
//     wcout<<dicts.dicts[0].words.size()<<endl;
//     wcout << dicts.dicts[0].Map.size() << endl;
//     wcout<<dicts.dicts[1].words.size()<<endl;
//     wcout << dicts.dicts[1].Map.size() << endl;
//     wcout<<dicts.dicts[2].words.size()<<endl;
//     wcout << dicts.dicts[2].Map.size() << endl;
//     wcout << "load in " << 1.0*clock()/CLOCKS_PER_SEC << "s" << endl;
//    // wcout<<dicts.dicts[0].words[1].word;
        Api api (dicts);
        //Word a= api.apiWord.getWord(Constants::TypeDict::EN_VI,L"myxoedema");
        for( auto &a : dicts.dicts[0].words)
        {
        wcout<<a.word<<endl;
        wcout<<a.pronounce<<endl;
        for(auto & i: a.worddef){
            wcout<<i.type<<endl;
            for(auto&y : i.definition){
                wcout<<y.meaning<<endl;
                for(auto & z: y.examples){
                    wcout<<z<<endl;
                }
            }
        }
        }
    return 0;
}
