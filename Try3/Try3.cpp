#include "ArraySequence.h"
#include "LinkedListSequence.h"

using namespace std;

template <class T>
void process_sequence(Sequence<T>* sequence) {
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
			Sequence<T>* sub = sequence->get_sub_sequence(l, r);
			cout << "Do you want to keep the cropped version? (then the old one will be lost) y/n" << endl;
			string choice;
			cin >> choice;
			if (choice == "y") {
				delete sequence;
				sequence = sub;
			}
			else {
				delete sub;
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
		else if (operation == "10") {
			cout << "Good bye!" << endl;
			working = false;
		}
		else if (operation == "11") {
			cout << sequence;
		}
		else {
			cout << "You entered an unknown operation" << endl;
		}
	}
}

int main() {
	string type;
	cout << "Select the type of data to be stored" << endl;
	cout << "1: int, "
		<< "2: double, "
		<< "3: char, " << endl;

	cin >> type;
	switch (type[0])
	{
	case '1': {
		Sequence<int>* sequence = new ArraySequence<int>();
		process_sequence(sequence);
		break;
	}
	case '2': {
		Sequence<double>* sequence = new ArraySequence<double>();
		process_sequence(sequence);
		break;
	}
	case '3': {
		Sequence<char>* sequence = new ArraySequence<char>();
		process_sequence(sequence);
		break;
	}
	default:
		break;
	}

}