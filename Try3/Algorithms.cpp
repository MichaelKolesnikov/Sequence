#include "Algorithms.h"





template<class T>
T reduce(T(*f)(T, T), Sequence<T>* sequence, T c) {
	return T();
}

template<class T>
Sequence<T>* where(bool(*h)(T), Sequence<T>* sequence) {
	return nullptr;
}

template<class T, class ...Args>
Sequence<tuple<Args...>>* zip(Sequence<T>* sequence1, Sequence<T>* sequence) {
	return nullptr;
}

template<class T, class ...Args>
tuple<Args...> unzip(Sequence<T>* sequence1, Sequence<T>* sequence) {
	return tuple<Args...>();
}

template<class T>
Sequence<Sequence<T>>* split(Sequence<T>* sequence, T separator) {
	return nullptr;
}

template<class T>
Sequence<T>* slice(int i, size_t N, Sequence<T>* sequence) {
	return nullptr;
}
