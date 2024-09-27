#include <iostream>

using namespace std;

template <class Object>
class Stack{
    public:
        Stack(){
            topOfStack = nullptr;
            stackCount = 0;
        }
        Stack(const Stack & rhs){
            topOfStack = nullptr;
            *this = rhs;

        }
        ~Stack( ){
            makeEmpty( );
        }

        bool isEmpty() const{
            return topOfStack == nullptr;
        }
        void makeEmpty(){
            while ( ! isEmpty( ) )
                pop( );

        }

        int returnStackCount(){
            return stackCount;
        }

        void pop(){
            if ( isEmpty( ) )
                throw out_of_range("Stack Underflow");
            ListNode *oldTop = topOfStack;
            stackCount--;
            topOfStack = topOfStack->next;
            delete oldTop;

        }
        void push(Object & myObject){
            stackCount++;
            topOfStack = new ListNode( myObject, topOfStack);
        }

        const Object & top() const{
            if ( isEmpty( ) )
                throw out_of_range("Stack Underflow");
            return topOfStack->element;

        }

        const Stack & operator=(const Stack & rhs){
            if ( this != &rhs )
            {
                makeEmpty( );
                if ( rhs.isEmpty( ) )
                    return *this;

                ListNode *rptr = rhs.topOfStack;
                ListNode *ptr  = new ListNode( rptr->element );
                topOfStack = ptr;

                for ( rptr = rptr->next; rptr != nullptr; rptr = rptr->next )
                    ptr = ptr->next = new ListNode( rptr->element );
            }
            return *this;

        }



private:

    struct ListNode
    {
        Object   element;
        ListNode *next;


        ListNode( const Object & theElement, ListNode * n = nullptr)
                : element( theElement ), next( n )
                { }
    };


    int stackCount;
    ListNode *topOfStack;

};
