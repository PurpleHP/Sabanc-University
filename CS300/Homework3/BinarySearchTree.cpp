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
class BinarySearchTree;

template <class Key, class Value>
class AvlNode
{
    Key 	key;
    Value 	value;
    AvlNode         *left;
    AvlNode   		*right;

    AvlNode(const Key &theKey, const Value &theValue, AvlNode *lt, AvlNode *rt)
            : key(theKey), value(theValue), left(lt), right(rt) { }

    friend class BinarySearchTree<Key, Value>;
};


template <class Key, class Value>
class BinarySearchTree
{
public:
    explicit BinarySearchTree(): ITEM_NOT_FOUND("!"){
        root = nullptr;
    }

    ~BinarySearchTree( ){
        makeEmpty( );
    }

    const Key &find( const Key & x ) const{
        return elementAt( find( x, root ) );
    }

    void makeEmpty() {
        makeEmpty(root);
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

    void insert(const Key & x, Value value) {
        insert(x, value, root);
    }

private:
    AvlNode<Key, Value> *root;
    const Key ITEM_NOT_FOUND;

    const Key & elementAt( AvlNode<Key, Value> *t ) const{
        return t == nullptr ? ITEM_NOT_FOUND : t->key;
    }

    void makeEmpty(AvlNode<Key, Value> * & t) const {
        if(t != nullptr){
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
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


    void insert(const Key & key, Value value, AvlNode<Key, Value> * & t) {
        if(t == nullptr){
            t = new AvlNode<Key, Value>(key, value, nullptr, nullptr);
        }
        else if(key < t->key){
            insert(key, value, t->left);
        }
        else if(t->key < key){
            insert(key, value, t->right);
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
    }
};

#endif //AVLTREE_CPP
