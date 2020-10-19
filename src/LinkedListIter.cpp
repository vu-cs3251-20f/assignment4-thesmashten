// LinkedListIter.cpp
// Name: Nishant Jain
// VUNetid: jainn6
// Email: nishant.jan@vanderbilt.edu
// Honor statement: I attest that I understand the honor code for this class and have neither given
// nor received any unauthorized aid on this assignment
#ifndef LINKEDLISTITER_CPP
#define LINKEDLISTITER_CPP

template <typename T>
bool LinkedListIterator<T>::operator==(const LinkedListIterator<T>& rhs) const noexcept
{
    return mPtr == rhs.mPtr;
}

template <typename T>
bool LinkedListIterator<T>::operator!=(const LinkedListIterator<T>& rhs) const noexcept
{
    return mPtr != rhs.mPtr;
}

template <typename T> T& LinkedListIterator<T>::operator*() const
{
    return mPtr->mItem;
}
template <typename T> T* LinkedListIterator<T>::operator->() const
{
    return &mPtr->mItem;
}
template <typename T> LinkedListIterator<T>& LinkedListIterator<T>::operator++()
{
    mPtr = mPtr->mNext;
    return *this;
}
template <typename T> const LinkedListIterator<T> LinkedListIterator<T>::operator++(int)
{
    LinkedListIterator<T> temp(mPtr);
    mPtr = mPtr->mNext;
    return temp;
}
template <typename T> LinkedListIterator<T>& LinkedListIterator<T>::operator--()
{
    mPtr = mPtr->mPrev;
    return *this;
}
template <typename T> const LinkedListIterator<T> LinkedListIterator<T>::operator--(int)
{
    LinkedListIterator<T> temp(mPtr);
    mPtr = mPtr->mPrev;
    return temp;
}
template <typename T>
LinkedListIterator<T>::LinkedListIterator(LinkedListNode<T>* ptr)
    : mPtr(ptr)
{
}
#endif
