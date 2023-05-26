#pragma once
#include "IIterator.h"
#include "ArraySequence.h"

template <class T>
class ITree {
public:
    virtual void insert(T value) = 0;
    virtual bool contains(T value) const = 0;
    virtual IIterator<T>* create_iterator(const ArraySequence<int>& permutation) = 0;
    virtual IConstIterator<T>* create_const_iterator(const ArraySequence<int>& permutation) const = 0;
};

