#pragma once

#include <ostream>
#include "ICollection.h"
#include "IIterator.h"
#include "IConstIterator.h"

template <class T>
class ISequence : public ICollection<T> {
public:
	virtual IConstIterator<T>* Icbegin() const = 0;
	virtual IConstIterator<T>* Icend() const = 0;
	virtual IIterator<T>* Ibegin() = 0;
	virtual IIterator<T>* Iend() = 0;

	ISequence() = default;
	ISequence(size_t length) {}
	ISequence(T* items, size_t length) {}
	ISequence(const ISequence<T>& other) = default;
	~ISequence() = default;
	virtual ISequence<T>* create() const = 0;
	virtual ISequence<T>* copy() const = 0;

	virtual size_t get_length() const override = 0;

	virtual T& operator[](int index) override = 0;

	virtual T get(int index) const override = 0;
	virtual Option<T> try_get(int index) const override = 0;

	virtual T get_first() const = 0;
	virtual T get_last() const = 0;

	ISequence<T>& get_sub_sequence(int startIndex, int endIndex) const {
		ISequence<T>& sub = *(this->create());
		IConstIterator<T>* it = this->Icbegin();
		int i = 0;
		for (; i < startIndex; ++i) {
			it->next();
		}
		for (; i < endIndex; ++i, it->next()) {
			sub.append(it->get());
		}
		return sub;
	}

	virtual void append(T item) = 0;
	virtual void prepend(T item) = 0;
	virtual void insert_at(T item, int index) = 0;

	virtual T pop() = 0;

	ISequence<T>& concat(const ISequence <T>& const otherSequence) const {
		ISequence<T>& concated = *(this->copy());
		for (IConstIterator<T>* it = otherSequence.Icbegin(); !(it->is_equal(otherSequence.Icend())); it->next()) {
			concated.append(it->get());
		}
		return concated;
	}

	ISequence<T>& find(bool (*f)(T)) const {
        ISequence<T>& result = *(this->create());
        for (IConstIterator<T>* it = this->Icbegin(); !(it->is_equal(this->Icend())); it->next()) {
            if (f(it->get())) {
				result.append(it->get());
            }    
        }
        return result;
    }

    T reduce(T(*f)(T, T), T base) const {
		for (IConstIterator<T>* it = this->Icend(); !(it->is_equal(this->Icbegin()));) {
			it->prev();
            base = f(it->get(), base);
        }
        return base;
    }

	friend std::ostream& operator<< (std::ostream& stream, const ISequence<T>& sequence) {
		stream << std::endl << "[";
		IConstIterator<T>* it = sequence.Icbegin();
		for (; !(it->is_equal(sequence.Icend())); it->next()) {
			stream << it->get() << " ";
		}
		stream << "]" << std::endl;
		delete it;
		return stream;
	}
};

template <class output_type, class sequence_output_type, class input_type>
typename std::enable_if<std::is_base_of<ISequence<output_type>, sequence_output_type>::value, ISequence<output_type>&>::type
map_sequence(output_type(*f)(input_type), const ISequence<input_type>& sequence) {
	ISequence<output_type>& result = *(new sequence_output_type());
	for (IConstIterator<input_type>* it = sequence.Icbegin(); !(it->is_equal(sequence.Icend())); it->next()) {
		result.append(f(it->get()));
	}
	return result;
}