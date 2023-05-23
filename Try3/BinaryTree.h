#pragma once

#include "Sequence.h"

template <class T>
class BinaryTree {
private:
	class TreeNode {
	public:
		T value;
		BinaryTree<T>::TreeNode* left;
		BinaryTree<T>::TreeNode* right;

		explicit TreeNode(T value) : value(value), left(nullptr), right(nullptr) {}
		TreeNode(T value, BinaryTree<T>::TreeNode* left, BinaryTree<T>::TreeNode* right) : value(value), left(left), right(right) {}
	};

	TreeNode* root;
public:
	BinaryTree() {}
	/*explicit BinaryTree(const Sequence<T>* const sequence) {
		for (IConstIterator<T> it = *)
	}*/

};

