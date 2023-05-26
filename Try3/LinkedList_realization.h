#pragma once
#include "LinkedList.h"

template <class T>
LinkedList<T>::Node::Node() {
    this->value = T();
    this->prev = nullptr;
    this->next = nullptr;
}

template <class T>
LinkedList<T>::Node::Node(T value, typename LinkedList<T>::Node* prev, typename LinkedList<T>::Node* next) {
    this->value = value;
    this->prev = prev;
    this->next = next;
}

template <class T>
LinkedList<T>::BaseIterator::BaseIterator() : current(nullptr) {}

template <class T>
LinkedList<T>::BaseIterator::BaseIterator(LinkedList<T> list) : current(list.head) {}

template <class T>
LinkedList<T>::BaseIterator::BaseIterator(typename LinkedList<T>::Node* first) : current(first) {}

template <class T>
typename LinkedList<T>::BaseIterator LinkedList<T>::BaseIterator::operator+ (int n) {
    size_t counter = 0;
    while (counter != n) {
        current = this->current->next;
        counter++;
    }
    return *this;
}

template <class T>
typename LinkedList<T>::BaseIterator LinkedList<T>::BaseIterator::operator- (int n) {
    size_t counter = 0;
    while (counter != n) {
        this->current = this->current->prev;
        counter++;
    }
    return *this;
}

template <class T>
typename LinkedList<T>::BaseIterator LinkedList<T>::BaseIterator::operator++ (int) {
    current = current->next;
    return *this;
}

template <class T>
typename LinkedList<T>::BaseIterator LinkedList<T>::BaseIterator::operator-- (int) {
    current = current->prev;
    return *this;
}

template <class T>
typename LinkedList<T>::BaseIterator LinkedList<T>::BaseIterator::operator++ () {
    current = current->next;
    return *this;
}

template <class T>
typename LinkedList<T>::BaseIterator LinkedList<T>::BaseIterator::operator-- () {
    current = current->prev;
    return *this;
}

template <class T>
bool LinkedList<T>::BaseIterator::operator!= (const BaseIterator& other) const {
    return this->current != other.current;
}

template <class T>
bool LinkedList<T>::BaseIterator::operator== (const BaseIterator& other) const {
    return this->current == other.current;
}

template <class T>
T LinkedList<T>::BaseIterator::get() const {
    return this->current->value;
}

template <class T>
LinkedList<T>::ConstIterator::ConstIterator() : BaseIterator() {}

template <class T>
LinkedList<T>::ConstIterator::ConstIterator(LinkedList<T> list) : BaseIterator(list) {}

template <class T>
LinkedList<T>::ConstIterator::ConstIterator(typename LinkedList<T>::Node* first) : BaseIterator(first) {}

template <class T>
LinkedList<T>::Iterator::Iterator() : BaseIterator() {}

template <class T>
LinkedList<T>::Iterator::Iterator(LinkedList<T> list) : BaseIterator(list) {}

template <class T>
LinkedList<T>::Iterator::Iterator(typename LinkedList<T>::Node* first) : BaseIterator(first) {}

template <class T>
T& LinkedList<T>::Iterator::operator* () {
    return this->current->value;
}

template <class T>
typename LinkedList<T>::ConstIterator LinkedList<T>::cbegin() const {
    return ConstIterator(this->head);
}

