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

    static void formatString(std::string s, int size, int fontSize, std::vector <std::string>& result)
    {
        int i = 0;
        std::string tmp;
        std::string tmpword;
        while (i < s.length())
        {
            if (size < MeasureText(tmp.c_str(), fontSize) + MeasureText(tmpword.c_str(), fontSize))
            {
                result.push_back(tmp);
                tmp.clear();
            }
            if (s[i] == ' ')
            {
                tmp += " ";
                tmp += tmpword;
                tmpword.clear();
            }
            else if (s[i] != '\n')
                tmpword.push_back(s[i]);
            if (s[i] == '\n' || i == s.length() - 1)
            {
                result.push_back(tmp + " " + tmpword);
                tmp.clear();
                tmpword.clear();
            }
            i++;
        }
    }
};
#endif //CS163_GROUP9_UTILS_H
