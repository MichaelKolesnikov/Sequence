#include "pch.h"
#include "D:/МИФИ/Семестр 2/Программирование/Лабы/лаб2/Try3/Try3/ArraySequence.h"
#include "D:/МИФИ/Семестр 2/Программирование/Лабы/лаб2/Try3/Try3/LinkedListSequence.h"

TEST(TestCaseName, TestName) {
	int n;
	cin >> n;
	int* m = new int[n];
	for (int i = 0; i < n; ++i) {
		m[i] = i;
	}
	Sequence<int>* sequence1 = new ArraySequence<int>(m, n);
	Sequence<int>* sequence2 = new LinkedListSequence<int>(m, n);
	for (int i = 0; i < n; ++i) {
		EXPECT_EQ(sequence1[i],  sequence2[i]);
	}
}