//Author: codeforces.com/profile/20.21.14.07
#ifndef TRIE_CPP
#define TRIE_CPP
#include "Trie.h"
#include <functional>

// Trie node
template < typename ValueType >
TrieNode < ValueType > ::TrieNode(const ValueType &value) : value(value), isEndOfWord(false), wordCount(0) {}

// Trie
template < typename ValueType >
Trie < ValueType > ::Trie() : root(new TrieNode < ValueType > ()) {}

template < typename ValueType >
Trie < ValueType > ::Trie(Trie &&other) : root(other.root) {
    other.root = nullptr;
    WordCount = other.WordCount;
}

template < typename ValueType >
Trie < ValueType > ::~Trie() {
    removeHelper(root);
}
template < typename ValueType >
void Trie < ValueType > ::clear() {
    removeHelper(root);
    WordCount = 0;
}

template < typename ValueType >
Trie < ValueType > &Trie < ValueType > ::operator = (const Trie &other) {
    if (this == &other) return *this;
    removeHelper(root);
    root = new TrieNode < ValueType > ();
    vector < pair < wstring , ValueType > > temp = other.getAll();
    for (int i = 0 ; i < temp.size() ; i++) {
        operator[](temp[i].first) = temp[i].second;
    }
    WordCount = other.WordCount;
    return *this;
}

template < typename ValueType >
Trie < ValueType > &Trie < ValueType > ::operator = (Trie &&other) {
    if (this == &other) return *this;
    removeHelper(root);
    root = other.root;
    other.root = nullptr;
    WordCount = other.WordCount;
    return *this;
}

template < typename ValueType >
bool Trie < ValueType > ::find(const wstring &key) {
    TrieNode < ValueType > *current = root;
    for (auto &c : key) {
        if (!current->children.find(c)) {
            return false;
        }
        current = current->children[c];
    }
    return current->isEndOfWord;
}
//Trie<int> a;
//a[wstring] = int;
template < typename ValueType >
ValueType &Trie < ValueType > ::operator[](const wstring &key) {
    insert(key);
    TrieNode < ValueType > *current = root;
    for (auto &c : key) {
        if (!current->children.find(c)) {
            current->children[c] = new TrieNode < ValueType > ();
        }
        current = current->children[c];
    }
    if (!current->isEndOfWord) {
        WordCount++;
    }
    current->isEndOfWord = true;
    return current->value;
}

template < typename ValueType >
void Trie < ValueType > ::remove(const wstring &key) {
    if (!find(key)) return;
    TrieNode < ValueType > *current = root;
    current->wordCount--;
    for (auto &c : key) {
        if (!current->children.find(c)) {
            return;
        }
        if (current->children[c]->wordCount == 1) {
            removeHelper(current->children[c]);
            current->children.remove(c);
            return;
        }
        current = current->children[c];
        current->wordCount--;
    }
    current->isEndOfWord = false;
    WordCount--;
}

template < typename ValueType >
void Trie < ValueType > ::getAll(TrieNode < ValueType > *current , wstring &key , vector < pair < wstring , ValueType > > &result) const {
    if (current->isEndOfWord) {
        result.push_back(make_pair(key , current->value));
    }
    auto children = current->children.getAll();
    for (auto &child : children) {
        key.push_back(child.first);
        getAll(child.second , key , result);
        key.pop_back();
    }
}

template < typename ValueType >
vector < pair < wstring, ValueType > > Trie < ValueType > ::getAll() const {
    vector < pair < wstring , ValueType > > result;
    wstring key;
    getAll(root , key , result);
    return result;
}

