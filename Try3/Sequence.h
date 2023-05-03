#pragma once

#include <ostream>
#include "ICollection.h"
#include "IIterator.h"

template <class T>
class Sequence : public ICollection<T> {
public:
	virtual IIterator<T>* Ibegin() = 0;
	virtual IIterator<T>* Iend() = 0;

	Sequence() = default;
	Sequence(size_t length) {}
	Sequence(T* items, size_t length) {}
	Sequence(const Sequence<T>& other) = default;
	~Sequence() = default;
	virtual Sequence<T>* create() = 0;
	virtual Sequence<T>* copy() = 0;

	virtual size_t get_length() const override = 0;

	virtual T& operator[](int index) override = 0;

	virtual T get(int index) const override = 0;
	virtual Option<T> try_get(int index) const override = 0;

	virtual T get_first() const = 0;
	virtual T get_last() const = 0;

	virtual Sequence<T>* get_sub_sequence(int startIndex, int endIndex) const = 0;

	virtual void append(T item) = 0;
	virtual void prepend(T item) = 0;
	virtual void insert_at(T item, int index) = 0;

	virtual Sequence <T>* concat(const Sequence <T>* const otherSequence) const = 0;

	Sequence<T>* map(T(*f)(T&)) {
        Sequence<T>* result = this->create();
        for (int i = 0; i < this->get_length(); ++i) {
            result->append(f(this->get(i)));
        }
        return result;
    }
	Sequence<T>* where(bool (*f)(T&)) {
        Sequence<T>* result = this->create();
        for (int i = 0; i < this->get_length(); ++i) {
            if (f(this->get(i))) {
                result->append(this->get(i));
            }    
        }
        return result;
    }
    T reduce(T(*f)(T, T), T base) {
        for (int i = this->get_length() - 1; i > 0; --i) {
            base = f(this->get(i), base);
        }
        base = f(this->get_first(), base);
        return base;
    }

	friend std::ostream& operator<< (std::ostream& stream, Sequence<T>* sequence) {
		stream << std::endl << sequence->get_length() << std::endl;
		for (IIterator<T>* it = sequence->Ibegin(); !(it->is_equel(sequence->Iend())); it->next()) {
			stream << it->get() << " ";
		}
		stream << std::endl;
		return stream;
	}
};
