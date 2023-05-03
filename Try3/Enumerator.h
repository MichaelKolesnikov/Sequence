#pragma once

template<class T>
class Enumerator {
public:
	Enumerator() = default;
	virtual T Current() = 0;
	virtual bool MoveNext() = 0;
	virtual void Reset() = 0;
};
