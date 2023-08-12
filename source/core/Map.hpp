//Author : codeforces.com/profile/20.21.14.07
#ifndef MAP_HPP
#define MAP_HPP
#include <vector>
using namespace std;
template < typename keyType, typename valueType >
struct Map{
    struct Node{
        keyType key;
        valueType value;
        Node *left, *right;
        int height;
        Node(const keyType &key = keyType(), const valueType &value = valueType()) : key(key), value(value), left(nullptr), right(nullptr), height(1) {}
    };
    Node *root;
    Map() : root(nullptr) {}
    void Copy(Node*&root, const Node *&Other){
        if (Other){
            root = new Node(Other.key,Other.value);
            Copy(root->left,Other->left);
            Copy(root->right,Other->right);
        } else root = nullptr;
    }
    Map(const Map& Other){
        Copy(root,Other.root);
    }
    Map(Map &&Other){
        root = Other.root;
        Other.root = nullptr;
    }
    Map &operator = (const Map& Other){
        if (this == &Other) return *this;
        Destructor(root);
        root = nullptr;
        Copy(root,Other.root);
        return *this;
    }
    Map &operator = (Map &&Other){
        if (this == &Other) return *this;
        Destructor(root);
        root = Other.root;
        Other.root = nullptr;
        return *this;
    }
    void Destructor(Node *root){
        if (root) {
            Destructor(root->left); 
            Destructor(root->right);
            delete root; 
        }
    }
    ~Map(){
        Destructor(root);
    }
    
    int getHeight(Node *node){
        return node ? node->height : 0;
    }
    void updateHeight(Node *node){
        if (node){
            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        }
    }
    Node* rotateLeft(Node *node){
        Node *temp = node->right;
        node->right = temp->left;
        temp->left = node;
        updateHeight(node);
        updateHeight(temp);
        return temp;
    }
    Node *rotateRight(Node *node){
        Node *temp = node->left;
        node->left = temp->right;
        temp->right = node;
        updateHeight(node);
        updateHeight(temp);
        return temp;
    }
    Node *reBalance(Node *node){
        if (!node) return node;
        updateHeight(node);
        if (getHeight(node->left) - getHeight(node->right) > 1){
            if (getHeight(node->left->left) < getHeight(node->left->right)){
                node->left = rotateLeft(node->left);
            }
            node = rotateRight(node);
        }
        else if (getHeight(node->right) - getHeight(node->left) > 1){
            if (getHeight(node->right->right) < getHeight(node->right->left)){
                node->right = rotateRight(node->right);
            }
            node = rotateLeft(node);
        }
        return node;
    }
    Node *insertHelper(Node *node, const keyType &key, const valueType &value){
        if (!node) return new Node(key, value);
        if (key < node->key){
            node->left = insertHelper(node->left, key, value);
        }
        else if (key > node->key){
            node->right = insertHelper(node->right, key, value);
        }
        else{
            node->value = value;
        }
        return reBalance(node);
    }
    void insert(const keyType &key, const valueType &value){
        root = insertHelper(root, key, value);
    }
    Node *removeHelper(Node *node, const keyType &key){
        if (!node) return node;
        if (node->key == key){
            if (!node->left && !node->right){
                delete node;
                return nullptr;
            }
            else if (!node->left){
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right){
                Node *temp = node->left;
                delete node;
                return temp;
            }
            else{
                Node *temp = node->right;
                while (temp->left){
                    temp = temp->left;
                }
                node->key = temp->key;
                node->value = temp->value;
                node->right = removeHelper(node->right, temp->key);
            }
        }
        else if (key < node->key){
            node->left = removeHelper(node->left, key);
        }
        else{
            node->right = removeHelper(node->right, key);
        }
        return reBalance(node);
    }
    void remove(const keyType &key){
        root = removeHelper(root, key);
    }
    bool find(const keyType &key){
        Node *temp = root;
        while (temp){
            if (temp->key == key){
                return true;
            }
            else if (key < temp->key){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
        }
        return false;
    }
    valueType &operator[](const keyType &key){
        Node *temp = root;
        while (temp){
            if (temp->key == key){
                return temp->value;
            }
            else if (key < temp->key){
                temp = temp->left;
            }
            else{
                temp = temp->right;
            }
        }
        insert(key, valueType());
        return operator[](key);
    }

    void getAllHelper(Node *node, vector < pair < keyType, valueType > > &result){
        if (!node) return;
        getAllHelper(node->left, result);
        result.push_back(make_pair(node->key, node->value));
        getAllHelper(node->right, result);
    }

    vector < pair < keyType, valueType > > getAll(){
        vector < pair < keyType, valueType > > result;
        getAllHelper(root, result);
        return move(result);
    }
};

#endif //MAP_HPP