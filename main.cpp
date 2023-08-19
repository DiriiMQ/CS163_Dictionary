#include "Window.h"
#include "_raygui.h"
#include "core/Api.h"

int main() {
    Dicts dicts;
    Api api(dicts);
    Window window(&api);
    vector <wstring> s = api.apiSearch.getAutoCompleteListForWord((Constants::TypeDict)3, L"f");
    wcout << s.size();
    window.run();
    return 0;
}
