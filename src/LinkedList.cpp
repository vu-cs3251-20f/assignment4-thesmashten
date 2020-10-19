// LinkedList.cpp
// Name: Nishant Jain
// VUNetid: jainn6
// Email: nishant.jan@vanderbilt.edu
// Honor statement: I attest that I understand the honor code for this class and have neither given
// nor received any unauthorized aid on this assignment
#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP
#include <LinkedList.h>
#include <cstddef>
#include <string>

/**
 * Initializes an empty LinkedList.
 * This operation provides strong exception safety.
 */
template <typename T>
LinkedList<T>::LinkedList()
    : mSize(0)
    , mTail(std::make_unique<LinkedListNode<T>>())
{
}

/**
 * Initializes the LinkedList to be a copy of src.
 * This operation provides strong exception safety.
 *
 * @param src LinkedList to copy
 */
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& src)
    : mSize(0)
    , mTail(std::make_unique<LinkedListNode<T>>())
{
    uint32_t otherSize = src.mSize;
    std::unique_ptr<LinkedList<T>> tmp(std::make_unique<LinkedList<T>>());
    LinkedListConstIterator<T> iter = src.begin();
    for (uint32_t i = 0; i < otherSize; ++i) {
        tmp->add(*iter);
        ++iter;
    }
    swap(*tmp);
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
template <typename T> LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
    if (this != &rhs) {
        std::unique_ptr<LinkedList<T>> tmp(std::make_unique<LinkedList<T>>(rhs));
        swap(*tmp);
    }
    return *this;
}

/**
 * Destructor. Releases all resources held by this LinkedList.
 * This operation is no-throw under the assumption that the parameterizing
 * type's destructor is no-throw.
 */
template <typename T> LinkedList<T>::~LinkedList() noexcept
{
    LinkedList<T>::clear();
}

/**
 * Adds value to the end of this LinkedList. The insertion is performed in
 * constant time.
 * This operation provides strong exception safety.
 *
 * @param value value to append to this LinkedList
 */
template <typename T> void LinkedList<T>::add(const T& value)
{
    new LinkedListNode<T>(value, mTail->mPrev, mTail.get());
    ++mSize;
}

/**
 * Inserts value at the specified index. All elements at or to the right of
 * index are shifted down by one spot. Time proportional to the maximum of
 * the size of this LinkedList or index is needed to perform this operation.
 * In particular, note that this operation does not perform the tail
 * insertion optimization that add(const T& value) offers. If this
 * LinkedList needs to be enlarged (index is out of range) default values
 * are used to fill the gaps.
 * This operation provides strong exception safety.
 *
 * @param index index at which to insert value
 * @param value the element to insert
 */
template <typename T> void LinkedList<T>::add(uint32_t index, const T& value)
{
    // case 1: adding to an empty list (adding to the front of the list)
    // case 2: adding to end of the list (index = mSize)
    // case 3: adding after the end of the list (index > mSize)
    // case 4: adding in the middle of the list somewhere (index < mSize)
    // case 5: adding to the front of the list in a non-empty Linked List (index = 0)
    // case 6: adding to an empty list with an index greater than mSize (i.e index = 10)
    if (index == mSize) { // case 2
        add(value);
        return;
    } else if (index < mSize) { // case 1, case 4
        LinkedListNode<T>* currNode(mTail->mNext);
        for (uint32_t i = 0; i < index; ++i) {
            currNode = currNode->mNext;
        }
        new LinkedListNode<T>(value, currNode->mPrev, currNode);
        ++mSize;
    } else { // case 3, case 5, case 6
        uint32_t firstSize = mSize;
        uint32_t diff = index - firstSize;
        for (uint32_t i = 0; i < diff; ++i) {
            add(T());
        }
        add(value); // add the real value at the indexth index
    }
}

/**
 * Empties this LinkedList returning it to the same state as the default
 * constructor.
 * This operation is no-throw under the assumption that the parameterizing
 * type's destructor is no-throw.
 */
template <typename T> void LinkedList<T>::clear() noexcept
{
    while (mSize > 0) {
        LinkedList<T>::removeNode(begin());
    }
}

/**
 * Returns a constant reference to the element stored at the provided index.
 * If index is out of bounds, an std::out_of_range exception is thrown with
 * the index as its message.
 * This operation provides strong exception safety.
 *
 * @param index index of the element to return
 * @return constant reference to the element at the index.
 */
template <typename T> const T& LinkedList<T>::get(uint32_t index) const
{
    rangeCheck(index);
    LinkedListNode<T>* currNode(mTail->mNext);
    while (index > 0) {
        currNode = currNode->mNext;
        --index;
    }
    return currNode->mItem;
}

/**
 * Returns a reference to the element stored at the provided index. If index
 * is out of bounds, an std::out_of_range exception is thrown with the index
 * as its message.
 * This operation provides strong exception safety.
 *
 * @param index index of the element to return
 * @return reference to the element at the index.
 */
template <typename T> T& LinkedList<T>::get(uint32_t index)
{
    return const_cast<T&>(const_cast<const LinkedList&>(*this).get(index));
}

