//
// Created by dirii on 28/7/23.
//
#ifndef WORD_CPP
#define WORD_CPP
#include "Word.h"
#include <iostream>
void writeStringVectorToFile(const std::vector<std::wstring>& strings, std::ofstream& outputFile) {
    size_t vectorSize = strings.size();
    outputFile.write(reinterpret_cast<const char*>(&vectorSize), sizeof(size_t));

    for (const std::wstring& str : strings) {
        size_t strSize = str.size();
        outputFile.write(reinterpret_cast<const char*>(&strSize), sizeof(size_t));
        outputFile.write(reinterpret_cast<const char*>(str.c_str()), strSize * sizeof(wchar_t));
    }
}
vector<wstring> readStringVectorFromFile(vector<wstring>& strings, ifstream& inputFile) {


    size_t vectorSize;
    inputFile.read(reinterpret_cast<char*>(&vectorSize), sizeof(size_t));

    for (size_t i = 0; i < vectorSize; ++i) {
        size_t strSize;
        inputFile.read(reinterpret_cast<char*>(&strSize), sizeof(size_t));

        wstring str;
        str.resize(strSize);
        inputFile.read(reinterpret_cast<char*>(&str[0]), strSize * sizeof(wchar_t));

        strings.push_back(str);
    }
    return strings;
}
void writetobinaryfile(vector<Word>Vdictionary, const string &filename){
    ofstream wfout(filename, ios::out | ios::binary);
    size_t dic_size = Vdictionary.size();
    wfout.write(reinterpret_cast<const char*> (&dic_size), sizeof(size_t));
    for (const Word wordd : Vdictionary) {
        size_t word_size = wordd.word.size();
        wfout.write(reinterpret_cast<const char*>(&word_size), sizeof(size_t));
        wfout.write(reinterpret_cast<const char*>(&wordd.word[0]), word_size*sizeof(wchar_t));
        // pronounce
        size_t pronounce_size = wordd.pronounce.size();
        wfout.write(reinterpret_cast<const char*>(&pronounce_size), sizeof(size_t));
        wfout.write(reinterpret_cast<const char*>(&wordd.pronounce[0]), pronounce_size * sizeof(wchar_t));


        //word def vector
        size_t def_size = wordd.worddef.size();
        wfout.write(reinterpret_cast<const char*> (&def_size), sizeof(size_t));
        for (const Type def : wordd.worddef) {
            size_t type_size = def.type.size();
            wfout.write(reinterpret_cast<const char*> (&type_size), sizeof(size_t));
            wfout.write(reinterpret_cast<const char*>(&def.type[0]), type_size * sizeof(wchar_t));

            // definition
            size_t defi_size = def.definition.size();
            wfout.write(reinterpret_cast<const char*> (&defi_size), sizeof(size_t));
            
            for (const Definition defi : def.definition) {
                size_t meaning_size = defi.meaning.size();
                wfout.write(reinterpret_cast<const char*> (&meaning_size), sizeof(size_t));
                wfout.write(reinterpret_cast<const char*>(&defi.meaning[0]), meaning_size * sizeof(wchar_t));
                writeStringVectorToFile(defi.examples, wfout);
            
            }
            size_t phrase_size = def.phrase.size();
            wfout.write(reinterpret_cast<const char*> (&phrase_size), sizeof(size_t));
            wfout.write(reinterpret_cast<const char*>(&def.phrase[0]), phrase_size * sizeof(wchar_t));
        }



    }




    wfout.close();
}

void readbinaryfile(vector<Word>& Vdictionary, const string &filename) {
    ifstream wfin(filename, ios::binary | ios::in);

    size_t dic_size;
    wfin.read(reinterpret_cast<char*> (&dic_size), sizeof(size_t));
    for (size_t i = 0; i < dic_size; i++) {
       
        size_t word_size;
        wstring word;
        Word wordd;
        wfin.read(reinterpret_cast<char*>(&word_size), sizeof(size_t));
        wordd.word.resize(word_size);
        wfin.read(reinterpret_cast<char*>(&wordd.word[0]), word_size * sizeof(wchar_t));

        // pronounce
        size_t pronounce_size;
        wfin.read(reinterpret_cast<char*>(&pronounce_size), sizeof(size_t));
        wordd.pronounce.resize(pronounce_size);
        wfin.read(reinterpret_cast<char*>(&wordd.pronounce[0]), pronounce_size * sizeof(wchar_t));


        //word def vector
        size_t def_size;
        wfin.read(reinterpret_cast<char*> (&def_size), sizeof(size_t));

        for (size_t j = 0; j < def_size; j++) {
            Type def;
            size_t type_size;
            wfin.read(reinterpret_cast<char*> (&type_size), sizeof(size_t));
            def.type.resize(type_size);
            wfin.read(reinterpret_cast<char*>(&def.type[0]), type_size * sizeof(wchar_t));

            // definition
            size_t defi_size;
            wfin.read(reinterpret_cast<char*> (&defi_size), sizeof(size_t));

            for (int z = 0; z < defi_size; z++) {
                size_t meaning_size;
                Definition defi;
                wfin.read(reinterpret_cast<char*> (&meaning_size), sizeof(size_t));
                defi.meaning.resize(meaning_size);
                wfin.read(reinterpret_cast<char*>(&defi.meaning[0]), meaning_size * sizeof(wchar_t));
                defi.examples = readStringVectorFromFile(defi.examples, wfin);

                def.definition.push_back(defi);
            }
            size_t phrase_size;
            wfin.read(reinterpret_cast<char*> (&phrase_size), sizeof(size_t));
            def.phrase.resize(phrase_size);
            wfin.read(reinterpret_cast<char*>(&def.phrase[0]), phrase_size * sizeof(wchar_t));

            wordd.worddef.push_back(def);
        }


        Vdictionary.push_back(wordd);
    }




    wfin.close();
}
#endif //WORD_CPP