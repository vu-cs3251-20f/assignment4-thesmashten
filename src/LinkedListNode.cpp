//
// Created by Nishant Jain on 10/15/20.
//
#ifndef LINKED_LIST_NODE_CPP
#define LINKED_LIST_NODE_CPP

/**
 * Initializes this node with the provided values, i.e. the node stores
 * item, follows prev and precedes next in the linked list. Modifies prev
 * and next to maintain the linked list invariant.  Prev and next should
 * never be nullptr, so don't bother checking for that.
 * This operation provides strong exception safety.
 *
 * @param item item to store in the node
 * @param prev pointer to the previous node
 * @param next pointer to the next node
 */
template <typename T>
LinkedListNode<T> :: LinkedListNode(const T& item, LinkedListNode<T>* prev, LinkedListNode<T>* next)
: mItem(item), mPrev(prev), mNext(next){}

/**
 * Establishes the proper linkage between the provided nodes.  First and
 * second should never be nullptr, so don't bother checking for that.
 *
 * @param   first node to link as preceding node
 * @param   second node to link as succeeding node
 * @post    first and second are linked in that order
 */
template <typename T>
void LinkedListNode<T> :: link(LinkedListNode<T>* first, LinkedListNode<T>* second) noexcept{
    if (first != second){
        first->mNext = second;
        second->mPrev = first;
    }
}


/**
 * Initializes this node to store the provided item. The next and previous
 * pointers of this node are set to point to the node itself.
 * This operation provides strong exception safety.
 * @param item the item to set
 */
template <typename T>
LinkedListNode<T> :: LinkedListNode(const T& item) : mItem(item), mPrev(this), mNext(this){}



/**
 * Destructor. Unlinks this node from its neighbors.
 * This operation is a no-throw.
 */
template <typename T>
LinkedListNode<T> :: ~LinkedListNode() noexcept{
    if (this->mNext == nullptr){ //if it's the last node in the list
        mPrev->mNext = nullptr;
    }
    else { // some random node in the middle of the list (has an mPrev and mNext)
        mNext->mPrev = mPrev;
        mPrev->mNext = mNext;
    }
    LinkedListNode<T>* node(this); //exception safety?
    delete node;
}


#endif // LINKED_LIST_NODE_CPP
