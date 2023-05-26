#include "pch.h"
#include "..\Try3\ArraySequence.h"
#include "..\Try3\LinkedListSequence.h"
#include "..\Try3\Vector.h"
#include "..\Try3\NumberTheory.h"
#include "..\Try3\PermutationGenerator.h"
#include "..\Try3\Stack.h"
#include "..\Try3\HanoiTowers.h"

using namespace std;

TEST(ISequence, ArraySequence) {
	ISequence<float>* s1 = new ArraySequence<float>();
	ISequence<double>* s2 = new ArraySequence<double>(5);
	int* data = new int[]{ 0, 1, 2, 3, 4 };
	ISequence<int>* s3 = new ArraySequence<int>(data, 5);
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(data[i], s3->get(i));
	}
	char* d = new char[] {'a', 'b', 'c'};
	ISequence<char>* s4 = new ArraySequence<char>(d, 3);
	ISequence<char>* s5 = new ArraySequence<char>(s4);
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
	ISequence<float>* s1 = new LinkedListSequence<float>();
	ISequence<double>* s2 = new LinkedListSequence<double>(5);
	int* data = new int[] { 0, 1, 2, 3, 4 };
	ISequence<int>* s3 = new LinkedListSequence<int>(data, 5);
	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(data[i], s3->get(i));
	}
	char* d = new char[] {'a', 'b', 'c'};
	ISequence<char>* s4 = new LinkedListSequence<char>(d, 3);
	ISequence<char>* s5 = new LinkedListSequence<char>(s4);
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
	ISequence<int>& s1 = *(new ArraySequence<int>(new int[] {1, 2, 3, 4, 5, 6}, 6));
	int left, right;

	left = 0, right = 1;
	ISequence<int>* sub = &s1.get_sub_sequence(left, right);
	EXPECT_EQ(sub->get_length(), 1);
	EXPECT_EQ(sub->get(0), s1.get(0));
	delete sub;

	left = 5, right = 6;
	sub = &s1.get_sub_sequence(left, right);
	EXPECT_EQ(sub->get_length(), 1);
	EXPECT_EQ(sub->get(0), s1.get(5));
	delete sub;

	left = 2, right = 4;
	sub = &s1.get_sub_sequence(left, right);
	EXPECT_EQ(sub->get_length(), 4 - 2);
	IIterator<int>* it1 = s1.Ibegin();
	it1->next();
	it1->next();
	for (IConstIterator<int>* it2 = sub->Icbegin(); 
		!(it2->is_equal(sub->Icend())); 
		it2->next(), 
		it1->next()) 
	{
		EXPECT_EQ(it1->get(), it2->get());
	}
	delete it1;
	delete sub;
	delete& s1;
}

TEST(Sequence, concat) {
	ISequence<int>& s1 = *(new LinkedListSequence<int>(new int[] {4, 8, 0, 1, 2, 3}, 6));
	ISequence<int>& s2 = *(new ArraySequence<int>(new int[] {6, 9, 0, 1, 4, 2, 3, 7}, 8));
	ISequence<int>& concated = s1.concat(s2);
	int i = 0;
	ISequence<int>* cur_seq = &s1;
	for (IConstIterator<int>* it = concated.Icbegin(); !(it->is_equal(concated.Icend())); it->next()) {
		EXPECT_EQ(it->get(), cur_seq->get(i));
		++i;
		if (i == cur_seq->get_length()) {
			cur_seq = &s2;
			i = 0;
		}
	}
	delete &s1;
	delete &s2;
	delete &concated;
}

TEST(Sequence, find) {
	ISequence<int>& s1 = *(new LinkedListSequence<int>(new int[] {5, 9, 0, 1, 2}, 5));
	auto f = [](int x) {return x % 2 == 0;};
	ISequence<int>& whered = s1.find(f);
	IIterator<int>* it1 = whered.Ibegin();
	for (IConstIterator<int>* it = s1.Icbegin(); !(it->is_equal(s1.Icend())) && !(whered.Iend()); it->next()) {
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
	ISequence<int>* s1 = new ArraySequence<int>(new int[] {4, 6, 1, 7}, 4);
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
	ISequence<int>& s1 = *(new LinkedListSequence<int>(new int[] {3, 6, 9, 1, 2}, 5));
	ISequence<double>& mapped = map_sequence<double, ArraySequence<double>, int>([](int x) {return (double)x / 2;}, s1);
	auto it = mapped.Ibegin();
	for (auto it1 = s1.Ibegin(); !(it->is_equal(mapped.Iend())); it->next(), it1->next()) {
		EXPECT_EQ(it->get(), (double)it1->get() / 2);
	}
	delete &s1;
	delete &mapped;
}

TEST(Vector, operations) {
	size_t size = 5;
	int* data1 = new int[size];
	for (size_t i = 0; i < size; ++i) {
		data1[i] = rand();
	}
	Vector<int> vector1(DynamicArray<int>(data1, size));

	int* data2 = new int[size];
	for (size_t i = 0; i < size; ++i) {
		data2[i] = rand();
	}
	Vector<int> vector2(DynamicArray<int>(data2, size));

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

TEST(EratosthenesSieve, prime_) {
	int n = 1e5;
	EratosthenesSieve Eratosthene(n);
	for (int i = 0; i < n; ++i) {
		EXPECT_EQ(prime(i), Eratosthene.is_prime(i));
	}
}

TEST(Factorizer, factorize) {
	int size = 1e3;
	EratosthenesSieve Eratosthenes_sieve(size);
	Factorizer factorizer(size);
	int (*multiply)(int, int) = [](int a, int b) -> int {return a * b;};
	for (int i = 1; i < size; ++i) {
		ArraySequence<int> divisors = factorizer.factorize(i);
		for (IConstIterator<int>* it = divisors.Icbegin(); !(it->is_equal(divisors.Icend())); it->next()) {
			EXPECT_EQ(true, Eratosthenes_sieve.is_prime(it->get()));
		}
		EXPECT_EQ(divisors.reduce(multiply, 1), i);
	}
}

TEST(PermutationGenerator, generate_permutation) {
	int size = 10;
	int* data = new int[size];
	for (int i = 0; i < size; ++i) {
		data[i] = i;
	}
	PermutationGenerator<int> generator(ArraySequence<int>(data, size));
	for (int i = 0; i < 10; ++i) {
		cout << generator.generate_permutation();
	}
}

TEST(Stack, stack) {
	Stack<int> stack = Stack<int>();
	stack.push(5);
	EXPECT_EQ(stack.peek(), 5);
	stack.push(8);
	EXPECT_EQ(8, stack.pop());
	EXPECT_EQ(5, stack.pop());
	EXPECT_EQ(true, stack.is_empty());
}

TEST(HanoiTowers, solve_Hanoi_towers) {
	int n = 20;
	Ring* rings = new Ring[n];
	for (int i = n - 1; i >= 0; --i) {
		rings[n - i - 1] = Ring(i + 1, i + 1);
	}
	ArraySequence<Ring> Rings = ArraySequence<Ring>(rings, n);
	HanoiTowers Hanoi_towers(Rings, (size_t)0, (size_t)2);
	solve_Hanoi_towers(Hanoi_towers);
	EXPECT_EQ(Hanoi_towers.is_win(), true);
}


