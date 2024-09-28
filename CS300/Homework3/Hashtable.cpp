#ifndef HASHTABLE_CPP
#define HASHTABLE_CPP
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


//Key = String, Value = WordItem
template <class Key, class Value>
class HashTable
{
public:

    int uniqueWordCount;
    explicit HashTable(int size = 53)
            : ITEM_NOT_FOUND( "!" ), array( nextPrime( size ))
    {
        currentSize = 0;
        uniqueWordCount = 0;
    };

    ~HashTable(){
        makeEmpty();
    }

    [[nodiscard]] int arraySize() const{
        return array.size();
    }

    const Key & find( const Key & x ) const{
        int currentPos = findPos( x );
        if (isActive( currentPos ))
            return array[ currentPos ].key;

        return   ITEM_NOT_FOUND;

    };


    bool isPrime( int n )
    {
        if ( n == 2 || n == 3 )
            return true;

        if ( n == 1 || n % 2 == 0 )
            return false;

        for ( int i = 3; i * i <= n; i += 2 )
            if ( n % i == 0 )
                return false;

        return true;
    }

    int nextPrime( int n )
    {
        if ( n % 2 == 0 )
            n++;

        for ( ; ! isPrime( n ); n += 2 )
            ;

        return n;
    }

    void makeEmpty( ){
        array.erase(array.begin(), array.end());
    };

    Value getDetails(const Key &key){
        int currentPos = findPos( key );
        return array[currentPos].value;
    }

    void insert( const Key & x, Value value ){
        // Insert x as active
        int currentPos = findPos( x );
        if ( isActive( currentPos ) ){
            for(int j = 0; j < value->details.size(); j++){
                bool found = false;
                for(int i = 0; i < array[currentPos].value->details.size(); i++){ //Updates the count since we know this key exists
                    if(array[currentPos].value->details[i].documentName == value->details[j].documentName){
                        array[currentPos].value->details[i].count++;
                        found = true;
                        break;
                    }
                }
                if (!found) { // If the document was not found in the existing details, add it
                    array[currentPos].value->details.push_back(value->details[j]);
                }
            }
            return;
        }

        array[ currentPos ] = HashEntry(x,  value, ACTIVE );
        uniqueWordCount++;


        // enlarge the hash table if necessary
        if ( ++currentSize >= array.size( ) * 0.85 )
            rehash( );
    };


    enum EntryType { ACTIVE, EMPTY };
private:

    struct HashEntry
    {
        Key key;
        Value value;
        EntryType info;

        explicit HashEntry( const Key & key="" , Value value=nullptr,
                            EntryType i = EMPTY )
                : key( key ), info( i ), value(value) { }
    };

    vector<HashEntry> array;
    int currentSize;
    const Key ITEM_NOT_FOUND;

    [[nodiscard]] bool isActive( int currentPos ) const{
        return array[ currentPos ].info == ACTIVE;
    };

    int findPos( const Key & x ) const{
        int collisionNum = 0;
        int currentPos = hash( x, array.size( ) );

        while ( array[ currentPos ].info != EMPTY &&
                array[ currentPos ].key != x )
        {
            //currentPos += static_cast<int>(pow(++collisionNum, 2));  //add the difference (explicitly cast result to int to get rid of error),
            currentPos += ++collisionNum;
            if ( currentPos >= array.size( ) )    // perform the mod
                currentPos -= array.size( );                // if necessary
        }
        return currentPos;
    };

    void rehash( ){
        vector<HashEntry> oldArray = array;

        cout << "rehashed..." << endl;
        cout << "previous table size:" << array.size() << ", new table size: ";
        // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        cout << array.size() << ",  current unique word count " << uniqueWordCount << "," << endl;
        for ( int j = 0; j < array.size( ); j++ )
            array[ j ].info = EMPTY;

        // Copy table over
        currentSize = 0;
        uniqueWordCount = 0;
        for ( int i = 0; i < oldArray.size( ); i++ )
            if ( oldArray[ i ].info == ACTIVE )
                insert( oldArray[ i ].key, oldArray[ i ].value );
        cout << "current load factor: " << (double)uniqueWordCount/array.size() << endl;

    };

    [[nodiscard]] int hash (const string & key, int tableSize) const
    {
        int hashVal = 0;

        for (char i : key)
            hashVal = 37 * hashVal + i;

        hashVal = hashVal % tableSize;

        if (hashVal < 0)
            hashVal = hashVal + tableSize;

        return(hashVal);
    }
};



#endif
