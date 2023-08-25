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
/**
 * @brief Class TrieNode
 * 
 */
template < typename ValueType >
struct TrieNode{
    ValueType value;
    Map < wchar_t , TrieNode * > children;
    bool isEndOfWord;
    int wordCount;
    TrieNode (const ValueType &value = ValueType());
};
/**
 * @brief Class Trie
 * 
 */
template < typename ValueType >
struct Trie{
private:
/**
 * @brief get random number
 * 
 */
    int randomNumber(int range) const ;
    TrieNode < ValueType > *root;
/**
 * @brief get all value of Trie
 * 
 */
    void getAll(TrieNode < ValueType > *current , wstring &key , vector < pair < wstring , ValueType > > &result) const ;
    int WordCount = 0;
/**
 * @brief Recursion for remove
 * 
 */
    void removeHelper(TrieNode < ValueType > *current);
/**
 * @brief Recursion for get all
 * 
 */
    void getAllConstRefHelper(TrieNode < ValueType > *current , wstring &key , vector < pair < const wstring , const ValueType& > > &result) const ;
/**
 * @brief Recursion for Auto Complete
 * 
 */ 
    void getAutoCompleteList(TrieNode < ValueType > *current , wstring &key , vector < wstring > &result);
/**
 * @brief Get Auto Complete
 * 
 */
    int getAutoCompleteHelper(wstring &key , TrieNode < ValueType > *root , vector < wstring > &result);
/**
 * @brief Insert a key
 * 
 */
    void insert(const wstring &key);
public:
/**
 * @brief Get size of Trie
 * 
 */
    int size() const ;
    Trie(const Trie &other);
/**
 * @brief Constructor
 * 
 */
    Trie();
    Trie(Trie &&other);
/**
 * @brief Operator for copy and move
 * 
 */
    Trie &operator = (const Trie &other);
    Trie &operator = (Trie &&other);
/**
 * @brief Destructor
 * 
 */
    ~Trie();
/**
 * @brief Check a key if it exist in Trie
 * 
 */
    bool find(const wstring &key);
/**
 * @brief Get value of key by operator
 * 
 */
    ValueType &operator[](const wstring &key);
/**
 * @brief Remove a key from Trie
 * 
 */
    void remove(const wstring &key);
/**
 * @brief Get all key and value
 * 
 */
    vector < pair < wstring , ValueType > > getAll() const ;
    const vector < pair < const wstring, const ValueType& > > getAllConstRef() const ;
/**
 * @brief Get value of key
 * 
 */
    ValueType search(const wstring& searchedWord);
/**
 * @brief Check if Trie if empty
 * 
 */
    bool empty() const ;
/**
 * @brief Get random string in Trie
 * 
 */
    const pair < wstring, const ValueType& > getRandom() const ;
    // 0 mean no word found with that key
    //-1 mean no word found with that key but there are words that start with that key
    // 1 mean there is a word with that key
/**
 * @brief Get auto complete
 * 
 */
    int getAutoComplete(wstring &key, vector < wstring > &result);
/**
 * @brief Clear trie
 * 
 */
    void clear();
};
#include "Trie.cpp"
#endif //TRIE_H