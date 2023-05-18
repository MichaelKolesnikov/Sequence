#pragma once

#include "ArraySequence.h"

template <class T>
class Stack {
private:
	ArraySequence<T> stack = ArraySequence<T>();

	T get(int index) const {
		return this->stack.get(index);
	}
public:
	Stack() {}

	void push(T item) {
		this->stack.append(item);
	}

	T pop() {
		return this->stack.pop();
	}

	T peek() const {
		return stack.get_last();
	}

	bool is_empty() const {
		return this->stack.get_length() == 0;
	}

	int get_size() const {
		return this->stack.get_length();
	}

	friend std::ostream& operator<< (std::ostream& stream, const Stack<T>& stack) {
		stream << std::endl;
		for (int i = 0; i < stack.get_size(); ++i) {
			stream << stack.get(i) << " ";
		}
		stream << std::endl;
		return stream;
	}
};
