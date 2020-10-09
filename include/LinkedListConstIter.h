// @author G. Hemingway, copyright 2020 - All rights reserved
//
#ifndef LINKEDLISTCONSTITER_H
#define LINKEDLISTCONSTITER_H

#include <exception>
#include <iterator>

template <typename T> class LinkedList;
template <typename T> class LinkedListNode;

/**
 * This header contains the const iterator for the
 * LinkedList container.  All of the methods for the classes should be self-explanatory
 *
 */
template <typename T> class LinkedListConstIterator {
public:
    friend class LinkedList<T>;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = int32_t;
    using pointer = T*;
    using reference = T&;

    LinkedListConstIterator() = delete;

    bool operator==(const LinkedListConstIterator<T>& rhs) const noexcept;
    bool operator!=(const LinkedListConstIterator<T>& rhs) const noexcept;
    const value_type& operator*() const;
    const value_type* operator->() const;
    LinkedListConstIterator<T>& operator++();
    const LinkedListConstIterator<T> operator++(int);
    LinkedListConstIterator<T>& operator--();
    const LinkedListConstIterator<T> operator--(int);

private:
    LinkedListNode<T>* mPtr;
    explicit LinkedListConstIterator(LinkedListNode<T>* ptr);
};

#include "../src/LinkedListConstIter.cpp"

#endif // LINKEDLISTCONSTITER_H
