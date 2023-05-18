#pragma once
#include "Sequence.h"
#include "DynamicArray.h"
#include "IIterator.h"

template <class T>
class ArraySequence : public Sequence<T> {
private:
	DynamicArray<T>* dynamicArray;
public:
	class ConstIterator : public IConstIterator<T> {
	private:
		typename DynamicArray<T>::ConstIterator it;
	public:
		ConstIterator() {}
		ConstIterator(typename DynamicArray<T>::ConstIterator it) : it(it) {}

		ConstIterator operator+ (int n) {
			it = it + n;
			return *this;
		}

		ConstIterator operator- (int n) {
			it = it - n;
			return *this;
		}

		ConstIterator& operator++ () {
			++it;
			return *this;
		}

		ConstIterator operator++ (int) {
			ConstIterator iter = *this;
			++(*this);
			return iter;
		}

		ConstIterator& operator-- () {
			--it;
			return *this;
		}

		ConstIterator operator-- (int) {
			ConstIterator iter = *this;
			--(*this);
			return iter;
		}

		bool operator== (const ConstIterator& other) const {
			return it == other.it;
		}

		bool operator!= (const ConstIterator& other) const {
			return it != other.it;
		}

		void next() override {
			this->operator++();
		}
		void prev() override {
			this->operator--();
		}
		bool is_equal(IConstIterator<T>* other) const override {
			ConstIterator* child = dynamic_cast<ConstIterator*>(other);
			return child != nullptr && *child == *this;
		}

		T get() const override {
			return this->it.get();
		}
	};
	class Iterator : public IIterator<T> {
	private:
		typename DynamicArray<T>::Iterator it;
	public:
		Iterator() {}
		Iterator(typename DynamicArray<T>::Iterator it) : it(it) {}

		Iterator operator+ (int n) {
			it = it + n;
			return *this;
		}

		Iterator operator- (int n) {
			it = it - n;
			return *this;
		}

		Iterator& operator++ () {
			++it;
			return *this;
		}

		Iterator operator++ (int) {
			Iterator iter = *this;
			++(*this);
			return iter;
		}

		Iterator& operator-- () {
			--it;
			return *this;
		}

		Iterator operator-- (int) {
			Iterator iter = *this;
			--(*this);
			return iter;
		}

		bool operator== (const Iterator& other) const {
			return it == other.it;
		}

		bool operator!= (const Iterator& other) const {
			return it != other.it;
		}

		void next() override {
			this->operator++();
		}
		void prev() override {
			this->operator--();
		}
		bool is_equal(IIterator<T>* other) const override {
			Iterator* child = dynamic_cast<Iterator*>(other);
			return child != nullptr && *child == *this;
		}

		T get() const override {
			return this->it.get();
		}

		T& operator* () {
			return *(this->it);
		}
	};

	ConstIterator cbegin() {
		return ConstIterator(this->dynamicArray->cbegin());
	}
	ConstIterator cend() {
		return ConstIterator(this->dynamicArray->cend());
	}
	IConstIterator<T>* Icbegin() const override {
		return new ConstIterator(this->dynamicArray->cbegin());
	}
	IConstIterator<T>* Icend() const override {
		return new ConstIterator(this->dynamicArray->cend());
	}

	Iterator begin() {
		return Iterator(this->dynamicArray->begin());
	}
	Iterator end() {
		return Iterator(this->dynamicArray->end());
	}
	IIterator<T>* Ibegin() override {
		return new Iterator(this->dynamicArray->begin());
	}
	IIterator<T>* Iend() override {
		return new Iterator(this->dynamicArray->end());
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
	ArraySequence(Sequence<T>* sequence) {
		this->dynamicArray = new DynamicArray<T>(sequence->get_length());
		IIterator<T>* it = sequence->Ibegin();
		for (auto it_ = this->dynamicArray->begin(); it_ != this->dynamicArray->end(); ++it_) {
			*it_ = it->get();
			it->next();
		}
	}

	Sequence<T>* create() const override {
		return new ArraySequence<T>();
	}
	Sequence<T>* copy() const override {
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

	T pop() {
		T value = this->get_last();
		this->dynamicArray->resize(this->get_length() - 1);
		return value;
	}
};
