#pragma once

#include "Vector.h"

//template <class T>
//class Matrix {
//private:
//	Vector<Vector<T>> matrix;
//public:
//	Matrix() {}
//	Matrix(const Vector<Vector<T>>& matrix) {
//		this->matrix = Vector<Vector<T>>(matrix);
//	}
//
//	template <class T>
//	Matrix<T>& operator=(const Matrix<T>& other) {
//		if (this != &other) {
//			this->matrix = other.matrix;
//		}
//		return *this;
//	}
//
//	size_t get_m() const {
//		return this->matrix.get_dimension();
//	}
//
//	size_t get_n() const {
//		if (this->get_m() > 0) {
//			return this->matrix.get(0).get_dimension();
//		}
//		return 0;
//	}
//
//	Vector<T> get(int string) const {
//		return this->matrix.get(string);
//	}
//
//	friend std::ostream& operator<< (std::ostream& stream, const Matrix<T>& matrix) {
//		stream << std::endl << "[";
//		for (int i = 0; i < matrix.get_m(); ++i) {
//			stream << matrix.get(i);
//		}
//		stream << "]" << std::endl;
//		return stream;
//	}
//};

