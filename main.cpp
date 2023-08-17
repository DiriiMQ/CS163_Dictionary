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
    return 0;
}
