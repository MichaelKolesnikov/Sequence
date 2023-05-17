#pragma once
#include "DynamicArray.h"
#include <cmath>

template <class T>
class Vector {
private:
	DynamicArray<T>* dynamic_array;
public:
	Vector(DynamicArray<T>* dynamic_array) {
		this->dynamic_array = new DynamicArray<T>(*dynamic_array);
	}

	T get(int index) const {
		return this->dynamic_array->get(index);
	}

	size_t get_dimension() const {
		return this->dynamic_array->get_length();
	}

	T operator*(const Vector<T>& vector) const {
		T value = this->get(0) * vector.get(0);
		for (int i = 1; i < this->get_dimension(); ++i) {
			value += this->dynamic_array->get(i) * vector.get(i);
		}
		return value;
	}

	Vector<T> operator*(T alpha) const {
		DynamicArray<T>* d = new DynamicArray<T>(this->get_dimension());
		for (int i = 0; i < d->get_length(); ++i) {
			d->operator[](i) = this->get(i) * alpha;
		}
		return Vector<T>(d);
	}

	T norm() const {
		T squared_sum = this->get(0) * this->get(0);
		for (int i = 1; i < this->get_dimension(); ++i) {
			squared_sum += this->get(i) * this->get(i);
		}
		return sqrt(squared_sum);
	}

	~Vector() {
		delete this->dynamic_array;
	}

	friend std::ostream& operator<< (std::ostream& stream, const Vector<T>& vector) {
		stream << std::endl << "[";
		for (size_t i = 0; i < vector.get_dimension(); ++i) {
			stream << vector.get(i) << " ";
		}
		stream << "]" << std::endl;
		return stream;
	}

	friend Vector<T> operator*(const T alpha, const Vector<T>& vector) {
		return vector * alpha;
	}
};
