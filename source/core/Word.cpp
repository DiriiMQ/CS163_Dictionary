//
// Created by dirii on 28/7/23.
//
#ifndef WORD_CPP
#define WORD_CPP
#include "Word.h"
#include <iostream>
void writeStringVectorToFile(const std::vector<std::wstring>& strings, ofstream& outputFile) {
    int vectorSize = strings.size();
    outputFile.write(reinterpret_cast<const char*>(&vectorSize), sizeof(int));

    for (const std::wstring& str : strings) {
        int strSize = str.size();
        outputFile.write(reinterpret_cast<const char*>(&strSize), sizeof(int));
        outputFile.write(reinterpret_cast<const char*>(str.c_str()), strSize * sizeof(wchar_t));
    }
}
void readStringVectorFromFile(vector<wstring>& strings, ifstream& inputFile) {
    int vectorSize;
    inputFile.read(reinterpret_cast<char*>(&vectorSize), sizeof(int));

    for (int i = 0; i < vectorSize; ++i) {
        int strSize;
        inputFile.read(reinterpret_cast<char*>(&strSize), sizeof(int));

        wstring str;
        str.resize(strSize);
        inputFile.read(reinterpret_cast<char*>(&str[0]), strSize * sizeof(wchar_t));
        strings.push_back(str);
    }
}
void writetobinaryfile(vector<Word> &Vdictionary,const string& filename) {
    ofstream wfout(filename, ios::out | ios::binary);
    int dic_size = Vdictionary.size();
  
    wfout.write(reinterpret_cast<const char*> (&dic_size), sizeof(int));
    for (const Word wordd : Vdictionary) {
        
        int word_size = wordd.word.size();
        wfout.write(reinterpret_cast<const char*>(&word_size), sizeof(int));
        wfout.write(reinterpret_cast<const char*>(&wordd.word[0]), word_size*sizeof(wchar_t));
        // pronounce
        int pronounce_size = wordd.pronounce.size();
        wfout.write(reinterpret_cast<const char*>(&pronounce_size), sizeof(int));
        wfout.write(reinterpret_cast<const char*>(&wordd.pronounce[0]), pronounce_size * sizeof(wchar_t));

        bool isType = wordd.IsType;
       
        wfout.write(reinterpret_cast<const char*>(&isType), sizeof(bool));
        //word def vector
        if (wordd.IsType)
        {
           
            int def_size = wordd.worddef.size();
            wfout.write(reinterpret_cast<const char*> (&def_size), sizeof(int));
            for (const Type def : wordd.worddef) {
                int type_size = def.type.size();
                wfout.write(reinterpret_cast<const char*> (&type_size), sizeof(int));
                wfout.write(reinterpret_cast<const char*>(&def.type[0]), type_size * sizeof(wchar_t));

                bool Isdefinition = def.Isdefinition;
                wfout.write(reinterpret_cast<const char*>(&Isdefinition), sizeof(bool));
                // definition
                if (def.Isdefinition)
                {

                    int defi_size = def.definition.size();
                    wfout.write(reinterpret_cast<const char*> (&defi_size), sizeof(int));

                    for (const Definition defi : def.definition) {
                        int meaning_size = defi.meaning.size();
                        wfout.write(reinterpret_cast<const char*> (&meaning_size), sizeof(int));
                        wfout.write(reinterpret_cast<const char*>(&defi.meaning[0]), meaning_size * sizeof(wchar_t));
                        bool Isexample = defi.Isexample;
                        wfout.write(reinterpret_cast<const char*>(&Isexample), sizeof(bool));
                        if(defi.Isexample)
                            writeStringVectorToFile(defi.examples, wfout);

                    }
                    int phrase_size = def.phrase.size();
                    wfout.write(reinterpret_cast<const char*> (&phrase_size), sizeof(int));
                    wfout.write(reinterpret_cast<const char*>(&def.phrase[0]), phrase_size * sizeof(wchar_t));
                }
            }
        }

    }
    wfout.close();
}
void readbinaryfile(vector<Word> &Vdictionary,const string&filename) {
    ifstream wfin(filename, ios::binary | ios::in);
    if (!wfin) {
        return;
    }
    int dic_size;
    wfin.read(reinterpret_cast<char*> (&dic_size), sizeof(int));
    
    for (int i = 0; i < dic_size;i++) {
        int word_size ;
        wstring word;
        Word wordd ;
        wfin.read(reinterpret_cast<char*>(&word_size), sizeof(int));
        wordd.word.resize(word_size);
        
        wfin.read(reinterpret_cast<char*>(&wordd.word[0]), word_size * sizeof(wchar_t));
       
        // pronounce
        int pronounce_size;
        wfin.read(reinterpret_cast<char*>(&pronounce_size), sizeof(int));
        wordd.pronounce.resize(pronounce_size);
       
        wfin.read(reinterpret_cast<char*>(&wordd.pronounce[0]), pronounce_size * sizeof(wchar_t));
        
        

        //word def vector
        wfin.read(reinterpret_cast<char*>(&wordd.IsType), sizeof(bool));
        
        if (wordd.IsType) {
            int def_size;
            wfin.read(reinterpret_cast<char*> (&def_size), sizeof(int));

            for (int j = 0; j < def_size; j++) {
                Type def;

                
                if (wordd.IsType) {
                    int type_size;
                    wfin.read(reinterpret_cast<char*> (&type_size), sizeof(int));
                    def.type.resize(type_size);
                    wfin.read(reinterpret_cast<char*>(&def.type[0]), type_size * sizeof(wchar_t));

                    // definition
                    wfin.read(reinterpret_cast<char*>(&def.Isdefinition), sizeof(bool));
                    if (def.Isdefinition) {
                        int defi_size;
                        wfin.read(reinterpret_cast<char*> (&defi_size), sizeof(int));

                        for (int z = 0; z < defi_size; z++) {
                            int meaning_size;
                            Definition defi;
                            wfin.read(reinterpret_cast<char*> (&meaning_size), sizeof(int));
                            defi.meaning.resize(meaning_size);
                            wfin.read(reinterpret_cast<char*>(&defi.meaning[0]), meaning_size * sizeof(wchar_t));

                            wfin.read(reinterpret_cast<char*>(&defi.Isexample), sizeof(bool));
                            if (defi.Isexample)
                                readStringVectorFromFile(defi.examples, wfin);

                            def.definition.push_back(defi);
                        }
                        int phrase_size;
                        wfin.read(reinterpret_cast<char*> (&phrase_size), sizeof(int));
                        def.phrase.resize(phrase_size);
                        wfin.read(reinterpret_cast<char*>(&def.phrase[0]), phrase_size * sizeof(wchar_t));

                        wordd.worddef.push_back(def);
                    }
                }
            }


            Vdictionary.push_back(wordd);
           
        }
    }




    wfin.close();
}


void Word::setData(std::wstring word, std::wstring definition, std::wstring example, std::wstring phrase,std::wstring type)
{
    this->word=word;
    this->IsType=true;
    Type type1;
    Definition def;
    def.Isexample= true;
    type1.Isdefinition=true;

    type1.type=type;
    type1.phrase=phrase;
    def.meaning= definition;
    def.examples.push_back(example);
    type1.definition.push_back(def);
    this->worddef.push_back(type1);
}


vector<wstring> loadimagepath(vector<Word> dic){
    vector<wstring> final;
    for(int i=0;i<dic.size();i++){
        wstring b= L"../../../assets/components/"+dic[i].word + L".png";
        final.push_back(b);

    }
    return final;
}
#endif //WORD_CPP