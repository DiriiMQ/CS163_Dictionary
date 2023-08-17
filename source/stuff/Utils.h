//
// Created by dirii on 29/7/23.
//

#ifndef CS163_GROUP9_UTILS_H
#define CS163_GROUP9_UTILS_H

#include <string>
#include <locale>       // For std::wstring_convert
#include <codecvt>      // For std::codecvt_utf8
#include <vector>

namespace Utils {
    static std::string WStringToUTF8(const std::wstring &wstr) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }

    
    static std::wstring UTF8ToWString(const std::string &str) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wstr = converter.from_bytes(str);
        return wstr;
    }

    static void formatString(Font *font, float spacing, std::string s, float size, float fontSize, std::vector <std::string>& result)
    {
        std::string currentLines, currentWord;
        while(s.back() == ' ' || s.back() == '\n') s.pop_back();
        s.push_back('\n');
        for (auto i : s) {
            if (i == '\n') {
                if (MeasureTextEx(*font, currentLines.c_str(), fontSize, spacing).x +
                    MeasureTextEx(*font, currentWord.c_str(), fontSize, spacing).x > size) {
                    result.push_back(currentLines);
                    currentLines = currentWord;
                } else
                    currentLines += " " + currentWord;
                result.push_back(currentLines);
                currentLines.clear();
                currentWord.clear();
            } else if (i == ' ') {
                if (MeasureTextEx(*font, currentLines.c_str(), fontSize, spacing).x +
                    MeasureTextEx(*font, currentWord.c_str(), fontSize, spacing).x > size) {
                    result.push_back(currentLines);
                    currentLines = currentWord;
                    currentWord.clear();
                } else {
                    currentLines += " " + currentWord;
                    currentWord.clear();
                }
            } else {
                currentWord.push_back(i);
            }
        }

//        int i = 0;
//        std::string tmp;
//        std::string tmpword;
//        while (i < s.length())
//        {
//            if (size <
//                    MeasureTextEx(*font, tmp.c_str(), fontSize, spacing).x +
//                    MeasureTextEx(*font, tmpword.c_str(), fontSize, spacing).x
//            ){
//                result.push_back(tmp);
//                tmp.clear();
//            }
//            if (s[i] == ' ')
//            {
//                tmp += " ";
//                tmp += tmpword;
//                tmpword.clear();
//            }
//            else if (s[i] != '\n')
//                tmpword.push_back(s[i]);
//            if (s[i] == '\n' || i == s.length() - 1)
//            {
//                result.push_back(tmp + " " + tmpword);
//                tmp.clear();
//                tmpword.clear();
//            }
//            i++;
//        }
    }
};
#endif //CS163_GROUP9_UTILS_H