//Users can search for a keyword.
template <typename ValueType>
ValueType Trie<ValueType>::search(const wstring& searchedWord) {
    TrieNode<ValueType>* current = root;
    for (char c : searchedWord) {
        if (!current->children.find(c)) {
            // Key does not exist in the trie, return a default value.
            return ValueType();
        }
        current = current->children[c];
    }
    // Searched word found, save it to a file
   // saveHistory(searchedWord);

    // Return the value of the last node representing the searched word.
    return current->value;
}
template < typename ValueType >
int Trie < ValueType > ::size() const {
    return WordCount;
}
template < typename ValueType >
bool Trie < ValueType > ::empty() const {
    return WordCount == 0;
}
template < typename ValueType >
Trie < ValueType > ::Trie(const Trie &other) {
    root = new TrieNode < ValueType > ();
    vector < pair < wstring , ValueType > > temp = other.getAll();
    for (int i = 0 ; i < temp.size() ; i++) {
        operator[](temp[i].first) = temp[i].second;
    }
    WordCount = other.WordCount;
}
template < typename ValueType >
void Trie < ValueType > ::removeHelper(TrieNode < ValueType > *current) {
    if (!current) return;
    auto children = current->children.getAll();
    for (auto &child : children) {
        removeHelper(child.second);
    }
    if (current->isEndOfWord) {
        WordCount--;
    }
    delete current;
}

template < typename ValueType >
void Trie < ValueType > ::getAllConstRefHelper(TrieNode < ValueType > *current , wstring &key , vector < pair < const wstring , const ValueType& > > &result) const {
    if (current->isEndOfWord) {
        result.push_back(move(make_pair(key , std::cref(current->value))));
    }
    auto children = current->children.getAll();
    for (auto &child : children) {
        key.push_back(child.first);
        getAllConstRefHelper(child.second , key , result);
        key.pop_back();
    }
}

template < typename ValueType >
const vector < pair < const wstring, const ValueType& > > Trie < ValueType > ::getAllConstRef() const {
    vector < pair < const wstring , const ValueType& > > result;
    wstring key;
    getAllConstRefHelper(root , key , result);
    return move(result);
}

template < typename ValueType >
void Trie < ValueType > ::insert(const wstring &key) {
    if (find(key)) return;
    TrieNode < ValueType > *current = root;
    current->wordCount++;
    for (auto &c : key) {
        if (!current->children.find(c)) {
            current->children[c] = new TrieNode < ValueType > ();
        }
        current = current->children[c];
        current->wordCount++;
    }
    if (!current->isEndOfWord) {
        WordCount++;
    }
    current->isEndOfWord = true;
}

template < typename ValueType >
int Trie < ValueType > ::randomNumber(int range) const {
    unsigned int temp = 0;
    for (int i = 0; i < 4; ++i){
        temp = (temp << 8) | (rand() % 256);
    }
    return temp % range;
}

template < typename ValueType >
const pair < wstring, const ValueType& > Trie < ValueType > :: getRandom() const {
    int random = randomNumber(WordCount);
    wstring key = L""; 
    TrieNode < ValueType > *current = root;
    while (random >= 0) {
        if (current->isEndOfWord) {
            random--;
        }
        if (random < 0) break;
        auto children = current->children.getAll();
        for (auto &child : children) {
            if (random < 0) break;
            if (child.second->wordCount > random) {
                current = child.second;
                key.push_back(child.first);
                break;
            }
            random -= child.second->wordCount;
        }
    }
    return make_pair(key , std::cref(current->value));
}
template < typename ValueType >
void Trie < ValueType > ::getAutoCompleteList(TrieNode < ValueType > *current , wstring &key , vector < wstring > &result) {
    if (current->isEndOfWord) {
        result.push_back(key);
    }
    auto children = current->children.getAll();
    for (auto &child : children) {
        key.push_back(child.first);
        getAutoCompleteList(child.second, key, result);
        key.pop_back();
    }
}
template < typename ValueType >
int Trie < ValueType > ::getAutoCompleteHelper(wstring &key , TrieNode < ValueType > *root , vector < wstring > &result) {
    TrieNode < ValueType > *current = root;
    for (auto &c : key) {
        if (!current->children.find(c)) {
            return 0;
        }
        current = current->children[c];
    }
    if (current->children.root==nullptr) {
        if (current->isEndOfWord) {
            result.push_back(key);
            return 1;
        } 
        return -1;
    }
    getAutoCompleteList(current, key, result);
    return 1;
}
template < typename ValueType >
int Trie < ValueType > ::getAutoComplete(wstring &key, vector < wstring > &result){
    return getAutoCompleteHelper(key, root, result);
}

#endif //STRINGMAPPING_CPP