#ifndef COMPARESTRING_H
#define COMPARESTRING_H

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
using namespace std;
int getLevenshteinDistance(const wstring &s1, const wstring &s2) {
    int **d = new int *[s1.length() + 2];
    for (int i = 0; i < s1.length(); i++) {
        d[i] = new int[s2.length() + 2];
    }
    for (int i = 0; i <= s1.length(); i++) {
        d[i][0] = i;
    }
    for (int j = 0; j <= s2.length(); j++) {
        d[0][j] = j;
    }
   
    for (int j = 1; j <= s2.length(); j++) {
        for (int i = 1; i <= s1.length(); i++) {
            d[i][j] = min({d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1])});
        }
    }
    return d[s1.length() - 1][s2.length() - 1];
}
int getWordChanges(const wstring &s1, const wstring &s2) {
    int similarityThreshold = 50;
    int wordChanges = 0;

    wstring lowercaseS1 = s1;
    wstring lowercaseS2 = s2;
    replace(lowercaseS1.begin(), lowercaseS1.end(), '.', ' ');
    replace(lowercaseS1.begin(), lowercaseS1.end(), ',', ' ');
    replace(lowercaseS1.begin(), lowercaseS1.end(), ';', ' ');
    replace(lowercaseS2.begin(), lowercaseS2.end(), '.', ' ');
    replace(lowercaseS2.begin(), lowercaseS2.end(), ',', ' ');
    replace(lowercaseS2.begin(), lowercaseS2.end(), ';', ' ');

    int pos1 = 0, pos2 = 0;

    while ((pos1 = lowercaseS1.find(' ', pos1)) != wstring::npos &&
           (pos2 = lowercaseS2.find(' ', pos2)) != wstring::npos) {
        wstring word1 = lowercaseS1.substr(0, pos1);
        wstring word2 = lowercaseS2.substr(0, pos2);

        if ((getLevenshteinDistance(word1, word2) * 100 / word1.length()) < similarityThreshold) {
            wordChanges++;
        }

        lowercaseS1.erase(0, pos1 + 1);
        lowercaseS2.erase(0, pos2 + 1);
        pos1 = pos2 = 0;
    }

    return wordChanges;
}
int GetLength(const wstring &s1, const wstring &s2){
    int c1 = s1.size();
    int c2 = s2.size();
    return abs(c1 - c2);
}
int GetWordCount(const wstring &s1, const wstring &s2){
    wstring cur;
    wstringstream ss(s1);
    int cnt1 = 0;
    while (ss >> cur) cnt1++;
    wstringstream ss2(s2);
    int cnt2 = 0;
    while (ss2 >> cur) cnt2++;
    return abs(cnt1 - cnt2);
}

#endif // COMPARESTRING_H