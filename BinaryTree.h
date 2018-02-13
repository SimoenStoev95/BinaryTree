#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include<assert.h>
#include<cmath>

template<class T>
struct node {
	T data;
	node *left;
	node *right;
};

template<class T>
class BinaryTree;

template<class T>
int depth(const BinaryTree<T>&);

template<class T>
int depth1(const node<T>*);

template<class T>
class BinaryTree {
public:
	friend int depth<T>(const BinaryTree&);
	friend int depth1<T>(const node<T>*);
	// The big Four
	BinaryTree();
	BinaryTree(const BinaryTree&);
	~BinaryTree();
	BinaryTree& operator=(const BinaryTree& other);
	// Bool function - checks if tree is empty
	bool empty() const;
	// Functions to access the root
	node<T>* getRoot() const;
	node<T>*& getRefRoot() { return root; }
	// Gets the root and the left and the right trees
	T rootTree() const;
	BinaryTree leftTree() const;
	BinaryTree rightTree() const;
	// print function
	void print() const {
		pr(root);
		std::cout << std::endl;
	}
	// Function which creates a tree by a given root, left and right subtree
	void create3(const T&, const BinaryTree<T>&, const BinaryTree<T>&);
	//	This function creates a tree by inserting the data for the tree in orfer of Root-Left-Right
	void create() {
		createTree(root);
	}
	// Increase all leafs with a number
	void increaseLeafsWith(int number) {
		increaseLeaf(root, number);
	}
	// Search for a node in the tree
	bool searchForNode(const T&);
	// Checks if a tree is balanced
	bool isBalanced() {
		return balance(root);
	}
protected:
	// Access the root of the right tree
	node<T>* getRightRoot() const { return root->right; }
	node<T>* getLeftRoot() const { return root->left; }
protected:
	// the root of the tree
	node<T> *root;
	// help print function
	void pr(const node<T>*) const;
	// copy function
	void copyTree(const BinaryTree<T>&);
	// help copy function
	void copy(node<T>*&, node<T>* const&) const;
	// delete function
	void deleteTree(node<T>*&) const;
	// Help function for creating a tree
	void createTree(node<T>*&) const;
	// Increasing every leaf with a number
	void increaseLeaf(node<T>*&, int);
	// Searching for a node in a tree, help function for searchForNode
	bool searchFor(const node<T>*, const T&);
	// Checks if a tree is balanced
	bool balance(const node<T>*);
};

// Friend functions
template<class T>
int depth(const BinaryTree<T>& tree) {
	if (tree.empty()) return 0;
	int n, m;
	n = depth(tree.leftTree());
	m = depth(tree.rightTree());
	if (n > m) return n + 1;
	return m + 1;
}

template<class T>
int depth1(const node<T>* r) {
	if (r == NULL) return 0;
	int n, m;
	n = depth1(r->left);
	m = depth1(r->right);
	if (n > m) return n + 1;
	return m + 1;
}

// The Big Four

template<class T>
BinaryTree<T>::BinaryTree() {
	root = NULL;
}

template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other) {
	// *this = other;
	// copy(this->root, other.root);
	copyTree(other);
}

template<class T>
BinaryTree<T>::~BinaryTree() {
	deleteTree(root);
}

template<class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other) {
	if (this != &other) {
		deleteTree(root);
		copyTree(other);
	}
	return *this;
}

// The Big Four implementation ends here

// Checks if the tree is empty
template<class T>
bool BinaryTree<T>::empty() const {
	return root == NULL;
}

// Get the root of the tree
template<class T>
node<T>* BinaryTree<T>::getRoot() const {
	return root;
}

// Get the information of the tree's root
template<class T>
T BinaryTree<T>::rootTree() const {
	return root->data;
}

// Get information for the left tree
template<class T>
BinaryTree<T> BinaryTree<T>::leftTree() const {
	BinaryTree<T> tree;
 	copy(tree.root, root->left);
	return tree;
}

// Get information about the right tree
template<class T>
BinaryTree<T> BinaryTree<T>::rightTree() const {
	BinaryTree<T> tree;
	copy(tree.root, root->right);
	return tree;
}

// Copy function
template<class T>
void BinaryTree<T>::copyTree(const BinaryTree<T>& other) {
	copy(root, other.root);
}

// Helping copy function
template<class T>
void BinaryTree<T>::copy(node<T> *&_pos, node<T>* const&_other) const{
	_pos = NULL;
	if (_other) {
		_pos = new node<T>;
		assert(_pos != NULL);
		_pos->data = _other->data;
		copy(_pos->left, _other->left);
		copy(_pos->right, _other->right);
	}
}

// Delete function
template<class T>
void BinaryTree<T>::deleteTree(node<T>*& r) const {
	if (r) {
		deleteTree(r->left);
		deleteTree(r->right);
		delete r;
		r = NULL;
	}
}

// Function which creates a tree by a given root and a left and a right subtree
template<class T>
void BinaryTree<T>::create3(const T& r, const BinaryTree<T>& leftTr, const BinaryTree<T>& rightTr) {
	if (root != NULL) {
		deleteTree(root);
	}
	root = new node<T>;
	root->data = r;
	copy(root->left, leftTr.root);
	copy(root->right, rightTr.root);
}

// Helping print function
template<class T>
void BinaryTree<T>::pr(const node<T>* r) const {
	if (r) {
		pr(r->left);
		std::cout << r->data << " -- ";
		pr(r->right);
	}
}

// Help function for creating a tree
template<class T>
void BinaryTree<T>::createTree(node<T> *&r) const {
	T indentificator;
	char symbol;
	std::cout << "root: ";
	std::cin >> indentificator;
	r = new node<T>;
	r->data = indentificator;
	r->left = NULL;
	r->right = NULL;
	std::cout << "Left tree of: " << indentificator << " y/n?" << std::endl;
	std::cin >> symbol;
	if (symbol == 'y') {
		createTree(r->left);
	}
	std::cout << "Right tree of: " << indentificator << " y/n?" << std::endl;
	std::cin >> symbol;
	if (symbol == 'y') {
		createTree(r->right);
	}
}

// Increase all leafs with a number
template<class T>
void BinaryTree<T>::increaseLeaf(node<T> *&r, int number) {
	if (r) {
		r->data = r->data + number;
		increaseLeaf(r->left, number);
		increaseLeaf(r->right, number);
	}
}

// Searchin for a node in a tree
template<class T>
bool BinaryTree<T>::searchForNode(const T& elem) {
	return searchFor(root, elem);
}

// Help function for searching for a node in a tree
template<class T>
bool BinaryTree<T>::searchFor(const node<T>*r, const T& elem) {
	if (r == NULL) {
		return false;
	}
	if (r->data == elem) {
		return true;
	}
	if (r->left == NULL && r->right == NULL) {
		return false;
	}
	bool leftSide = searchFor(r->left, elem);
	bool rightSide = searchFor(r->right, elem);
	return leftSide || rightSide;
	// return searchFor(r->left, elem) || searchFor(r->right, elem);
}

// Help function for finding whether a tree is balanced or not
template<class T>
bool BinaryTree<T>::balance(const node<T>* tree) {
	if (tree == NULL || depth1(tree) == 1) {
		return true;
	}
	if (abs(depth1(tree->left) - depth1(tree->right)) > 1) {
		return false;
	}
	return balance(tree->left) && balance(tree->right);
}

#endif // BINARYTREE_H_INCLUDED