#ifndef BINARYORDTREE_H_INCLUDED
#define BINARYORDTREE_H_INCLUDED

#include "BinaryTree.h"
#include<iostream>

template<class T>
class BinaryOrdTree {};

template<class T>
friend ostream& operator<<(ostream&, const BinaryOrdTree<T>&);

template<class T>
friend istream& operator>>(istream&, BinaryOrdTree<T>&);

template<class T>
class BinaryOrdTree : public BinaryTree<T> {
public:
	// friend functions for cin and cout
	friend ostream& operator<<<T>(ostream&, const BinaryOrdTree<T>&);
	friend istream& operator>><T>(istream&, BinaryOrdTree<T>&);
	// The Big Four
	BinaryOrdTree();
	BinaryOrdTree(const BinaryOrdTree&);
	~BinaryOrdTree();
	BinaryOrdTree& operator=(const BinaryOrdTree&);
	// The Big Four ends here
	// Add node to a tree
	void AddNode(const T& list) {
		add(this->getRefRoot(), list);
	}
	// Finds the smallest element in the right tree
	T findMinimalRightELemnt() const {
		return findMin(getRightRoot());
	}
	// finds the smallest element in the tree
	T findMinElement() const {
		return findMin(this->getLeftRoot());
	}
	void deleteNode(const T& elem) {
		node<T>* pointer = NULL;
		char c = 'w';
		deleteElem(root, elem, pointer, c);
	}
private:
	void add(node<T>*&, const T&);
	T findMin(const node<T>*) const;
	void deleteElem(node<T>*&, const T&, node<T>*, char);
};

template<class T>
ostream& operator<<(ostream& out, const BinaryOrdTree<T>& tree) {
	tree.print();
	return out;
}

template<class T>
istream& operator>> (istream& in, BinaryOrdTree<T>& tree) {
	T temp;
	int counter = 0;
	while (counter < 5) {
		in >> temp;
		tree.AddNode(temp);
		counter++;
	}
	return in;
}

template<class T>
BinaryOrdTree<T>::BinaryOrdTree() : BinaryTree() {

}

template<class T>
BinaryOrdTree<T>::BinaryOrdTree(const BinaryOrdTree<T>& other) : BinaryTree(other) {

}

template<class T>
BinaryOrdTree<T>::~BinaryOrdTree() {
	BinaryTree<T>::~BinaryTree();
}

template<class T>
BinaryOrdTree<T>& BinaryOrdTree<T>::operator=(const BinaryOrdTree<T>& other) {
	BinaryTree<T>::operator=(other);
	return *this;
}

template<class T>
void BinaryOrdTree<T>::add(node<T>*& _root, const T& list) {
	if (!_root) {
		_root = new node<T>;
		_root->data = list;
		_root->left = NULL;
		_root->right = NULL;
	}
	else {
		if (_root->data > list) {
			add(_root->left, list);
		}
		else {
			add(_root->right, list);
		}
	}
}

template<class T>
T BinaryOrdTree<T>::findMin(const node<T>* _root) const {
	if (_root->left == NULL) {
		return _root->data;
	}
	return findMin(_root->left);
}


// This function doesn't work properly
template<class T>
void BinaryOrdTree<T>::deleteElem(node<T>* &_root, const T &elem, node<T>* pointer, char c) {
	if (_root) {
		// First case
		if (_root->data == elem && (_root->left == NULL && _root->right == NULL)) {
			// The previous element should point to NULL ????????? PROBLEM
			if (c == 'l')
				pointer->left = NULL;
			else if (c == 'r')
				pointer->right = NULL;
			delete _root;
		}
		// Second case
		else if (_root->left != NULL && _root->right == NULL && _root->data == elem) {
			node<T>* r1 = _root;
			_root = _root->left;
			delete r1;
		}
		else if (_root->right != NULL && _root->left == NULL && _root->data == elem) {
			node<T>* r1 = _root;
			_root = _root->right;
			delete r1;
		}
		// Third case
		else if (_root->data == elem && _root->left && _root->right) {
			_root->data = findMin(_root->right);
			pointer = _root;
			c = 'r';
			deleteElem(_root->right, findMin(_root->right), pointer, c);
		}
		// Forth/Last case
		else {
			if (elem > _root->data) {
				pointer = _root;
				c = 'r';
				deleteElem(_root->right, elem, pointer, c);
			}
			else if(elem < _root->data) {
				pointer = _root;
				c = 'l';
				deleteElem(_root->left, elem, pointer, c);
			}
		}
	}
}

#endif // BINARYORDTREE_H_INCLUDED