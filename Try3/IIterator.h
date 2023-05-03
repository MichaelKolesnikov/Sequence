#pragma once

#include "ICollection.h"

template <class T>
class IIterator {
protected:
    ICollection<T>* collection;
    int index;
public:
    virtual void next() = 0;

    virtual void prev() = 0;

    virtual bool is_equel(IIterator* other) const = 0;

    virtual T get() const = 0;

    virtual T& operator* () = 0;
};

