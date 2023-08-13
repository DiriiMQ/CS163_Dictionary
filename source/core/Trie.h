#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <wchar.h>
#include <vector>
#include <set>
#include "Map.hpp"
#include <time.h>
#include <cstdlib>
using namespace std;
//mapping a wstring to a ValueType using trie
template < typename ValueType >
struct TrieNode{
    ValueType value;
    Map < wchar_t , TrieNode * > children;
    bool isEndOfWord;
    int wordCount;
    TrieNode (const ValueType &value = ValueType());
};

template < typename ValueType >
struct Trie{
private:
    int randomNumber(int range) const ;
    TrieNode < ValueType > *root;
    void getAll(TrieNode < ValueType > *current , wstring &key , vector < pair < wstring , ValueType > > &result) const ;
    int WordCount = 0;
    void removeHelper(TrieNode < ValueType > *current);
    void getAllConstRefHelper(TrieNode < ValueType > *current , wstring &key , vector < pair < const wstring , const ValueType& > > &result) const ;
    void getAutoCompleteList(TrieNode < ValueType > *current , wstring &key , vector < wstring > &result);
    int getAutoCompleteHelper(wstring &key , TrieNode < ValueType > *root , vector < wstring > &result);
    void insert(const wstring &key);
public:
    int size() const ;
    Trie(const Trie &other);
    Trie();
    Trie(Trie &&other);
    Trie &operator = (const Trie &other);
    Trie &operator = (Trie &&other);
    ~Trie();
    // nhận vào 1 wstring key, return true nếu key có trong trie, false nếu ngược lại
    bool find(const wstring &key);
    // nhận vào 1 wstring key, return value tương ứng với key đó
    ValueType &operator[](const wstring &key);
    // nhận vào 1 wstring key, xóa key đó khỏi trie
    void remove(const wstring &key);
    // return vector chứa tất cả các cặp <key, value> trong trie
    vector < pair < wstring , ValueType > > getAll() const ;
    const vector < pair < const wstring, const ValueType& > > getAllConstRef() const ;
    // nhập vào 1 key, return value (definition ở dạng set <wstring>))
    ValueType search(const wstring& searchedWord);
    bool empty() const ;
    const pair < wstring, const ValueType& > getRandom() const ;
    // 0 mean no word found with that key
    //-1 mean no word found with that key but there are words that start with that key
    // 1 mean there is a word with that key
    int getAutoComplete(wstring &key, vector < wstring > &result);
    void clear();
};
#include "Trie.cpp"
#endif //TRIE_H