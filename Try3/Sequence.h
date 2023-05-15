#pragma once

#include <ostream>
#include "ICollection.h"
#include "IIterator.h"

template <class T>
class Sequence : public ICollection<T> {
public:
	virtual IConstIterator<T>* Icbegin() const = 0;
	virtual IConstIterator<T>* Icend() const = 0;
	virtual IIterator<T>* Ibegin() = 0;
	virtual IIterator<T>* Iend() = 0;

	Sequence() = default;
	Sequence(size_t length) {}
	Sequence(T* items, size_t length) {}
	Sequence(const Sequence<T>& other) = default;
	~Sequence() = default;
	virtual Sequence<T>* create() const = 0;
	virtual Sequence<T>* copy() const = 0;

	virtual size_t get_length() const override = 0;

	virtual T& operator[](int index) override = 0;

	virtual T get(int index) const override = 0;
	virtual Option<T> try_get(int index) const override = 0;

	virtual T get_first() const = 0;
	virtual T get_last() const = 0;

	Sequence<T>* get_sub_sequence(int startIndex, int endIndex) {
		Sequence<T>* sub = this->create();
		IIterator<T>* it = this->Ibegin();
		int i = 0;
		for (; i < startIndex; ++i) {
			it->next();
		}
		for (; i < endIndex; ++i, it->next()) {
			sub->append(it->get());
		}
		return sub;
	}

	virtual void append(T item) = 0;
	virtual void prepend(T item) = 0;
	virtual void insert_at(T item, int index) = 0;

	Sequence <T>* concat(Sequence <T>* otherSequence) const {
		Sequence<T>* concated = this->copy();
		for (IIterator<T>* it = otherSequence->Ibegin(); !(it->is_equel(otherSequence->Iend())); it->next()) {
			concated->append(it->get());
		}
		return concated;
	}

	Sequence<T>* find(bool (*f)(T)) {
        Sequence<T>* result = this->create();
        for (IIterator<T>* it = this->Ibegin(); !(it->is_equel(this->Iend())); it->next()) {
            if (f(it->get())) {
				result->append(it->get());
            }    
        }
        return result;
    }

    T reduce(T(*f)(T, T), T base) {
		for (IIterator<T>* it = this->Iend(); !(it->is_equel(this->Ibegin()));) {
			it->prev();
            base = f(it->get(), base);
        }
        return base;
    }

	friend std::ostream& operator<< (std::ostream& stream, Sequence<T>* sequence) {
		stream << std::endl << "[";
		IIterator<T>* it = sequence->Ibegin();
		for (; !(it->is_equel(sequence->Iend())); it->next()) {
			stream << it->get() << " ";
		}
		stream << "]" << std::endl;
		delete it;
		return stream;
	}
};

template <class output_type, class sequence_output_type, class input_type>
typename std::enable_if<std::is_base_of<Sequence<output_type>, sequence_output_type>::value, Sequence<output_type>*>::type
map_sequence(output_type(*f)(input_type), Sequence<input_type>* sequence) {
	Sequence<output_type>* result = new sequence_output_type();
	for (IIterator<input_type>* it = sequence->Ibegin(); !(it->is_equel(sequence->Iend())); it->next()) {
		result->append(f(it->get()));
	}
	return result;
}
