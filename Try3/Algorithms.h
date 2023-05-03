#pragma once
#include <tuple>

#include "Sequence.h"

using namespace std;

template<class T>
Sequence<T>* map(T(*f)(T), Sequence<T>* sequence) {
    return nullptr;
}

template <class T>
T reduce(T(*f)(T, T), Sequence<T>* sequence, T c);

template <class T>
Sequence<T>* where(bool (*h)(T), Sequence<T>* sequence);

template<class T, class... Args>
Sequence<tuple<Args...>>* zip(Sequence<T>* sequence1, Sequence<T>* sequence);

template<class T, class... Args>
tuple<Args...> unzip(Sequence<T>* sequence1, Sequence<T>* sequence);

template <class T>
Sequence<Sequence<T>>* split(Sequence<T>* sequence, T separator);

template <class T>
Sequence<T>* slice(int i, size_t N, Sequence<T>* sequence);
