#pragma once
#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class LinkedListSequence : public Sequence<T> {
private:
	LinkedList<T>* linked_list;
public:
	class Iterator : public IIterator<T> {
	private:
		typename LinkedList<T>::Iterator it;
	public:
		Iterator(LinkedListSequence<T>* seq, int index) {
			this->collection = seq;
			this->index = index;
			this->it = seq->linked_list->begin();
			for (int i = 0; i < index && i < seq->get_length(); ++i) {
				++(this->it);
			}
		}

		Iterator operator+ (int n) const {
			Iterator it = *this;
			it.it += n;
			it.index += n;
			return it;
		}
		Iterator operator- (int n) const {
			Iterator it = *this;
			it.it -= n;
			it.index -= n;
			return it;
		}
		Iterator operator++ () {
			++(this->it);
			++this->index;
			return *this;
		}
		Iterator operator-- () {
			--(this->it);
			--this->index;
			return *this;
		}

		bool operator== (const Iterator& other) const {
			return (this->it) == other.it;
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
			return this->it.get();
		}

		T& operator* () {
			return *(this->it);
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
	IIterator<T>* Iend() override {
		return new Iterator(this, this->get_length());
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

	Sequence<T>* get_sub_sequence(int startIndex, int endIndex) const override {
		LinkedList<T>* subList = this->linked_list->get_sub_list(startIndex, endIndex);
		Sequence<T>* seq = new LinkedListSequence<T>(*subList);
		delete subList;
		return seq;
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
