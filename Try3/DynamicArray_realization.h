#include "DynamicArray.h"

template<class T>
DynamicArray<T>::BaseIterator::BaseIterator() : current(nullptr) {}

template<class T>
DynamicArray<T>::BaseIterator::BaseIterator(T* data) : current(data) {}

template<class T>
DynamicArray<T>::BaseIterator::BaseIterator(const DynamicArray<T>& other) : current(other.data) {}

template<class T>
typename DynamicArray<T>::BaseIterator DynamicArray<T>::BaseIterator::operator+ (int n) {
    return BaseIterator(current + n);
}

template<class T>
typename DynamicArray<T>::BaseIterator DynamicArray<T>::BaseIterator::operator- (int n) {
    return BaseIterator(current - n);
}

template<class T>
typename DynamicArray<T>::BaseIterator& DynamicArray<T>::BaseIterator::operator++ () {
    current++;
    return *this;
}

template<class T>
typename DynamicArray<T>::BaseIterator DynamicArray<T>::BaseIterator::operator++ (int) {
    Iterator iter = *this;
    ++(*this);
    return iter;
}

template<class T>
typename DynamicArray<T>::BaseIterator& DynamicArray<T>::BaseIterator::operator-- () {
    current--;
    return *this;
}

template<class T>
typename DynamicArray<T>::BaseIterator DynamicArray<T>::BaseIterator::operator-- (int) {
    BaseIterator iter = *this;
    --(*this);
    return iter;
}

template<class T>
bool DynamicArray<T>::BaseIterator::operator== (const BaseIterator& other) const {
    return this->current == other.current;
}

template<class T>
bool DynamicArray<T>::BaseIterator::operator!= (const BaseIterator& other) const {
    return !(this->operator==(other));
}

template<class T>
T DynamicArray<T>::BaseIterator::get() const {
    return *(current);
}

template<class T>
DynamicArray<T>::ConstIterator::ConstIterator() : BaseIterator() {}

template<class T>
DynamicArray<T>::ConstIterator::ConstIterator(T* data) : BaseIterator(data) {}

template<class T>
DynamicArray<T>::ConstIterator::ConstIterator(const DynamicArray<T>& other) : BaseIterator(other) {}

template<class T>
DynamicArray<T>::Iterator::Iterator() : BaseIterator() {}

template<class T>
DynamicArray<T>::Iterator::Iterator(T* data) : BaseIterator(data) {}

template<class T>
DynamicArray<T>::Iterator::Iterator(const DynamicArray<T>& other) : BaseIterator(other) {}

template<class T>
T& DynamicArray<T>::Iterator::operator* () {
    return *(this->current);
}

template<class T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::cbegin() const {
    return ConstIterator(this->data);
}

template<class T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::cend() const {
    return ConstIterator(this->data + this->length);
}

template<class T>
typename DynamicArray<T>::Iterator DynamicArray<T>::begin() {
    return Iterator(this->data);
}

template<class T>
typename DynamicArray<T>::Iterator DynamicArray<T>::end() {
    return Iterator(this->data + this->length);
}

template<class T>
DynamicArray<T>::DynamicArray() {
    this->length = 0;
    this->data = new T[0];
}

template<class T>
DynamicArray<T>::DynamicArray(size_t size) {
    this->length = size;
    this->data = new T[size];
}

template<class T>
DynamicArray<T>::DynamicArray(const T* const items, size_t size) {
    this->length = size;
    this->data = new T[size];
    memcpy(this->data, items, size * sizeof(T));
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamic_array) {
    this->length = dynamic_array.get_length();
    this->data = new T[this->length];
    memcpy(this->data, dynamic_array.data, length * sizeof(T));
}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this != &other) {
        delete[] this->data;
        this->length = other.length;
        this->data = new T[length];
        memcpy(this->data, other.data, length * sizeof(T));
    }
    return *this;
}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& other) noexcept {
    if (this != &other) {
        delete[] this->data;
        this->length = other.length;
        this->data = other.data;
        other.length = 0;
        other.data = nullptr;
    }
    return *this;
}

template<class T>
size_t DynamicArray<T>::get_length() const {
    return this->length;
}

template<class T>
T& DynamicArray<T>::operator[](int index) {
    if (index < 0 || this->length <= index) {
        throw IndexOutOfRange();
    }
    return this->data[index];
}

template<class T>
T DynamicArray<T>::get(int index) const {
    if (index < 0 || this->length <= index) {
        throw IndexOutOfRange();
    }
    return this->data[index];
}

template<class T>
Option<T> DynamicArray<T>::try_get(int index) const {
    if (index < 0 || this->length <= index) {
        return Option<T>();
    }
    return Option<T>(this->get(index));
}

template<class T>
void DynamicArray<T>::resize(size_t newSize) {
    this->length = newSize;
    this->data = (T*)realloc(this->data, newSize * sizeof(T));
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] this->data;
}

template<class T>
std::ostream& operator<< (std::ostream& stream, const DynamicArray<T>& dynamic_array) {
    stream << std::endl;
    stream << dynamic_array.get_length() << std::endl;
    for (auto it = dynamic_array.cbegin(); it != dynamic_array.cend(); ++it) {
        stream << it.get() << " ";
    }
    stream << std::endl;
    return stream;
}
