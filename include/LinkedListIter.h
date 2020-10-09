// @author G. Hemingway, copyright 2020 - All rights reserved
//
#ifndef LINKEDLISTITER_H
#define LINKEDLISTITER_H

#include <exception>
#include <iterator>

template <typename T> class LinkedList;
template <typename T> class LinkedListNode;

/**
 * This header contains both the normal iterator and the const iterator for the
 * LinkedList container.  All of the methods for both classes should be self-explanatory
 *
 */
template <typename T>
class LinkedListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    friend class LinkedList<T>;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = int32_t;
    using pointer = T*;
    using reference = T&;

    LinkedListIterator() = delete;

    bool operator==(const LinkedListIterator<T>& rhs) const noexcept;
    bool operator!=(const LinkedListIterator<T>& rhs) const noexcept;
    value_type& operator*() const;
    value_type* operator->() const;
    LinkedListIterator<T>& operator++();
    const LinkedListIterator<T> operator++(int);
    LinkedListIterator<T>& operator--();
    const LinkedListIterator<T> operator--(int);

private:
    LinkedListNode<T>* mPtr;
    explicit LinkedListIterator(LinkedListNode<T>* ptr);
};

#include "../src/LinkedListIter.cpp"

#endif // LINKEDLISTITER_H
