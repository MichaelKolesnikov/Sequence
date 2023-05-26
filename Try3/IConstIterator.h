#pragma once

template <class T>
class IConstIterator {
public:
    virtual void next() = 0;

    virtual void prev() = 0;

    virtual bool is_equal(IConstIterator* other) const = 0;

    virtual T get() const = 0;
};

