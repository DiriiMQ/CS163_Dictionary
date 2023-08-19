#include "Window.h"
#include "_raygui.h"
#include "core/Api.h"

int main() {
    Dicts dicts;
    Api api(dicts);
   /* Constants::TypeDict typedict = (Constants::TypeDict) 0;
    api.apiFavorite.resetFavorite(typedict);
    api.apiFavorite.addFavorite(typedict, L"Hi");
    api.apiFavorite.addFavorite(typedict, L"Hello");
    api.apiFavorite.removeFavorite(typedict, L"Hi");
    vector<wstring>tmp = api.apiFavorite.getFavorite(typedict);
    for (int i = 0; i < tmp.size(); i++)
        wcout << tmp[i];*/
    Window window(&api);
   // vector <wstring> s = api.apiSearch.getAutoCompleteListForWord((Constants::TypeDict)3, L"f");
    //wcout << s.size();
    window.run();
    return 0;
}
