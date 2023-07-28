//
// Created by dirii on 29/7/23.
//

#ifndef CS163_GROUP9_UTILS_H
#define CS163_GROUP9_UTILS_H

#include <string>
#include <locale>       // For std::wstring_convert
#include <codecvt>      // For std::codecvt_utf8

namespace Utils {
    static std::string WStringToUTF8(const std::wstring &wstr) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }
};
#endif //CS163_GROUP9_UTILS_H
