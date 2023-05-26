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

template <class T>
ISequence<T>& concat(const ISequence<T>& first_sequence, const ISequence<T>& const second_sequence) {
	ISequence<T>& concated = *(first_sequence.copy());
	for (IConstIterator<T>* it = second_sequence.Icbegin(); !(it->is_equal(second_sequence.Icend())); it->next()) {
		concated.append(it->get());
	}
	return concated;
}

template <class T>
ISequence<T>& find(const ISequence<T>& sequence, bool (*f)(T)) {
	ISequence<T>& result = *(sequence.create());
	for (IConstIterator<T>* it = sequence.Icbegin(); !(it->is_equal(sequence.Icend())); it->next()) {
		if (f(it->get())) {
			result.append(it->get());
		}
	}
	return result;
}

template <class T>
T reduce(const ISequence<T>& seq, T(*f)(T, T), T base) {
	for (IConstIterator<T>* it = seq.Icend(); !(it->is_equal(seq.Icbegin()));) {
		it->prev();
		base = f(it->get(), base);
	}
	return base;
}

