// LinkedListConstIter.cpp
// Name: Nishant Jain
// VUNetid: jainn6
// Email: nishant.jan@vanderbilt.edu
// Honor statement: I attest that I understand the honor code for this class and have neither given
// nor received any unauthorized aid on this assignment
#ifndef LINKEDLISTCONSTITER_CPP
#define LINKEDLISTCONSTITER_CPP
#include <LinkedListConstIter.h>

template <typename T>
bool LinkedListConstIterator<T>::operator==(const LinkedListConstIterator<T>& rhs) const noexcept
{
    return mPtr == rhs.mPtr;
}
template <typename T>
bool LinkedListConstIterator<T>::operator!=(const LinkedListConstIterator<T>& rhs) const noexcept
{
    return mPtr != rhs.mPtr;
}
template <typename T> const T& LinkedListConstIterator<T>::operator*() const
{
    return mPtr->mItem;
}
template <typename T> const T* LinkedListConstIterator<T>::operator->() const
{
    return &mPtr->mItem;
}
template <typename T> LinkedListConstIterator<T>& LinkedListConstIterator<T>::operator++()
{
    mPtr = mPtr->mNext;
    return *this;
}
template <typename T> const LinkedListConstIterator<T> LinkedListConstIterator<T>::operator++(int)
{
    LinkedListConstIterator<T> temp(mPtr);
    mPtr = mPtr->mNext;
    return temp;
}
template <typename T> LinkedListConstIterator<T>& LinkedListConstIterator<T>::operator--()
{
    mPtr = mPtr->mPrev;
    return *this;
}
template <typename T> const LinkedListConstIterator<T> LinkedListConstIterator<T>::operator--(int)
{
    LinkedListConstIterator<T> temp(mPtr);
    mPtr = mPtr->mPrev;
    return temp;
}
template <typename T>
LinkedListConstIterator<T>::LinkedListConstIterator(LinkedListNode<T>* ptr)
    : mPtr(ptr)
{
}
#endif
