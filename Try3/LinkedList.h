#pragma once
#include <ostream>
#include <stdlib.h>
#include <string.h>
#include "IndexOutOfRange.h"
#include "ICollection.h"

using namespace std;

template <class T>
class LinkedList : ICollection<T> {
private:
    class Node {
    public:
        T value;
        typename LinkedList<T>::Node* prev;
        typename LinkedList<T>::Node* next;

        Node();
        Node(T value, typename LinkedList<T>::Node* prev, typename LinkedList<T>::Node* next);
    };

    class BaseIterator {
    protected:
        typename LinkedList<T>::Node* current;
    public:
        BaseIterator();
        BaseIterator(LinkedList<T> list);
        BaseIterator(typename LinkedList<T>::Node* first);
        BaseIterator operator+ (int n);
        BaseIterator operator- (int n);
        BaseIterator operator++ (int);
        BaseIterator operator-- (int);
        BaseIterator operator++ ();
        BaseIterator operator-- ();
        bool operator!= (const BaseIterator& other) const;
        bool operator== (const BaseIterator& other) const;
        T get() const;
    };

    size_t length;
    typename LinkedList<T>::Node* head;
    typename LinkedList<T>::Node* tail;
public:
    class ConstIterator : public BaseIterator {
    public:
        ConstIterator();
        ConstIterator(LinkedList<T> list);
        ConstIterator(typename LinkedList<T>::Node* first);
    };
    class Iterator : public BaseIterator {
    public:
        Iterator();
        Iterator(LinkedList<T> list);
        Iterator(typename LinkedList<T>::Node* first);
        T& operator* ();
    };

    ConstIterator cbegin() const;
    ConstIterator cend() const;
    Iterator begin() noexcept;
    Iterator end() noexcept;

    LinkedList();
    LinkedList(size_t length);
    LinkedList(const T* const items, size_t length);
    LinkedList(const LinkedList<T>& list);

    T get_first() const;
    T get_last() const;

    T& operator[](int index);

    T get(int index) const override;
    Option<T> try_get(int index) const override;

    LinkedList<T>* get_sub_list(size_t startIndex, size_t endIndex) const;

    size_t get_length() const override;

    void append(T item);
    void prepend(T item);
    void insert_at(T item, size_t index);

    T pop();

    LinkedList<T>* concat(LinkedList<T>* list);

    ~LinkedList();

    friend std::ostream& operator<< (std::ostream& stream, const LinkedList<T>& list);
};

#include "LinkedList_realization.h"