/**
 * Returns true if and only if this LinkedList is logically equivalent to
 * rhs, i.e. the size and contents are equal.
 * This operation provides strong exception safety.
 *
 * @param rhs the LinkedList being compared to
 * @return true iff logically equivalent
 */
template <typename T> bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
    if (mSize != rhs.mSize) {
        return false;
    }
    LinkedListNode<T>* tmp(mTail->mNext);
    LinkedListNode<T>* rhsOne(rhs.mTail->mNext);
    for (uint32_t i = 0; i < mSize; ++i) {
        if (tmp->mItem != rhsOne->mItem) {
            rhsOne = rhsOne->mNext;
            tmp = tmp->mNext;
        }
    }
    return true;
}

/**
 * Returns false if this LinkedList is equal to rhs and true otherwise.
 * This operation provides strong exception safety.
 *
 * @param rhs the LinkedList being compared to
 * @return true iff not logically equivalent
 */
template <typename T> bool LinkedList<T>::operator!=(const LinkedList<T>& rhs) const
{
    return !(*this == rhs);
}

/**
 * Returns a constant iterator to the beginning.
 * This operation is a no-throw.
 *
 * @return const_iterator
 */
template <typename T> LinkedListConstIterator<T> LinkedList<T>::begin() const noexcept
{
    return LinkedListConstIterator<T>(mTail->mNext);
}

/**
 * Returns an iterator to the beginning.
 * This operation is a no-throw.
 *
 * @return iterator
 */
template <typename T> LinkedListIterator<T> LinkedList<T>::begin() noexcept
{
    return LinkedListIterator<T>(mTail->mNext);
}

/**
 * Returns a constant iterator to the end.
 * This operation is a no-throw.
 *
 * @return const_iterator
 */
template <typename T> LinkedListConstIterator<T> LinkedList<T>::end() const noexcept
{
    return LinkedListConstIterator<T>(mTail.get());
}

/**
 * Returns an iterator to the end.
 * This operation is a no-throw.
 *
 * @return iterator
 */
template <typename T> LinkedListIterator<T> LinkedList<T>::end() noexcept
{
    return LinkedListIterator<T>(mTail.get());
}

/**
 * Returns true if this LinkedList is empty and false otherwise.
 * This operation is a no-throw.
 *
 * @return bool True when empty
 */
template <typename T> bool LinkedList<T>::isEmpty() const noexcept
{
    return mSize == 0;
}

/**
 * Removes the element at the specified index. If index is out of bounds
 * an std::out_of_range exception is thrown with index as its messaged. If
 * index points to the first or last element, this operation is performed in
 * constant time. Otherwise, time proportional to index is needed.
 * This operation provides strong exception safety.
 *
 * @param index index of the object to remove.
 */
template <typename T> void LinkedList<T>::remove(uint32_t index)
{
    rangeCheck(index);
    LinkedListIterator<T> iter = begin();
    for (uint32_t i = 0; i < index; ++i) {
        ++iter;
    }
    LinkedList<T>::removeNode(iter);
}

/**
 * Sets the element at the specified index to the provided value. If index
 * is out of bounds, an std::out_of_range exception is thrown with the index
 * as its message. This method completes in time proportional to index.
 * This operation provides strong exception safety.
 *
 * @param index index of the object to set
 * @param value the new value
 */
template <typename T> void LinkedList<T>::set(uint32_t index, const T& value)
{
    rangeCheck(index);
    LinkedListNode<T>* list(mTail->mNext);
    for (uint32_t i = 0; i < index; ++i) {
        list = list->mNext;
    }
    list->mItem = value;
}

/**
 * Return the size of this LinkedList.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T> uint32_t LinkedList<T>::size() const noexcept
{
    return mSize;
}

/**
 * Given an index, this method throws an std::out_of_range with the index as
 * its message if index is out of bounds or is a no-op otherwise.
 * This operation provides strong exception safety.
 *
 * @param index index to check
 */
template <typename T> void LinkedList<T>::rangeCheck(uint32_t index) const
{
    if (index >= mSize) {
        throw std::out_of_range(std::to_string(index));
    }
}

/**
 * Removes from this LinkedList the node pointed to by iter.
 * This operation is no-throw under the assumption that the parameterizing
 * type's destructor is no-throw.
 *
 * @pre the iterator iter must point to an element (or end) within this list
 * @param iter iterator pointing to the node that should be removed.
 */
template <typename T> void LinkedList<T>::removeNode(LinkedList::iterator iter) noexcept
{
    if (iter != end()) {
        delete iter.mPtr;
        --mSize;
    }
}

/**
 * Swaps the contents of this LinkedList with that of other in constant time.
 * This operation is a no-throw.
 *
 * @param other the LinkedList to swap with
 */
template <typename T> void LinkedList<T>::swap(LinkedList<T>& rhs) noexcept
{
    mTail.swap(rhs.mTail);
    std::swap(rhs.mSize, mSize);
}
#endif
