#include "Window.h"
#include "_raygui.h"
#include <core/Dict.h>
#include "core/Api.h"
#include <iostream>
#include <fcntl.h> //_O_WTEXT
#include <io.h>    //_setmode()
#include <string>
#include <locale>
#include <codecvt> //possible C++11?
#include <fstream>
int main() {
    //_setmode(_fileno(stdout), _O_WTEXT); //needed for output
    //_setmode(_fileno(stdin), _O_WTEXT); //needed for input
  //  Dicts d;
  // // cout<<d.dicts[1].words.size();
  //  wcout<<d.dicts[0].words.size()<<endl;
  //  wcout<<d.dicts[1].words.size() << endl;
  //  wcout<<d.dicts[2].words.size() << endl;
  ////  ApiFavorite(d).addFavorite(Constants::TypeDict::VI_EN, L"Hello");
  //   void addFavorite(Constants::TypeDict typeDict, std::wstring word);
  //  for (int i = 0; i < 20; i++)
  //  {
  //      //cout << i << endl;
  //      d.dicts[1].FavouriteList.push_back(d.dicts[1].words[i].word);
  //      d.dicts[0].FavouriteList.push_back(d.dicts[0].words[i].word);
  //      d.dicts[2].FavouriteList.push_back(d.dicts[2].words[i].word);
  //     // wcout << d.dicts[1].words[i].word << endl;
  //  }
  //  for (int i = 0; i < 20; i++)
  //  {
  //      wcout << d.dicts[1].FavouriteList[i] << endl;
  //  }
  //  wcout << L"Chương trình kết thúc" << endl;
    Window  window;
    window.run();
    
    return 0;
}
