#pragma once
#include "Enumerator.h"

template<class T>
class Enumerable {
public:
	Enumerable() = default;
	virtual Enumerator<T>* GetEnumerator() = 0;
};
