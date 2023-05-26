#include "ArraySequence.h"
#include "LinkedListSequence.h"
#include <typeinfo>
#include "Vector.h"
#include "NumberTheory.h"
#include "HanoiTowers.h"
#include "PermutationGenerator.h"

using namespace std;

template <class T>
void process_sequence(ISequence<T>* sequence, bool(*f_find)(T x), T(*f_reduce)(T a, T b), T(*f_map)(T x)) {
	// couts of possible actions
	{
		cout << "Select the operation to be performed on the sequence" << endl;
		cout << "1: get_length" << endl;
		cout << "2: get item" << endl;
		cout << "3: get sub sequence" << endl;
		cout << "4: append" << endl;
		cout << "5: prepend" << endl;
		cout << "6: insert at" << endl;
		cout << "7: concat" << endl;
		cout << "8: find" << endl;
		cout << "9: reduce" << endl;
		cout << "10: EXIT" << endl;
		cout << "11: print" << endl;
		cout << "12: map" << endl;
	}
	
	bool working = true;
	while (working) {
		string operation;
		cin >> operation;

		if (operation == "1") {
			cout << sequence->get_length() << endl;
		}
		else if (operation == "2") {
			cout << "enter an index" << endl;
			int index;
			cin >> index;
			Option<T> option = sequence->try_get(index);
			if (option.has_value()) {
				cout << option.value() << endl;
			}
			else {
				cout << "You entered the wrong index" << endl;
			}
		}
		else if (operation == "3") {
			cout << "Enter the left and right index" << endl;
			int l, r;
			cin >> l >> r;
			if (!(0 <= l && l <= r && r <= sequence->get_length())) {
				cout << "You entered the wrong indexes" << endl;
				continue;
			}
			ISequence<T>& sub = sequence->get_sub_sequence(l, r);
			cout << sub;
			cout << "Do you want to keep the cropped version? (then the old one will be lost) y/n" << endl;
			string choice;
			cin >> choice;
			if (choice == "y") {
				delete sequence;
				*sequence = sub;
			}
			else {
				delete &sub;
			}
		}
		else if (operation == "4") {
			T value;
			cout << "Enter a value" << endl;
			cin >> value;
			sequence->append(value);
		}
		else if (operation == "5") {
			T value;
			cout << "Enter a value" << endl;
			cin >> value;
			sequence->prepend(value);
		}
		else if (operation == "6") {
			int index;
			cout << "Enter an index" << endl;
			cin >> index;
			if (!(0 <= index && index <= sequence->get_length())) {
				cout << "You entered the wrong indexes" << endl;
				continue;
			}
			T value;
			cout << "Enter a value" << endl;
			cin >> value;
			sequence->insert_at(value, index);
		}
		else if (operation == "7") {
			int n;
			cout << "Enter the length of the collection to be added" << endl;
			if (!(cin >> n)) {
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "wrong input format" << endl;
				continue;
			}
			T* data = new T[n];
			cout << "Enter the elements of the sequence to be added" << endl;
			for (int i = 0; i < n; ++i) {
				if (!(cin >> data[i])) {
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << "wrong input format" << endl;
					break;
				}
			}
			ISequence<T>& added = *(new ArraySequence<T>(data, n));
			ISequence<T>& concated = sequence->concat(added);
			delete sequence;
			delete &added;
			sequence = &concated;
		}
		else if (operation == "8") {
			ISequence<T>& whered = sequence->find(f_find);
			cout << whered;
			cout << "Do you want to keep the cropped version? (then the old one will be lost) y/n" << endl;
			string choice;
			cin >> choice;
			if (choice == "y") {
				delete sequence;
				sequence = &whered;
			}
			else {
				delete &whered;
			}
		}
		else if (operation == "9") {
			T value;
			cout << "Enter base value" << endl;
			cin >> value;
			cout << sequence->reduce(f_reduce, value) << endl;
		}
		else if (operation == "10") {
			delete sequence;
			cout << "You have finished the session.\nYou can start a new one" << endl;
			working = false;
		}
		else if (operation == "11") {
			cout << *sequence;
		}
		else if (operation == "12") {
			ISequence<T>& mapped = map_sequence<T, ArraySequence<T>, T>(f_map, *sequence);
			cout << mapped;
			cout << "Do you want to keep this version? (then the old one will be lost) y/n" << endl;
			string choice;
			cin >> choice;
			if (choice == "y") {
				delete sequence;
				sequence = &mapped;
			}
			else {
				delete &mapped;
			}
		}
		else {
			cout << "You entered an unknown operation" << endl;
		}
	}
}

template <class T>
bool f_find(T x) {
	if (typeid(x) == typeid(5)) {
		return x > 5;
	}
	if (typeid(x) == typeid(5.5)) {
		return x > 5;
	}
	if (typeid(x) == typeid('a')) {
		return 'a' <= x && x <= 'z';
	}
	return 0;
}

template <class T>
T f_reduce(T a, T b) {
	if (typeid(a) == typeid(5)) {
		return a + b;
	}
	if (typeid(a) == typeid(5.5)) {
		return a + b;
	}
	if (typeid(a) == typeid('a')) {
		return (char)(a / 2 + b / 2);
	}
	return T();
}

template <class T>
T f_map(T x) {
	if (typeid(x) == typeid(5)) {
		return x * 5;
	}
	if (typeid(x) == typeid(5.5)) {
		return x * 10;
	}
	if (typeid(x) == typeid('a')) {
		return (char)(x + 'a');
	}
	return T();
}

void call_interface() {
	bool working = true;

	EratosthenesSieve Er(10000);

	ArraySequence<int> seq(10);
	for (int i = 0; i < 10; ++i) {
		seq[i] = i;
	}
	PermutationGenerator<int> gen = PermutationGenerator<int>(seq);

	while (working) {
		// capability output
		{
			cout << "Select the type of data to be stored\nor generate permutation\nor check simplicity" << endl;
			cout << "1: int, " << endl
				<< "2: double, " << endl
				<< "3: char, " << endl
				<< "4: check simplicity, " << endl
				<< "5: gen perm, " << endl
				<< "9: EXIT" << endl;
		}

		string type;
		cin >> type;
		switch (type[0])
		{
		case '1': {
			ISequence<int>& sequence = *(new ArraySequence<int>());
			process_sequence(&sequence, f_find, f_reduce, f_map);
			break;
		}
		case '2': {
			ISequence<double>& sequence = *(new ArraySequence<double>());
			process_sequence(&sequence, f_find, f_reduce, f_map);
			break;
		}
		case '3': {
			ISequence<char>& sequence = *(new ArraySequence<char>());
			process_sequence(&sequence, f_find, f_reduce, f_map);
			break;
		}
		case '4': {
			int n;
			cin >> n;
			if (Er.is_prime(n)) {
				cout << "it is prime" << endl;
			}
			else {
				cout << "it is not prime" << endl;
			}
			break;
		}
		case '5': {
			ArraySequence<int> perm = gen.generate_permutation();
			cout << perm << endl;
			break;
		}
		case '9': {
			working = false;
			cout << "Good bye!" << endl;
			break;
		}
		default: {
			cout << "You entered the wrong command" << endl;
			break;
		}
		}
	}
}

int main() {
	
}