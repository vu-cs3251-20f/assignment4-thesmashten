//
// Created by Nishant Jain on 10/15/20.
//
#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP
#include "memory"
#include "algorithm"


/**
 * Initializes an empty LinkedList.
 * This operation provides strong exception safety.
 */
template <typename T>
LinkedList<T> :: LinkedList() : mSize(0), mTail(nullptr) {}

/**
 * Initializes the LinkedList to be a copy of src.
 * This operation provides strong exception safety.
 *
 * @param src LinkedList to copy
 */
template <typename T>
LinkedList<T> :: LinkedList(const LinkedList<T>& src) {
    if (src.mTail->mNext == nullptr){ //check if head of ArrayList is nullptr
        mTail->mNext = nullptr;
    }
    else{
        LinkedListNode<T> srcNode = src.mTail->mNext; //head of other arraylist
        LinkedListNode<T> thisNode = mTail->mNext;
        while (srcNode != nullptr){
            thisNode = new LinkedListNode<T>(srcNode.mItem);
            thisNode = thisNode.mNext;
            srcNode = srcNode.mNext;
        }
    }
}

/**
 * Makes this object a copy of rhs using the same guidelines as the copy
 * constructor. Note that calling this method on yourself (l = l;) is
 * equivalent to a no-op.
 * This operation provides strong exception safety.
 *
 * @param rhs LinkedList to copy
 * @return *this, used for chaining.
 */
template <typename T>
LinkedList<T>& LinkedList<T> ::  operator=(const LinkedList<T>& rhs){
    if (this != rhs){
        this = LinkedList<T>(rhs);
        return *this;
    }
}

/**
 * Destructor. Releases all resources held by this LinkedList.
 * This operation is no-throw under the assumption that the parameterizing
 * type's destructor is no-throw.
 */
template <typename T>
LinkedList<T> :: ~LinkedList() noexcept{}









#endif // LINKED_LIST_CPP