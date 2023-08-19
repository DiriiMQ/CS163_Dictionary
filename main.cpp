#include "Window.h"
#include "_raygui.h"
#include "core/Api.h"

int main() {
    Dicts dicts;
    Api api(dicts);
    Window window(&api);
    vector <wstring> s = api.apiSearch.getAutoCompleteListForDefinition((Constants::TypeDict)3, L"m");
  //  wcout << s[0];
    window.run();
    return 0;
}
