#pragma once
#include "ICollection.h"
#include "Enumerator.h"
#include <stdexcept>

template<class T>
class CollectionEnumerator : public Enumerator<T> {
private:
    int index;
    ICollection<T>& collection;
public:
    CollectionEnumerator(const ICollection<T>& collection) : index(0), collection((ICollection<T>&)collection) {}
    CollectionEnumerator(const ICollection<T>& collection, int start) : collection(collection) {
        if (start < collection.get_length()) {
            this->index = start;
        } 
        else {
            throw std::out_of_range("Index out of range");
        }
    }
    T Current() override {
        return this->collection.Get(index);
    }
    bool MoveNext() override {
        if (collection.GetLength() - 1 > index) {
            ++(this->index);
            return true;
        }
        else {
            return false;
        }
    }
    void Reset() override {
        this->index = 0;
    }
};
