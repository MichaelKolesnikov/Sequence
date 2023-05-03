#include "ArraySequence.h"
#include "LinkedListSequence.h"

using namespace std;

int main() {
	size_t length;
	cin >> length;
	int* data = new int[length];
	for (int i = 0; i < length; ++i) {
		cin >> data[i];
	}
	Sequence<int>* seq1 = new ArraySequence<int>(data, length);
	cout << seq1;
	cout << seq1->try_get(2).value_or(404) << endl;

	
	Sequence<int>* seq2 = new LinkedListSequence<int>(data, length);
	cout << seq2;
	cout << seq2->try_get(2).value_or(404) << endl;
}