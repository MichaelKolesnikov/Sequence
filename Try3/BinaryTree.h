#pragma once

#include "ISequence.h"

template <class T>
class BinaryTree {
private:
	class Node {
	public:
		T value;
		BinaryTree<T>::Node* left;
		BinaryTree<T>::Node* right;

		explicit Node(T value) : value(value), left(nullptr), right(nullptr) {}
		Node(T value, BinaryTree<T>::Node* left, BinaryTree<T>::Node* right) : value(value), left(left), right(right) {}
	};

	Node* root;
public:
	BinaryTree() {}
	explicit BinaryTree(const ISequence<T>& sequence) {
		/*for (IConstIterator<T>* it = sequence.Icbegin(); !(it->is_equal(sequence.Icend())); it->next()) {

		}*/
	}

};

