//#include "Window.h"
#include <iostream>
#include <stdio.h>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>
#include <fstream>
#include <vector>
#include <string>
#include <codecvt>
using namespace std;

int main() {

    // _setmode(_fileno(stdout), _O_U16TEXT);
    //setlocale(LC_ALL, "");
    /*_setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);*/
    //std::locale::global(std::locale(""));
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    
    

    wifstream wfin;
    string filename = "G:\\year1\\Semester 2\\Cs162\\Group project\\CS163_Group9\\assets\\data\\Test.txt";
    
    vector<WordAV> Vdictionary = readAVdictionary(filename);
    cout << "Done\n";

    return 0;

}