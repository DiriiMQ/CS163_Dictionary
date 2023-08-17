#include "Window.h"
#include <iostream>
#include "_raygui.h"
#include <io.h>
#include <fcntl.h>
#include "core/Api.h"

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    srand(time(0));
    //Window  window;
    //window.run();
    Dicts dicts;
    Api api(dicts);
    wcout << dicts.dicts[0].words.size() << endl;
    wcout << dicts.dicts[1].words.size() << endl;
    wcout << dicts.dicts[2].words.size() << endl;
    /*Word cur;
    Definition def;
    def.meaning = L"Siêu đẹp trai";
    Type type;
    type.definition.push_back(def);
    cur.worddef.push_back(type);
    cur.word = L"Nghianeee";
    wcout << cur.word << endl;
    wcout << cur.worddef[0].definition[0].meaning << endl;
    api.apiWord.addWord(Constants::TypeDict::EN_VI, cur);*/
    wcout << L"load in " << 1.0*clock()/CLOCKS_PER_SEC << endl;
    return 0;
}
