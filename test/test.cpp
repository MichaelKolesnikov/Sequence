#include "pch.h"
#include "..\Try3\ArraySequence.h"
#include "..\Try3\LinkedListSequence.h"

using namespace std;

TEST(TestCaseName, TestName) {
	Sequence<float>* nothing1 = new ArraySequence<float>(0);
	Sequence<float>* nothing2 = new LinkedListSequence<float>(0);

	int n = 10;
	int* m = new int[n];
	for (int i = 0; i < n; ++i) {
		m[i] = i;
	}
	Sequence<int>* sequence1 = new ArraySequence<int>(m, n);
	Sequence<int>* sequence2 = new LinkedListSequence<int>(m, n);
	for (int i = 0; i < n; ++i) {
		EXPECT_EQ(sequence1->get(i), sequence2->get(i));
	}
	for (IIterator<int>* it1 = sequence1->Ibegin(), *it2 = sequence2->Ibegin(); 
		!(it1->is_equel(sequence1->Iend())) && !(it2->is_equel(sequence2->Iend())); 
	it1->next(), it2->next()) {
		auto val = it1->get();
		EXPECT_EQ(it1->get(), it2->get());
		it1->operator*() = 505;
		it2->operator*() = 505;
		EXPECT_EQ(it1->get(), it2->get());
		it1->operator*() = val;
		it2->operator*() = val;
	}
	Sequence<int>* concated = sequence1->concat(sequence2);
	int i = 0;
	Sequence<int>* cur_seq = sequence1;
	for (IIterator<int>* it = concated->Ibegin(); !(it->is_equel(concated->Iend())); it->next()) {
		EXPECT_EQ(it->get(), cur_seq->get(i));
		++i;
		if (i == cur_seq->get_length()) {
			cur_seq = sequence2;
			i = 0;
		}
	}
	Sequence<double>* mapped = map_sequence<double, ArraySequence<double>, int>([](int x) {return (double)x / 2;}, sequence1);
	auto it = mapped->Ibegin();
	for (auto it1 = sequence1->Ibegin(); !(it->is_equel(mapped->Iend())); it->next(), it1->next()) {
		EXPECT_EQ(it->get(), (double)it1->get() / 2);
	}
	auto f = [](int x) {return x % 2 == 0;};
	Sequence<int>* whered = sequence1->where(f);
	for (IIterator<int>* it = sequence1->Ibegin(), *it1 = whered->Ibegin(); !(it->is_equel(sequence1->Iend())) && !(whered->Iend()); it->next()) {
		if (f(it->get())) {
			if (f(it->get())) {
				EXPECT_EQ(it->get(), it1->get());
				if (it->get() != it1->get()) {
					break;
				}
				it1->next();
			}
		}
	}
	auto val = sequence1->reduce([](int x, int y) {return x + y;}, 100);
	cout << val;

}