template <class T>
typename LinkedList<T>::ConstIterator LinkedList<T>::cend() const {
    return ConstIterator(this->tail->next);
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() noexcept {
    return Iterator(this->head);
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::end() noexcept {
    return Iterator(this->tail->next);
}

template <class T>
LinkedList<T>::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}

template <class T>
LinkedList<T>::LinkedList(size_t length) {
    this->length = length;
    if (length == 0) {
        *this = LinkedList<T>();
        return;
    }
    this->head = new typename LinkedList<T>::Node();
    typename LinkedList<T>::Node* node = this->head;
    for (size_t i = 1; i < length; ++i) {
        node->next = new typename LinkedList<T>::Node;
        node->next->prev = node;
        node = node->next;
    }
    this->tail = node;
}

template <class T>
LinkedList<T>::LinkedList(const T* const items, size_t length) : LinkedList(length) {
    int i = -1;
    for (typename LinkedList<T>::Node* node = this->head; node != nullptr; node = node->next) {
        node->value = items[++i];
    }
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) : LinkedList(list.length) {
    for (typename LinkedList<T>::Node* node = this->head, *newNode = list.head; newNode != nullptr; node = node->next, newNode = newNode->next) {
        node->value = newNode->value;
    }
}

template <class T>
T LinkedList<T>::get_first() const {
    if (this->length == 0) {
        throw IndexOutOfRange();
    }
    return this->head->value;
}

template <class T>
T LinkedList<T>::get_last() const {
    if (this->length == 0) {
        throw IndexOutOfRange();
    }
    return this->tail->value;
}

template <class T>
T& LinkedList<T>::operator[](int index) {
    if (index < 0 || this->length <= index) {
        throw IndexOutOfRange();
    }
    int i = 0;
    typename LinkedList<T>::Node* node = this->head;
    for (; i < index; node = node->next, ++i) {}
    return node->value;
}

template <class T>
T LinkedList<T>::get(int index) const {
    if (this->length <= index) {
        throw IndexOutOfRange();
    }
    int i = 0;
    typename LinkedList<T>::Node* node = this->head;
    for (; node != nullptr && i != index; node = node->next, ++i) {}
    return node->value;
}

template <class T>
Option<T> LinkedList<T>::try_get(int index) const {
    if (index < 0 || this->length <= index) {
        return Option<T>();
    }
    return Option<T>(this->get(index));
}

template <class T>
LinkedList<T>* LinkedList<T>::get_sub_list(size_t startIndex, size_t endIndex) const {
    if (startIndex >= this->length || endIndex > this->length) {
        throw IndexOutOfRange();
    }
    LinkedList<T>* subList = new LinkedList<T>(endIndex - startIndex);
    typename LinkedList<T>::Node* node = this->head;
    int i = 0;
    for (; i != startIndex; ++i, node = node->next) {}
    typename LinkedList<T>::Node* subNode = subList->head;
    for (; i < endIndex; ++i, node = node->next, subNode = subNode->next) {
        subNode->value = node->value;
    }
    return subList;
}

template <class T>
size_t LinkedList<T>::get_length() const {
    return this->length;
}

template <class T>
void LinkedList<T>::append(T item) {
    if (this->length == 0) {
        *this = LinkedList<T>(&item, 1);
        return;
    }
    this->tail->next = new typename LinkedList<T>::Node(item, this->tail, nullptr);
    this->tail = this->tail->next;
    ++this->length;
}

template <class T>
void LinkedList<T>::prepend(T item) {
    if (this->length == 0) {
        *this = LinkedList<T>(&item, 1);
        return;
    }
    this->head->prev = new typename LinkedList<T>::Node(item, nullptr, this->head);
    this->head = this->head->prev;
    ++this->length;
}

template <class T>
void LinkedList<T>::insert_at(T item, size_t index) {
    if (this->length < index) {
        throw IndexOutOfRange();
    }
    if (index == 0) {
        this->prepend(item);
        return;
    }
    if (index == this->length) {
        this->append(item);
        return;
    }
    int i = 0;
    typename LinkedList<T>::Node* node = this->head;
    for (; i != index - 1; ++i, node = node->next) {}
    typename LinkedList<T>::Node* newNode = new typename LinkedList<T>::Node(item, node, node->next);
    node->next->prev = newNode;
    node->next = newNode;
    ++this->length;
}

template <class T>
T LinkedList<T>::pop() {
    if (this->length == 0) {
        throw IndexOutOfRange();
    }
    T item = this->tail->value;
    typename LinkedList<T>::Node* prev = this->tail->prev;
    delete this->tail;
    this->tail = prev;
    this->tail->next = nullptr;
    --this->length;
    return item;
}

template <class T>
LinkedList<T>* LinkedList<T>::concat(LinkedList<T>* list) {
    if (list == nullptr) {
        return this;
    }
    if (this->length == 0) {
        *this = LinkedList<T>(*list);
        return this;
    }
    if (list->length == 0) {
        delete list;
        return this;
    }
    this->tail->next = list->head;
    list->head->prev = this->tail;
    this->tail = list->tail;
    this->length += list->length;
    delete list;
    return this;
}

template <class T>
LinkedList<T>::~LinkedList() {
    typename LinkedList<T>::Node* current = this->head;
    while (current != nullptr) {
        typename LinkedList<T>::Node* next = current->next;
        delete current;
        current = next;
    }
}

template <class T>
std::ostream& operator<< (std::ostream& stream, const LinkedList<T>& list) {
    typename LinkedList<T>::ConstIterator iter = list.cbegin();
    while (iter != list.cend()) {
        stream << *iter << " ";
        ++iter;
    }
    return stream;
}
