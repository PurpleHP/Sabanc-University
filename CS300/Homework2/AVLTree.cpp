#ifndef AVLTREE_CPP
#define AVLTREE_CPP
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct DocumentItem {
    string documentName;
    int count;
    explicit DocumentItem(string &s): documentName(s), count(1) {}
};

struct WordItem {
    string word;
    vector<DocumentItem> details;
    explicit WordItem(string &s, DocumentItem* d): word(s) {
        details.push_back(*d);
    }
};

//Key = String, Value = WordItem

template <class Key, class Value>
class AVLSearchTree;

template <class Key, class Value>
class AvlNode
{
    Key 	key;
    Value 	value;
    AvlNode         *left;
    AvlNode   		*right;
    int        		height;

    AvlNode(const Key &theKey, const Value &theValue, AvlNode *lt, AvlNode *rt, int h = 0)
            : key(theKey), value(theValue), left(lt), right(rt), height(h) { }

    friend class AVLSearchTree<Key, Value>;
};


template <class Key, class Value>
class AVLSearchTree
{
public:
    explicit AVLSearchTree(): ITEM_NOT_FOUND("!"){
        root = nullptr;
    }

    AVLSearchTree( const AVLSearchTree & rhs )
    :root( nullptr ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ){
        *this = rhs;
    }

    ~AVLSearchTree( ){
        makeEmpty( );
    }

    const Key &find( const Key & x ) const{
        return elementAt( find( x, root ) );
    }

    [[nodiscard]]bool isEmpty( ) const{
        return root == nullptr;
    }
    void printTree( ) const{
        if(isEmpty()){
            cout << "AVL Tree is empty" << endl;
        }
        else{
            printTree(root);
        }
    }

    Value getDetails(const Key &key){
        return find(key, root)->value;
    }

    void makeEmpty() {
        makeEmpty(root);
    }
    void insert(const Key & x, Value value) {
        insert(x, value, root);
    }
    void remove(const Key & x) {
        remove(x, root);
    }

    int height( AvlNode<Key, Value> *t ) const{
        return t == nullptr ? -1 : t->height;
    }

    //const AVLSearchTree & operator=( const Key & rhs );

private:
    AvlNode<Key, Value> *root;
    const Key ITEM_NOT_FOUND;

    const Key & elementAt( AvlNode<Key, Value> *t ) const{
        return t == nullptr ? ITEM_NOT_FOUND : t->key;
    }

    AvlNode<Key, Value> * remove(const Key & key, AvlNode<Key, Value> * & t) {
        if(t == nullptr){
            return t;
        }
        if(key < t->key){
            t->left = remove(key, t->left);
        }
        else if(t->key < key){
            t->right = remove(key, t->right);
        }
        else{ //Match
            if(t->left == nullptr || t->right == nullptr){
                AvlNode<Key, Value> *temp = t->left ? t->left : t->right;
                if(temp == nullptr){
                    temp = t;
                    t = nullptr;
                }
                else{
                    *t = *temp;
                }
                delete temp;
            }
            else{
                AvlNode<Key, Value>* temp = findMin(t->right);
                t->key = temp->key;
                t->right = remove(temp->key, t->right);
            }
        } //Balance the tree
        if(t == nullptr){
            return t;
        }
        t->height = 1 + max(height(t->left), height(t->right));
        int balance = height(t->left) - height(t->right); //Check if the tree is unbalanced
        if(balance > 1){ //Left heavy
            if(height(t->left->left) >= height(t->left->right)){
                rotateWithLeftChild(t);
            }
            else{
                doubleWithLeftChild(t);
            }
        }
        else if(balance < -1){ //Right heavy
            if(height(t->right->right) >= height(t->right->left)){
                rotateWithRightChild(t);
            }
            else{
                doubleWithRightChild(t);
            }
        }
        return t;
    }

    AvlNode<Key, Value> * findMin( AvlNode<Key, Value> *t ) const{
        if(t != nullptr){
            while(t->left != nullptr){
                t = t->left;
            }
        }
        return t;
    }

    AvlNode<Key, Value> * findMax( AvlNode<Key, Value> *t ) const{
        if(t != nullptr){
            while(t->right != nullptr){
                t = t->right;
            }
        }
        return t;
    }

    AvlNode<Key, Value> * find( const Key & x, AvlNode<Key, Value> *t )const{
        while( t != nullptr )
            if( x < t->key )
                t = t->left;
            else if( t->key < x )
                t = t->right;
            else
                return t;    // Match

        return nullptr;   // No match

    }
    void makeEmpty(AvlNode<Key, Value> * & t) const {
        if(t != nullptr){
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    //For testing purposes
    void printTree( AvlNode<Key, Value> *t ) const{
        if(t != nullptr){
            printTree(t->left);
            cout << t->key;
            for(int i = 0; i < t->value->details.size(); i++){
                cout << " " << t->value->details[i].documentName << " " << t->value->details[i].count;
            }
            cout << endl;
            printTree(t->right);
        }
    }

    [[nodiscard]] int max( int lhs, int rhs ) const {
        return lhs > rhs ? lhs : rhs;
    }

    void insert(const Key & key, Value value, AvlNode<Key, Value> * & t) {
        if(t == nullptr){
            t = new AvlNode<Key, Value>(key, value, nullptr, nullptr);
        }
        else if(key < t->key){
            insert(key, value, t->left);
            if(height(t->left) - height(t->right) == 2){
                if(key < t->left->key){
                    rotateWithLeftChild(t);
                }
                else{
                    doubleWithLeftChild(t);
                }
            }
        }
        else if(t->key < key){
            insert(key, value, t->right);
            if(height(t->right) - height(t->left) == 2){
                if(t->right->key < key){
                    rotateWithRightChild(t);
                }
                else{
                    doubleWithRightChild(t);
                }
            }
        }
        else { // Duplicate, so we don't insert instead we update
            for(int j = 0; j < value->details.size(); j++){
                bool found = false;
                for(int i = 0; i < t->value->details.size(); i++){ //Updates the count since we know this key exists
                    if(t->value->details[i].documentName == value->details[j].documentName){
                        t->value->details[i].count++;
                        found = true;
                        break;
                    }
                }
                if (!found) { // If the document was not found in the existing details, add it
                    t->value->details.push_back(value->details[j]);
                }
            }
        }
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    //ROTATIONS
    void rotateWithLeftChild( AvlNode<Key, Value> * & k2 ) const{
        AvlNode<Key, Value> *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }
    void rotateWithRightChild( AvlNode<Key, Value> * & k1 ) const{
        AvlNode<Key, Value> *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }
    void doubleWithLeftChild( AvlNode<Key, Value> * & k3 ) const{
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }
    void doubleWithRightChild( AvlNode<Key, Value> * & k1 ) const{
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};

#endif //AVLTREE_CPP
