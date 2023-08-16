#include <iostream>
#include "core/Api.h"
// #include "_raygui.h"
using namespace std;

int main() {
    // Window  window;
    // window.run();

    Dicts dicts;
    Api api(dicts);

    std::wcout << L"done\n";
   // wcout<<dicts.dicts[0].words[1].word;
    std::wcout << api.apiWord.getWord(Constants::TypeDict::EN_VI, L"apple").word;

    return 0;
}
