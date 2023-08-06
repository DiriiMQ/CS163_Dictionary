//
// Created by dirii on 28/7/23.
//

#ifndef CS163_GROUP9_WORD_H
#define CS163_GROUP9_WORD_H
#include <bits/stdc++.h>

#include <vector>
using namespace std;
class Word {
public:
    
};

struct Definition {
    wstring meaning;
    vector<wstring> examples;
};
struct Type {
    wstring type;
    vector<Definition> definition;
    wstring phrase;
};

struct WordAV {
    wstring word;
    wstring pronounce;
    vector<Type> worddef;
    vector<wstring> sideexplain;
};
vector<WordAV> readAVdictionary(const string& filename)
{
    locale loc(locale(), new codecvt_utf8<wchar_t>);
    vector<WordAV> Vdictionary;
    wifstream wfin(filename, ios::binary);
    wfin.imbue(loc);
    if (!wfin) {
        cout << "Error open Vietnamese Dictionary";
        return Vdictionary;
    }
    wstring line;
    /*const int bufferSize = 8192;
    wchar_t buffer[bufferSize];

    wfin.rdbuf()->pubsetbuf(buffer, bufferSize);*/
    getline(wfin, line);
    while (line.size()==1 || line[0] == L'@') {

        WordAV cur;
        if (line.size()==1)
        {
            getline(wfin, line);

            continue;
        }
        else if (line[0] == L'@') {
            wcout << line[0] << endl;
            // word and pronounciation

            size_t firstSlash = line.find('/');
            if (firstSlash != std::string::npos) {

                cur.word = line.substr(1, firstSlash - 1);
                size_t secondSlash = line.find('/', firstSlash + 1);
                cur.pronounce = line.substr(firstSlash + 1, secondSlash - firstSlash - 1);
                wcout << cur.pronounce << endl;
                wcout << cur.word << endl;
            }
            else {
                cur.word = line.substr(1);
                wcout << cur.word;
            }

            getline(wfin, line);

            while (line.size() != 1)
            {
                if (line[0] == L'*' || line[0] == L'!') {
                    //type
                    wcout << line[0] << endl;
                    Type wordtype;
                    if (line[0] == L'*')
                        wordtype.type = line.substr(1);
                    else wordtype.phrase = line.substr(1);
                    getline(wfin, line);
                    while (line.size() != 1) {
                        if (line[0] == L'-') {
                            wcout << line[0] << endl;
                            Definition def;
                            def.meaning = line.substr(1);
                            getline(wfin, line);
                            while (line.size() != 1) {
                                if (line[0] == L'=') {
                                    wcout << line[0] << endl;
                                    def.examples.push_back(line.substr(1));
                                    getline(wfin, line);

                                }
                                else break;
                            }

                            wordtype.definition.push_back(def);
                            cur.worddef.push_back(wordtype);

                        }
                        else if (line[0] == L'/' || iswalpha(line[0])) {
                            getline(wfin, line);
                        }


                        else break;

                    }

                }
                else if (line[0] == L'-') {
                    Type wordtype;
                    Definition def;

                    def.meaning = line.substr(1);
                    getline(wfin, line);
                    while (line.size() != 1) {
                        if (line[0] == L'=') {
                            wcout << line[0] << endl;
                            def.examples.push_back(line.substr(1));
                            getline(wfin, line);

                        }
                        else break;
                    }

                    wordtype.definition.push_back(def);
                    cur.worddef.push_back(wordtype);
                }
                else if (line[0] == L'/'|| line[0]==L'?'|| iswalpha(line[0]) ){
                    getline(wfin, line);
                }
                else break;

            }
            Vdictionary.push_back(cur);
           
        }

    }
    wfin.close();
    return Vdictionary;
}
#endif //CS163_GROUP9_WORD_H
