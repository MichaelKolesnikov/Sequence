#pragma once
#include <iostream>

using namespace std;

class IndexOutOfRange : public exception {
public:
	IndexOutOfRange() :exception("index is negative or greater than/equal to number of elements") {}
};
