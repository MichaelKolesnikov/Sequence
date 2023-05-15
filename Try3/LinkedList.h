#pragma once
#include <ostream>
#include <stdlib.h>
#include <string.h>
#include "IndexOutOfRange.h"
#include "ICollection.h"

using namespace std;

template <class T>
class NodeList {
public:
	T value;
	NodeList<T>* prev;
	NodeList<T>* next;

	NodeList() {
		this->value = T();
		this->prev = nullptr;
		this->next = nullptr;
	}
	NodeList(T value, NodeList<T>* prev, NodeList<T>* next) {
		this->value = value;
		this->prev = prev;
		this->next = next;
	}
};

template <class T>
class LinkedList : ICollection<T> {
private:
	class BaseIterator {
	protected:
		NodeList<T>* current;
	public:
		BaseIterator() : current(nullptr) {}

		BaseIterator(LinkedList<T> list) : current(list.head) {}

		BaseIterator(NodeList<T>* first) : current(first) {}

		BaseIterator operator+ (int n) {
			size_t counter = 0;
			while (counter != n) {
				current = this->current->next;
				counter++;
			}
			return *this;
		}

		BaseIterator operator- (int n) {
			size_t counter = 0;
			while (counter != n) {
				this->current = this->current->prev;
				counter++;
			}
			return *this;
		}

		BaseIterator operator++ (int) { current = current->next; return *this; }
		BaseIterator operator-- (int) { current = current->prev; return *this; }
		BaseIterator operator++ () { current = current->next; return *this; }
		BaseIterator operator-- () { current = current->prev; return *this; }

		bool operator!= (const BaseIterator& other) const { return this->current != other.current; }
		bool operator== (const BaseIterator& other) const { return this->current == other.current; }

		T get() const { return this->current->value; }
	};
	size_t length;
	NodeList<T>* head;
	NodeList<T>* tail;
public:
	class ConstIterator : public BaseIterator {
	public:
		ConstIterator() : BaseIterator() {}
		ConstIterator(LinkedList<T> list) : BaseIterator(list) {}
		ConstIterator(NodeList<T>* first) : BaseIterator(first) {}
	};
	class Iterator: public BaseIterator {
	public:
		Iterator(): BaseIterator() {}
		Iterator(LinkedList<T> list): BaseIterator(list) {}
		Iterator(NodeList<T>* first): BaseIterator(first) {}

		T& operator* () { return this->current->value; }
	};
	ConstIterator cbegin() const { return ConstIterator(this->head); }
	ConstIterator cend() const { return ConstIterator(this->tail->next); }
	Iterator begin() noexcept { return Iterator(this->head); }
	Iterator end() noexcept { return Iterator(this->tail->next); }

	LinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
		this->length = 0;
	}
	LinkedList(size_t length) {
		this->length = length;
		if (length == 0) {
			*this = LinkedList<T>();
			return;
		}
		this->head = new NodeList<T>;
		NodeList<T>* node = this->head;
		for (size_t i = 1; i < length; ++i) {
			node->next = new NodeList<T>;
			node->next->prev = node;
			node = node->next;
		}
		this->tail = node;
	}
	LinkedList(const T* const items, size_t length) :LinkedList(length) {
		int i = -1;
		for (NodeList<T>* node = this->head; node != nullptr; node = node->next) {
			node->value = items[++i];
		}
	}
	LinkedList(const LinkedList <T>& list) : LinkedList(list.length) {
		for (NodeList<T>* node = this->head, *newNode = list.head; newNode != nullptr; node = node->next, newNode = newNode->next) {
			node->value = newNode->value;
		}
	}

	T get_first() const {
		if (this->length == 0) {
			throw IndexOutOfRange();
		}
		return this->head->value;
	}
	T get_last() const {
		if (this->length == 0) {
			throw IndexOutOfRange();
		}
		return this->tail->value;
	}

	T& operator[](int index) {
		if (index < 0 || this->length <= index) {
			throw IndexOutOfRange();
		}
		int i = 0;
		NodeList<T>* node = this->head;
		for (; i < index; node = node->next, ++i) {}
		return node->value;
	}

	T get(int index) const override {
		if (this->length <= index) {
			throw IndexOutOfRange();
		}
		int i = 0;
		NodeList<T>* node = this->head;
		for (; node != nullptr && i != index; node = node->next, ++i) {}
		return node->value;
	}

	Option<T> try_get(int index) const override {
		if (index < 0 || this->length <= index) {
			return Option<T>();
		}
		return Option<T>(this->get(index));
	}

	LinkedList<T>* get_sub_list(size_t startIndex, size_t endIndex) const {
		if (startIndex >= this->length || endIndex > this->length) {
			throw IndexOutOfRange();
		}
		LinkedList<T>* subList = new LinkedList<T>(endIndex - startIndex);
		NodeList<T>* node = this->head;
		int i = 0;
		for (; i != startIndex; ++i, node = node->next) {}
		NodeList<T>* subNode = subList->head;
		for (; i < endIndex; ++i, node = node->next, subNode = subNode->next) {
			subNode->value = node->value;
		}
		return subList;
	}

	size_t get_length() const override {
		return this->length;
	}

	void append(T item) {
		if (this->length == 0) {
			*this = LinkedList<T>(&item, 1);
			return;
		}
		this->tail->next = new NodeList<T>(item, this->tail, nullptr);
		this->tail = this->tail->next;
		++this->length;
	}
	void prepend(T item) {
		if (this->length == 0) {
			*this = LinkedList<T>(&item, 1);
			return;
		}
		this->head->prev = new NodeList<T>(item, nullptr, this->head);
		this->head = this->head->prev;
		++this->length;
	}
	void insert_at(T item, size_t index) {
		if (this->length < index) {
			throw IndexOutOfRange();
		}
		if (index == 0) {
			this->prepend(item);
			return;
		}
		if (index == this->length) {
			this->append(item);
			return;
		}
		int i = 0;
		NodeList<T>* node = this->head;
		for (;i != index; node = node->next, ++i) {}
		NodeList<T>* newNode = new NodeList<T>(item, node->prev, node);
		node->prev->next = newNode;
		++this->length;
	}

	LinkedList<T>* concat(LinkedList<T>* list) {
		LinkedList<T>* list1 = new LinkedList<T>(*this);
		LinkedList<T>* list2 = new LinkedList<T>(*list);
		list1->tail->next = list2->head;
		list2->head->prev = list1->tail;
		list1->length = list1->length + list2->length;
		return list1;
	}

	~LinkedList() {
		if (this->head == nullptr) {
			return;
		}
		NodeList<T>* node = this->head->next;
		for (; node != nullptr; node = node->next) {
			delete node->prev;
			node->prev = nullptr;
		}
		delete node;
	}

	friend std::ostream& operator<< (std::ostream& stream, const LinkedList<T>& list) {
		stream << std::endl;
		stream << list.get_length() << std::endl;
		for (auto it = list.cbegin(); it != nullptr; ++it) {
			stream << it.get() << " ";
		}
		stream << std::endl;
		return stream;
	}
};
