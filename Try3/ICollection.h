#pragma once
#include "Option.h"

template<class T>
class ICollection {
public:
    virtual size_t get_length() const = 0;
    
    virtual T& operator[](int index) = 0;

    virtual T get(int index) const = 0;
    virtual Option<T> try_get(int index) const = 0;
};

