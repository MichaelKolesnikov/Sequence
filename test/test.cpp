#include "pch.h"
#include "..\Try3\ArraySequence.h"
#include "..\Try3\LinkedListSequence.h"
#include "..\Try3\Vector.h"
#include "..\Try3\NumberTheory.h"

using namespace std;

TEST(Sequence, ArraySequence) {
	Sequence<float>* s1 = new ArraySequence<float>();
	Sequence<double>* s2 = new ArraySequence<double>(5);
	int* data = new int[]{ 0, 1, 2, 3, 4 };
	Sequence<int>* s3 = new ArraySequence<int>(data, 5);
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(data[i], s3->get(i));
	}
	char* d = new char[] {'a', 'b', 'c'};
	Sequence<char>* s4 = new ArraySequence<char>(d, 3);
	Sequence<char>* s5 = new ArraySequence<char>(s4);
	for (int i = 0; i < 3; ++i) {
		EXPECT_EQ(s4->get(i), s5->get(i));
	}
	delete s1;
	delete s2;
	delete s3;
	delete s4;
	delete s5;
	delete[] data;
	delete[] d;
}

TEST(Sequence, LinkedListSequence) {
	Sequence<float>* s1 = new LinkedListSequence<float>();
	Sequence<double>* s2 = new LinkedListSequence<double>(5);
	int* data = new int[] { 0, 1, 2, 3, 4 };
	Sequence<int>* s3 = new LinkedListSequence<int>(data, 5);
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(data[i], s3->get(i));
	}
	char* d = new char[] {'a', 'b', 'c'};
	Sequence<char>* s4 = new LinkedListSequence<char>(d, 3);
	Sequence<char>* s5 = new LinkedListSequence<char>(s4);
	for (int i = 0; i < 3; ++i) {
		EXPECT_EQ(s4->get(i), s5->get(i));
	}
	delete s1;
	delete s2;
	delete s3;
	delete s4;
	delete s5;
	delete[] data;
	delete[] d;
}

TEST(Sequence, get_sub_sequence) {
	Sequence<int>* s1 = new ArraySequence<int>(new int[] {1, 2, 3, 4, 5, 6}, 6);
	Sequence<int>* sub;
	int left, right;

	left = 0, right = 1;
	sub = s1->get_sub_sequence(left, right);
	EXPECT_EQ(sub->get_length(), 1);
	EXPECT_EQ(sub->get(0), s1->get(0));
	delete sub;

	left = 5, right = 6;
	sub = s1->get_sub_sequence(left, right);
	EXPECT_EQ(sub->get_length(), 1);
	EXPECT_EQ(sub->get(0), s1->get(5));
	delete sub;

	left = 2, right = 4;
	sub = s1->get_sub_sequence(left, right);
	EXPECT_EQ(sub->get_length(), 4 - 2);
	IIterator<int>* it1 = s1->Ibegin();
	it1->next();
	it1->next();
	for (IIterator<int>* it2 = sub->Ibegin(); !(it2->is_equal(sub->Iend())); it2->next(), it1->next()) {
		EXPECT_EQ(it1->get(), it2->get());
	}
	delete it1;
	delete sub;
}

TEST(Sequence, concat) {
	Sequence<int>* s1 = new LinkedListSequence<int>(new int[] {4, 8, 0, 1, 2, 3}, 6);
	Sequence<int>* s2 = new ArraySequence<int>(new int[] {6, 9, 0, 1, 4, 2, 3, 7}, 8);
	Sequence<int>* concated = s1->concat(s2);
	int i = 0;
	Sequence<int>* cur_seq = s1;
	for (IIterator<int>* it = concated->Ibegin(); !(it->is_equal(concated->Iend())); it->next()) {
		EXPECT_EQ(it->get(), cur_seq->get(i));
		++i;
		if (i == cur_seq->get_length()) {
			cur_seq = s2;
			i = 0;
		}
	}
	delete s1;
	delete s2;
	delete concated;
}

TEST(Sequence, find) {
	Sequence<int>* s1 = new LinkedListSequence<int>(new int[] {5, 9, 0, 1, 2}, 5);
	auto f = [](int x) {return x % 2 == 0;};
	Sequence<int>* whered = s1->find(f);
	for (IIterator<int>* it = s1->Ibegin(), *it1 = whered->Ibegin(); !(it->is_equal(s1->Iend())) && !(whered->Iend()); it->next()) {
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
}

TEST(Sequence, reduce) {
	Sequence<int>* s1 = new ArraySequence<int>(new int[] {4, 6, 1, 7}, 4);
	int base = 100;
	auto f = [](int x, int y) {return x + y;};
	auto val = s1->reduce(f, base);
	for (IIterator<int>* it = s1->Iend(); !(it->is_equal(s1->Ibegin()));) {
		it->prev();
		base = f(it->get(), base);
	}
	EXPECT_EQ(val, base);
	delete s1;
}

TEST(Sequence, map_sequence) {
	Sequence<int>* s1 = new LinkedListSequence<int>(new int[] {3, 6, 9, 1, 2}, 5);
	Sequence<double>* mapped = map_sequence<double, ArraySequence<double>, int>([](int x) {return (double)x / 2;}, s1);
	auto it = mapped->Ibegin();
	for (auto it1 = s1->Ibegin(); !(it->is_equal(mapped->Iend())); it->next(), it1->next()) {
		EXPECT_EQ(it->get(), (double)it1->get() / 2);
	}
	delete s1;
	delete mapped;
}

TEST(Vector, operations) {
	size_t size = 5;
	int* data1 = new int[size];
	for (size_t i = 0; i < size; ++i) {
		data1[i] = rand();
	}
	Vector<int> vector1(new DynamicArray<int>(data1, size));

	int* data2 = new int[size];
	for (size_t i = 0; i < size; ++i) {
		data2[i] = rand();
	}
	Vector<int> vector2(new DynamicArray<int>(data2, size));

	int s = 0;
	for (int i = 0; i < size; ++i) {
		s += data1[i] * data2[i];
	}
	EXPECT_EQ(s, vector1 * vector2);

	int alpha = 66;
	Vector<int> vector3 = alpha * vector1;
	for (size_t i = 0; i < vector3.get_dimension(); ++i) {
		EXPECT_EQ(data1[i] * alpha, vector3.get(i));
	}

	s = 0;
	for (int i = 0; i < size; ++i) {
		s += data1[i] * data1[i];
	}
	EXPECT_EQ((int)sqrt(s), vector1.norm());
}

TEST(EratosthenesSieve, is_prime) {
	int n = 1e5;
	EratosthenesSieve Eratosthene(n);
	for (int i = 0; i < n; ++i) {
		EXPECT_EQ(is_prime(i), Eratosthene.is_prime(i));
	}
}

TEST(Factorizer, factorize) {
	int size = 1e3;
	EratosthenesSieve Eratosthenes_sieve(size);
	Factorizer factorizer(size);
	int (*multiply)(int, int) = [](int a, int b) -> int {return a * b;};
	for (int i = 1; i < size; ++i) {
		ArraySequence<int>* divisors = factorizer.factorize(i);
		for (IConstIterator<int>* it = divisors->Icbegin(); !(it->is_equal(divisors->Icend())); it->next()) {
			EXPECT_EQ(true, Eratosthenes_sieve.is_prime(it->get()));
		}
		EXPECT_EQ(divisors->reduce(multiply, 1), i);
		delete divisors;
	}
}
