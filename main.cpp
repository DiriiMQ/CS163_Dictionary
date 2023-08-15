#include "Window.h"
#include <iostream>
#include "_raygui.h"
#include <core/Dict.h>
#include "core/Api.h"

int main() {

    Dicts d;
   // cout<<d.dicts[1].words.size();
    cout<<d.dicts[2].words.size();
  //  ApiFavorite(d).addFavorite(Constants::TypeDict::VI_EN, L"Hello");
     void addFavorite(Constants::TypeDict typeDict, std::wstring word);
    for (int i = 0; i < 20; i++)
    {
        //cout << i << endl;
        d.dicts[2].FavouriteList.push_back(d.dicts[2].words[i].word);
       // wcout << d.dicts[1].words[i].word << endl;
    }
    Window  window;
    window.run(d);
    
    return 0;
}
