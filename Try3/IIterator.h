#pragma once

#include "ICollection.h"

template <class T>
class IConstIterator {
protected:
    int index;
public:
    virtual void next() = 0;

    virtual void prev() = 0;

    virtual bool is_equel(IConstIterator* other) const = 0;

    virtual T get() const = 0;
};

template <class T>
class IIterator {
protected:
    int index;
public:
    virtual void next() = 0;

    virtual void prev() = 0;

    virtual bool is_equel(IIterator* other) const = 0;

    virtual T get() const = 0;

    virtual T& operator* () = 0;
};

