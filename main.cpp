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
    std::cout << dicts.dicts[0].Map.size() << std::endl;
    std::cout << dicts.dicts[1].Map.size() << std::endl;
    int cnt=10;
    while (cnt--){
        Word cur = api.apiWord.getRandomWord(Constants::TypeDict::EN_VI);
        wcout << cur.word << endl;
    }
    std::wcout << L"load in " << 1.0*clock()/CLOCKS_PER_SEC << std::endl;
    return 0;
}
