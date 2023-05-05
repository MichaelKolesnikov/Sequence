#pragma once
#include <ostream>
#include <stdlib.h>
#include <string.h>
#include "IndexOutOfRange.h"
#include "ICollection.h"

using namespace std;

template<class T>
class DynamicArray : ICollection<T> {
private:
	size_t length;
	T* data;
public:
    class ConstIterator {
    private:
        T* current;
    public:
        ConstIterator() : current(nullptr) {}
        ConstIterator(T* data) : current(data) {}

        ConstIterator(const DynamicArray<T>& other) : current(other.data) {}

        ConstIterator operator+ (int n) {
            return ConstIterator(current + n);
        }

        ConstIterator operator- (int n) {
            return ConstIterator(current - n);
        }

        ConstIterator& operator++ () {
            current++;
            return *this;
        }

        ConstIterator operator++ (int) {
            Iterator iter = *this;
            ++(*this);
            return iter;
        }

        ConstIterator& operator-- () {
            current--;
            return *this;
        }

        ConstIterator operator-- (int) {
            ConstIterator iter = *this;
            --(*this);
            return iter;
        }

        bool operator== (const ConstIterator& other) const {
            return this->current == other.current;
        }

        bool operator!= (const ConstIterator& other) const {
            return !(this->operator==(other));
        }

        T get() const {
            return *(current);
        }
    };
    class Iterator : ConstIterator {
    public:
        Iterator(T* data): ConstIterator(data) {}

        Iterator(const DynamicArray<T>& other) : ConstIterator(other) {}

        T& operator* () { 
            return *(this->current); 
        }
    };

    ConstIterator cbegin() const {
        return ConstIterator(this->data);
    }
    ConstIterator cend() const {
        return ConstIterator(this->data + this->length);
    }
    Iterator begin() {
        return Iterator(this->data);
    }
    Iterator end() {
        return Iterator(this->data + this->length);
    }

	DynamicArray() {
		this->length = 0;
		this->data = new T[0];
	}
	DynamicArray(size_t size) {
		this->length = size;
		this->data = new T[size];
	}
	DynamicArray(const T* const items, size_t size) {
		this->length = size;
		this->data = new T[size];
		memcpy(this->data, items, size * sizeof(T));
	}
	DynamicArray(const DynamicArray<T>& dynamic_array) {
		this->length = dynamic_array.get_length();
		this->data = new T[this->length];
		memcpy(this->data, dynamic_array.data, length * sizeof(T));
	}
	
	size_t get_length() const override {
		return this->length;
	}

	T& operator[](int index) {
		if (index < 0 || this->length <= index) {
			throw IndexOutOfRange();
		}
		return this->data[index];
	}

	T get(int index) const override {
		if (index < 0 || this->length <= index) {
			throw IndexOutOfRange();
		}
		return this->data[index];
	}
	Option<T> try_get(int index) const override {
		if (index < 0 || this->length <= index) {
			return Option<T>();
		}
		return Option<T>(this->get(index));
	}

	void resize(size_t newSize) {
		this->length = newSize;
		this->data = (T*)realloc(this->data, newSize * sizeof(T));
	}

	~DynamicArray() {
		delete[] this->data;
	}

    friend std::ostream& operator<< (std::ostream& stream, const DynamicArray<T>& dynamic_array) {
		stream << std::endl;
		stream << dynamic_array.get_length() << std::endl;
        for (auto it = dynamic_array.cbegin(); it != dynamic_array.cend(); ++it) {
            stream << it.get() << " ";
        }
		stream << std::endl;
        return stream;
    }
};
