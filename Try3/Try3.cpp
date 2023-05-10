#include "ArraySequence.h"
#include "LinkedListSequence.h"

using namespace std;

int main() {
	size_t length1 = 0, length2;
	int* data = new int[0];
	Sequence<int>* seq1 = new ArraySequence<int>(data, length1);
	cout << seq1;
	cout << seq1->try_get(0).value_or(404) << endl;
	delete[] data;
	seq1->~Sequence();
	delete seq1;

	length1 = 3;
	length2 = 5;
	int* data1 = new int[length1] {1, 2, 3};
	int* data2 = new int[length2] {1, 2, 3, 4, 5};
	seq1 = new ArraySequence<int>(data1, length1);
	Sequence<int>* seq2 = new ArraySequence<int>(data2, length2);
	Sequence<int>* concat = seq1->concat(seq2);
	cout << concat;

	Sequence<double>* mapped = map_sequence<double, LinkedListSequence<double>, int>([](int x) {return (double)x / 2;}, seq1);
	cout << mapped;
}