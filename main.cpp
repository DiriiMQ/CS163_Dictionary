#include "Window.h"
#include "_raygui.h"
#include "core/Api.h"

int main() {
    Dicts dicts;
    Api api(dicts);
    Window window(&api);
    window.run();
    // std::vector<std::wstring> wordList = api.apiSearch.getAutoCompleteListForWord(Constants::TypeDict::EN_VI, L"haa");
    // for (auto &i : wordList) {
    //     std::wcout << i << std::endl;
    // }

    // Word word = api.apiWord.getWord(Constants::TypeDict::EN_VI, L"d-ration");
    // std::cout << Utils::WStringToUTF8(word.word) << std::endl;
    // std::cout << Utils::WStringToUTF8(word.pronounce) << std::endl;
    // for (auto &i : word.worddef) {
    //     std::cout << "______\n";
    //     std::cout << '\t' << Utils::WStringToUTF8(i.type) << std::endl;

    //     for (auto &j : i.definition) {
    //         std::cout << "\t\t" << Utils::WStringToUTF8(j.meaning) << std::endl;
    //         for (auto &k : j.examples) {
    //             std::cout << "\t\t\t" << Utils::WStringToUTF8(k) << std::endl;
    //         }
    //     }

    //     std::cout << '\t' << Utils::WStringToUTF8(i.type) << std::endl;
    // }
    return 0;
}
