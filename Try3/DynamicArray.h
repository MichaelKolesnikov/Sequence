#pragma once
#include <ostream>
#include <stdlib.h>
#include <string.h>
#include "IndexOutOfRange.h"
#include "ICollection.h"

template<class T>
class DynamicArray : ICollection<T> {
private:
    class BaseIterator {
    protected:
        T* current;
    public:
        BaseIterator();
        BaseIterator(T* data);

        BaseIterator(const DynamicArray<T>& other);

        BaseIterator operator+ (int n);
        BaseIterator operator- (int n);

        BaseIterator& operator++ ();
        BaseIterator operator++ (int);

        BaseIterator& operator-- ();
        BaseIterator operator-- (int);

        bool operator== (const BaseIterator& other) const;
        bool operator!= (const BaseIterator& other) const;

        T get() const;
    };

    size_t length;
    T* data;
public:
    class ConstIterator : public BaseIterator {
    public:
        ConstIterator();
        ConstIterator(T* data);
        ConstIterator(const DynamicArray<T>& other);
    };
    class Iterator : public BaseIterator {
    public:
        Iterator();
        Iterator(T* data);
        Iterator(const DynamicArray<T>& other);

        T& operator* ();
    };

    ConstIterator cbegin() const;
    ConstIterator cend() const;
    Iterator begin();
    Iterator end();

    DynamicArray();
    DynamicArray(size_t size);
    DynamicArray(const T* const items, size_t size);
    DynamicArray(const DynamicArray<T>& dynamic_array);

    DynamicArray<T>& operator=(const DynamicArray<T>& other);
    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept;

    size_t get_length() const override;

    T& operator[](int index);

    T get(int index) const override;
    Option<T> try_get(int index) const override;

    void resize(size_t newSize);

    ~DynamicArray();

    friend std::ostream& operator<< (std::ostream& stream, const DynamicArray<T>& dynamic_array);
};

#include "DynamicArray_realization.h"
