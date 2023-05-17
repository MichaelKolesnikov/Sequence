#pragma once
#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class LinkedListSequence : public Sequence<T> {
private:
	LinkedList<T>* linked_list;
public:
	class ConstIterator : public IConstIterator<T> {
	private:
		typename LinkedList<T>::ConstIterator it;
	public:
		ConstIterator() {}
		ConstIterator(typename LinkedList<T>::ConstIterator it) : it(it) {}

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
		typename LinkedList<T>::Iterator it;
	public:
		Iterator() {}
		Iterator(typename LinkedList<T>::Iterator it) : it(it) {}

		Iterator operator+ (int n) {
			this->it = this->it + n;
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

	ConstIterator cbegin() const {
		return ConstIterator(this->linked_list->cbegin());
	}
	ConstIterator cend() const {
		return ConstIterator(this->linked_list->cend());
	}

	IConstIterator<T>* Icbegin() const override {
		return new ConstIterator(this->linked_list->cbegin());
	}
	IConstIterator<T>* Icend() const override {
		return new ConstIterator(this->linked_list->cend());
	}

	Iterator begin() {
		return Iterator(this->linked_list->begin());
	}
	Iterator end() {
		return Iterator(this->linked_list->end());
	}
	
	IIterator<T>* Ibegin() override {
		return new Iterator(this->linked_list->begin());
	}
	IIterator<T>* Iend() override {
		return new Iterator(this->linked_list->end());
	}

	LinkedListSequence() {
		this->linked_list = new LinkedList<T>();
	}
	LinkedListSequence(size_t length) {
		this->linked_list = new LinkedList<T>(length);
	}
	LinkedListSequence(T* items, size_t length) {
		this->linked_list = new LinkedList<T>(items, length);
	}
	LinkedListSequence(const LinkedList<T>& list) {
		this->linked_list = new LinkedList<T>(list);
	}
	LinkedListSequence(const LinkedListSequence<T>& other) : Sequence<T>(other) {
		this->linked_list = new LinkedList<T>(*other.linked_list);
	}
	LinkedListSequence(Sequence<T>* sequence) {
		this->linked_list = new LinkedList<T>(sequence->get_length());
		IIterator<T>* it = sequence->Ibegin();
		for (auto it_ = this->linked_list->begin(); it_ != this->linked_list->end(); ++it_) {
			*it_ = it->get();
			it->next();
		}
	}
	Sequence<T>* create() const {
		return new LinkedListSequence<T>();
	}
	Sequence<T>* copy() const {
		return new LinkedListSequence<T>(*this);
	}

	T get_first() const override {
		return this->linked_list->get_first();
	}
	T get_last() const override {
		return this->linked_list->get_last();
	}

	T& operator[](int index) override {
		return this->linked_list->operator[](index);
	}
	T get(int index) const override {
		return this->linked_list->get(index);
	}
	Option<T> try_get(int index) const override {
		return this->linked_list->try_get(index);
	}

	size_t get_length() const override {
		return this->linked_list->get_length();
	}

	void append(T item) override {
		this->linked_list->append(item);
	}
	void prepend(T item) override {
		this->linked_list->prepend(item);
	}
	void insert_at(T item, int index) override {
		this->linked_list->insert_at(item, index);
	}
};
