#pragma once
#include "Sequence.h"
#include "DynamicArray.h"
#include "IIterator.h"

template <class T>
class ArraySequence : public Sequence<T> {
private:
	DynamicArray<T>* dynamicArray;
public:
	class Iterator : public IIterator<T> {
	private:
		T* pointer;
	public:
		Iterator(ArraySequence<T>* seq, int index) {
			this->collection = seq;
			this->index = index;
			this->pointer = (0 <= index && index < seq->get_length() ? &seq->operator[](index) : nullptr);
		}

		Iterator operator+ (int n) const {
			Iterator it = *this;
			it.pointer += n;
			it.index += n;
			return it;
		}
		Iterator operator- (int n) const {
			Iterator it = *this;
			it.pointer -= n;
			it.index -= n;
			return it;
		}
		Iterator operator++ () {
			++this->pointer;
			++this->index;
			return *this;
		}
		Iterator operator-- () {
			--this->pointer;
			--this->index;
			return *this;
		}

		bool operator== (const Iterator& other) const {
			return this->pointer == other.pointer;
		}
		bool operator!= (const Iterator& other) const {
			return !(this->operator==(other));
		}

		void next() override {
			this->operator++();
		}
		void prev() override {
			this->operator--();
		}
		bool is_equel(IIterator<T>* other) const override {
			Iterator* child = dynamic_cast<Iterator*>(other);
			return child != nullptr && this->collection == child->collection && this->index == child->index;
		}

		T get() const override {
			return *(this->pointer);
		}

		T& operator* () {
			return *(this->pointer);
		}
	};

	Iterator begin() {
		return Iterator(this, 0);
	}
	Iterator end() {
		return Iterator(this, this->get_length());
	}
	IIterator<T>* Ibegin() override {
		return new Iterator(this, 0);
	}
	IIterator<T>* Iend() override{
		return new Iterator(this, this->get_length());
	}

	ArraySequence() {
		this->dynamicArray = new DynamicArray<T>();
	}
	ArraySequence(size_t size) {
		this->dynamicArray = new DynamicArray<T>(size);
	}
	ArraySequence(const T* const items, size_t size) {
		this->dynamicArray = new DynamicArray<T>(items, size);
	}
	ArraySequence(const DynamicArray<T>& arr) {
		this->dynamicArray = new DynamicArray<T>(arr);
	}
	ArraySequence(const ArraySequence<T>& other) : Sequence<T>(other) {
		this->dynamicArray = new DynamicArray<T>(*other.dynamicArray);
	}
	Sequence<T>* create() {
		return new ArraySequence<T>();
	}
	Sequence<T>* copy() {
		return new ArraySequence<T>(*(this->dynamicArray));
	}

	T get_first() const override {
		return this->dynamicArray->get(0);
	}
	T get_last() const override {
		return this->dynamicArray->get(this->get_length() - 1);
	}

	T& operator[](int index) override {
		return this->dynamicArray->operator[](index);
	}
	T get(int index) const override {
		return this->dynamicArray->get(index);
	}
	Option<T> try_get(int index) const override {
		return this->dynamicArray->try_get(index);
	}

	Sequence<T>* get_sub_sequence(int startIndex, int endIndex) const override {
		DynamicArray<T>* d = new DynamicArray<T>(endIndex - startIndex);
		for (int i = startIndex, j = 0; i < endIndex; ++i, ++j) {
			(*d)[j] = (*(this->dynamicArray))[i];
		}
		Sequence<T>* res = new ArraySequence<T>(*d);
		return res;
	}

	size_t get_length() const override {
		return this->dynamicArray->get_length();
	}

	void append(T item) override {
		insert_at(item, this->get_length());
	}
	void prepend(T item) override {
		this->insert_at(item, 0);
	}
	void insert_at(T item, int index) override {
		this->dynamicArray->resize(this->get_length() + 1);
		for (int i = this->get_length() - 1; i > index; --i) {
			(*(this->dynamicArray))[i] = this->dynamicArray->get(i - 1);
		}
		(*(this->dynamicArray))[index] = item;
	}

	Sequence <T>* concat(const Sequence <T>* const otherSequence) const override {
		DynamicArray<T>* concatArr = new DynamicArray<T>(this->get_length() + otherSequence->get_length());
		for (int i = 0; i < this->get_length(); ++i) {
			(*(concatArr))[i] = this->get(i);
		}
		for (int i = this->get_length(); i < concatArr->get_length(); ++i) {
			(*(concatArr))[i] = otherSequence->get(i - this->get_length());
		}
		return new ArraySequence<T>(*concatArr);
	}
};
