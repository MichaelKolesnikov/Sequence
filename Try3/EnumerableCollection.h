#pragma once
#include "ICollection.h"
#include "Enumerable.h"
#include "CollectionEnumerator.h"
#include <ostream>

template<typename T>
class EnumerableCollection : public ICollection<T>, public Enumerable<T> {
public:
    EnumerableCollection() = default;
    EnumerableCollection(EnumerableCollection<T> const& collection) = default;
    
    ~EnumerableCollection() = default;
    
    CollectionEnumerator<T>* GetEnumerator() override {
        return new CollectionEnumerator<T>(*this);
    }
};

template<class T>
std::ostream& operator << (std::ostream& os, EnumerableCollection<T>& collection) {
    for (CollectionEnumerator<T>* it = collection.GetEnumerator();;) {
        os << it->Current() << ' ';
        if (!(it->MoveNext())) {
            break;
        }
    }
    os << std::endl;
    return os;
}